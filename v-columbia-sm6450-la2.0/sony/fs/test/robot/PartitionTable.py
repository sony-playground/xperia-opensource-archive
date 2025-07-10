import collections
import struct
import sys
import logging
import tarfile
import uuid

from os import getcwd
from os.path import join
from shutil import copy2
from zipfile import ZipFile
from pprint import pformat


class GPTDecoder(object):
    # TODO use zlib.crc32

    # http://en.wikipedia.org/wiki/GUID_Partition_Table#Partition_table_header_.28LBA_1.29
    GPT_HEADER_FORMAT = """
8s signature
4s revision
L header_size
L crc32
4x _
Q current_lba
Q backup_lba
Q first_usable_lba
Q last_usable_lba
16s disk_guid
Q part_entry_start_lba
L num_part_entries
L part_entry_size
L crc32_part_array
    """

    # http://en.wikipedia.org/wiki/GUID_Partition_Table#Partition_entries_.28LBA_2.E2.80.9333.29
    GPT_PARTITION_FORMAT = """
16s type
16s unique
Q first_lba
Q last_lba
Q flags
72s name
    """

    @classmethod
    def _make_fmt(cls, name, format, extras=[]):
        type_and_name = [l.split(None, 1) for l in format.strip().splitlines()]
        fmt = '<' + ''.join(t for (t, n) in type_and_name)
        tupletype = collections.namedtuple(name, [n for (t, n) in type_and_name if n != '_'] + extras)
        return (fmt, tupletype)

    @classmethod
    def read_header(cls, fp, lba_size=4096):
        # skip MBR
        fp.seek(1 * lba_size)
        fmt, gpt_header = cls._make_fmt('GPTHeader', cls.GPT_HEADER_FORMAT)
        data = fp.read(struct.calcsize(fmt))
        header = gpt_header._make(struct.unpack(fmt, data))
        if header.signature != b'EFI PART':
            raise RuntimeError('Bad signature: %r' % header.signature)
        if header.revision != b'\x00\x00\x01\x00':
            raise RuntimeError('Bad revision: %r' % header.revision)
        if header.header_size < 92:
            raise RuntimeError('Bad header size: %r' % header.header_size)
        # TODO check crc32
        header = header._replace(disk_guid=str(uuid.UUID(bytes_le=header.disk_guid)),)
        return header

    @classmethod
    def read_partitions(cls, fp, header, lba_size=4096):
        fp.seek(header.part_entry_start_lba * lba_size)
        fmt, gpt_partition = cls._make_fmt('GPTPartition', cls.GPT_PARTITION_FORMAT, extras=['index'])
        for idx in range(1, 1 + header.num_part_entries):
            data = fp.read(header.part_entry_size)
            if len(data) < struct.calcsize(fmt):
                raise RuntimeError('Short partition entry')
            part = gpt_partition._make(struct.unpack(fmt, data) + (idx,))
            if part.type == 16 * '\x00':
                continue
            part = part._replace(type=str(uuid.UUID(bytes_le=part.type)),
                                 unique=str(uuid.UUID(bytes_le=part.unique)),
                                 # do C-style string termination; otherwise you'll see a
                                 # long row of NILs for most names
                                 name=part.name.decode('utf-16').split('\0', 1)[0],)
            yield part


class PartitionTable(object):
    _slots = ('A', 'B')
    _slot_suffixes = ('_a', '_b')

    def __init__(self, table, images):
        self._table = table
        self._partition_images = images
        self._has_slots = any(partition for partition in self._table if partition.endswith(self._slot_suffixes))
        self._info = [(slot, suffix) for slot in self._slots for suffix in self._slot_suffixes
                      if slot == suffix.replace('_', '').upper()] if self._has_slots else None

    @property
    def partition_table(self):
        return self._table

    @property
    def partition_images(self):
        return self._partition_images

    @property
    def has_slots(self):
        return self._has_slots

    @property
    def slot_info(self):
        return self._info


class PartitionTableGenerator(object):
    """
        This class is given a partition.zip containing LUN files and generates a partition table as dictionary.

        For example:
            {'bluetooth_a': {'lun': '0',
                                   'size': 256,
                                   'start_sector': 62889},
             'bluetooth_b': {'lun': '0',
                                   'size': 256,
                                   'start_sector': 1407673},}

        $ ls
        partition.zip    simplegpt.py
        $ unzip partition.zip
        Archive:  partition.zip
        inflating: partition-image-LUN0.sin
        inflating: partition-image-LUN1.sin
        inflating: partition-image-LUN2.sin
        $ tar xf partition-image-LUN0.sin
        $ tar xf partition-image-LUN1.sin
        $ tar xf partition-image-LUN2.sin
        $ ls table
        partition-image-LUN0.sin    partition-image-LUN2.sin    partitionimage_1.000
        partition-image-LUN1.sin    partitionimage_0.000        partitionimage_2.000
        $ python simplegpt.py partitionimage_0.000
    """

    logger = logging.getLogger('PartitionTableGenerator')

    @classmethod
    def create_from_zip(cls, partition_zip_path, unpack_path):  # partition.zip from APP-SW
        def extract_partition_zip():
            partitions = {}
            partition_images = {}
            with ZipFile(partition_zip_path) as zip:
                for lun_file in zip.namelist():
                    if lun_file.endswith(('.sin')) and 'LUN' in lun_file:  # extract partition-image sin
                        zip.extract(lun_file, unpack_path)  # unzip partitionimage_0.000
                        cls.logger.info('extracted file {}'.format(lun_file))

                        cls.untarzip_partition_sin(lun_file, unpack_path, partitions, partition_images)

            return partitions, partition_images

        table, partition_images = extract_partition_zip()
        return PartitionTable(table, partition_images)

    @classmethod
    def create_from_sin(cls, lun_sin_file, source_path, unpack_path):
        partitions = {}
        partition_images = {}
        copy2(join(source_path, lun_sin_file), join(unpack_path, lun_sin_file))
        cls.untarzip_partition_sin(lun_sin_file, unpack_path, partitions, partition_images)
        return PartitionTable(partitions, partition_images)

    @classmethod
    def untarzip_partition_sin(cls, lun_sin_file, unpack_path, partitions, partition_images):
        lun_file_path = join(unpack_path, lun_sin_file)

        with tarfile.open(lun_file_path, "r") as archive_file:
            for member in archive_file.getmembers():
                if member.name.endswith('.000') and 'partition' in member.name:
                    cls.logger.info('unzipping {} => {}'.format(member.name, unpack_path))
                    archive_file.extract(member, unpack_path)
                    lun_image = join(unpack_path, member.name)
                    lun_number = lun_sin_file.split('.')[0][-1]
                    partition_images[lun_number] = lun_image
                    partitions.update(cls.get_partitions(lun_image, lun_number))

    @staticmethod
    def get_partitions(lun_file, lun_number):
        with open(lun_file, 'rb') as lun_fp:
            header = GPTDecoder.read_header(lun_fp)
            table = {str(part.name): {'start_sector': part.first_lba,
                                      'size': hex(part.last_lba - part.first_lba + 1),
                                      'flags': format(part.flags, '#016x'),
                                      'unique': part.unique,
                                      'type': part.type,
                                      'lun': lun_number}
                     for part in GPTDecoder.read_partitions(lun_fp, header)}
        return table


if __name__ == '__main__':
    logging.basicConfig(filename='tmp.log',
                        level=logging.DEBUG if '-v' in sys.argv else logging.INFO,
                        format='%(asctime)s %(name)-15s %(levelname)-8s %(message)s')

    console_handler = logging.StreamHandler(sys.stdout)
    console_handler.setFormatter(logging.Formatter('%(name)-15s %(levelname)-8s %(message)s'))

    # add the console handler to the root logger
    logging.getLogger('').addHandler(console_handler)

    new_sw_unpack_path = join(getcwd(), 'table')

    table = PartitionTableGenerator.create_from_zip('partition.zip', new_sw_unpack_path)
    logging.info('generated table=\n{}'.format(pformat(table.partition_table)))
    logging.info('generated images=\n{}'.format(pformat(table.partition_images)))
    if table.has_slots:
        for slot, suffix in table.slot_info:
            logging.info('generated slots={} suffix={}'.format(slot, suffix))
