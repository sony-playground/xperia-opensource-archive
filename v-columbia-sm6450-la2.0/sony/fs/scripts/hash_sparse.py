#!/usr/bin/env python

# Copyright (C) 2016 Sony Mobile Communications Inc.
# All rights, including trade secret rights, reserved.

"""This module contains functions that can be used to generate a
SHA256 hashlist for an Android sparse image. A hashlist is a list of
hashes, where every hash corresponds to part of the corresponding
input file. A hashlist is commonly used to allow verification of
streamed images, eliminating the need to store the whole image in RAM
at any point in time.

Running this module will read an Android sparse image from stdin and
produce a hashlist on stdout. This hashlist can be saved to a file, or
piped into further processing applications. As an example, the
following command pipeline will produce a DER-formatted, signed, CMS
(Cryptographic Message Syntax) structure, containing the hashlist
(tested with OpenSSL 1.0.2f):

 $ cat <infile> | ./hash_sparse.py | openssl cms -sign -signer <cert>
     -inkey <privkey> -out <outfile> -binary -outform DER -nodetach
"""

import hashlib
import struct
import sys
import unittest


_SPARSE_MAGIC = 0xed26ff3a
_SPARSE_MAJOR_VERSION = 1
_SPARSE_V1_FILE_HDR_SIZE = 28
_SPARSE_V1_CHUNK_HDR_SIZE = 12
_SPARSE_V1_CHUNK_TYPE_RAW = 0xcac1
_SPARSE_V1_CHUNK_TYPE_FILL = 0xcac2
_SPARSE_V1_CHUNK_TYPE_DONT_CARE = 0xcac3
_SPARSE_V1_CHUNK_TYPE_CRC32 = 0xcac4


class InvalidFileError(Exception):
    """Exception raised for invalid input files"""
    pass


class WrongVersionError(Exception):
    """Exception raised when a sparse image is the wrong version"""
    pass


class InvalidChunkTypeError(Exception):
    """Exception raised when an unknown chunk type is encountered"""
    pass


class IncompleteFileError(Exception):
    """Exception raised when a file ends prematurely"""
    pass


def _read_struct(fobj, fmt):
    size = struct.calcsize(fmt)
    data = fobj.read(size)
    hdr_hash = hashlib.sha256(data).digest()
    return (hdr_hash,) + struct.unpack(fmt, data)


def _read_hdr(fobj):
    (
        hdr_hash, magic, major_version, dummy_minor_version, file_hdr_sz,
        chunk_hdr_sz, blk_sz, total_blks, total_chunks, image_checksum
    ) = _read_struct(fobj, '<IHHHHIIII')

    if magic != _SPARSE_MAGIC:
        raise InvalidFileError()

    if major_version != _SPARSE_MAJOR_VERSION:
        raise WrongVersionError()

    if file_hdr_sz != _SPARSE_V1_FILE_HDR_SIZE:
        raise InvalidFileError()

    if chunk_hdr_sz != _SPARSE_V1_CHUNK_HDR_SIZE:
        raise InvalidFileError()

    return (hdr_hash, blk_sz, total_blks, total_chunks, image_checksum)


def _hash_data(fobj, size):
    data = fobj.read(size)
    if len(data) != size:
        raise IncompleteFileError()
    return hashlib.sha256(data).digest()


def output_hash_list(infobj=sys.stdin, outfobj=sys.stdout):
    """This function will read an Android sparse image from the input file
    object ('infobj', default sys.stdin), and write a list of SHA256
    hashes to the output file object ('outfobj', default stdout).

    Every part of the sparse image will be covered by a hash. An
    Android sparse image contains a file header followed by a number
    of chunks. Every chunk also has a header, describing what the
    chunk contains. The first hash in the output covers the file
    header, and subsequent hashes represent the individual chunks. A
    chunk is represented by one or two hashes, depending on the chunk
    type: one hash covering the header, and an optional second hash
    covering the contents of the chunk (raw data, fill pattern or
    CRC32). The hashes are concatenated, one after another, in binary
    form, with no additional formatting.
    """
    (
        hdr_hash, blk_sz, dummy_total_blks, total_chunks, dummy_image_checksum
    ) = _read_hdr(infobj)

    outfobj.write(hdr_hash)

    for _ in xrange(total_chunks):
        (
            chunk_hdr_hash, chunk_type, dummy_reserved,
            chunk_sz, dummy_total_sz
        ) = _read_struct(infobj, '<HHLL')

        outfobj.write(chunk_hdr_hash)

        if chunk_type == _SPARSE_V1_CHUNK_TYPE_RAW:
            outfobj.write(_hash_data(infobj, chunk_sz * blk_sz))
        elif chunk_type == _SPARSE_V1_CHUNK_TYPE_FILL:
            outfobj.write(_hash_data(infobj, 4))
        elif chunk_type == _SPARSE_V1_CHUNK_TYPE_CRC32:
            outfobj.write(_hash_data(infobj, 4))
        elif chunk_type != _SPARSE_V1_CHUNK_TYPE_DONT_CARE:
            raise InvalidChunkTypeError()


class SparseTestCase(unittest.TestCase):
    """Unit test class for the module"""

    _valid_header = [0x3a, 0xff, 0x26, 0xed, 0x01, 0x00, 0x00, 0x00,
                     0x1c, 0x00, 0x0c, 0x00, 0x00, 0x10, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00]

    _valid_header_hash = [0x13, 0xc9, 0xa2, 0xeb, 0x25, 0x70, 0x60,
                          0x4e, 0xdc, 0xb5, 0x75, 0xbf, 0x71, 0x43,
                          0x7b, 0x92, 0xa5, 0x76, 0x0b, 0x39, 0xf5,
                          0x40, 0xda, 0x5d, 0xbf, 0x6f, 0xd7, 0xf0,
                          0xcc, 0xcd, 0x69, 0x97]

    _test_raw_chunk_hdr = [0xc1, 0xca, 0x00, 0x00, 0x01, 0x00, 0x00,
                           0x00, 0x00, 0x00, 0x00, 0x00]

    _test_raw_chunk = _test_raw_chunk_hdr + [0xaa] * 4096

    _test_raw_chunk_hdr_hash = [0xfc, 0x48, 0x06, 0x7c, 0xba, 0x55,
                                0xd4, 0x46, 0x15, 0x43, 0x98, 0x68,
                                0xe2, 0xd2, 0x60, 0x50, 0xe9, 0x0c,
                                0xb1, 0xe6, 0x30, 0x43, 0x8d, 0xb5,
                                0x06, 0x4a, 0xaa, 0xa3, 0x84, 0x45,
                                0xd3, 0xac]

    _test_raw_chunk_hash = [0xc6, 0x22, 0x00, 0x54, 0x93, 0xc4, 0xcb,
                            0x75, 0xf3, 0xe0, 0x8e, 0xda, 0x4c, 0xc0,
                            0xbf, 0xe1, 0x72, 0xe2, 0xc5, 0xee, 0xca,
                            0x66, 0x1e, 0xc4, 0x90, 0x8c, 0x54, 0x90,
                            0xfc, 0x3d, 0x69, 0x94]

    _test_fill_chunk_hdr = [0xc2, 0xca, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x10, 0x00, 0x00]

    _test_fill_chunk = _test_fill_chunk_hdr + [0xaa] * 4

    _test_fill_chunk_hash = [0xdb, 0xed, 0x14, 0xce, 0xb0, 0x01, 0xd1,
                             0x10, 0xd7, 0x66, 0xb9, 0x01, 0x3d, 0x3b,
                             0x5b, 0xbf, 0xfa, 0xd6, 0x91, 0x54, 0x75,
                             0xa9, 0xba, 0x07, 0x93, 0x2d, 0x2a, 0xc0,
                             0x57, 0x94, 0x4c, 0x04]

    _test_crc_chunk_hdr = [0xc4, 0xca, 0x00, 0x00, 0x00, 0x00, 0x00,
                           0x00, 0x00, 0x10, 0x00, 0x00]

    _test_crc_chunk = _test_crc_chunk_hdr + [0xaa] * 4

    _test_crc_chunk_hash = _test_fill_chunk_hash

    _test_dont_care_chunk = [0xc3, 0xca, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x10, 0x00, 0x00]

    @staticmethod
    def _run(contents):
        import StringIO
        contents_str = ''.join([chr(x) for x in contents])
        infobj = StringIO.StringIO(contents_str)
        outfobj = StringIO.StringIO()
        output_hash_list(infobj, outfobj)
        output = outfobj.getvalue()
        outfobj.close()
        return output

    @staticmethod
    def _replace(old_list, offset, replace):
        new_list = old_list[:]
        new_list[offset:offset+len(replace)] = replace
        return new_list

    def _one_chunk(self, chunk):
        one_chunk = self._replace(self._valid_header, 20, [0x01])
        one_chunk += chunk
        return one_chunk

    def test_empty_file(self):
        """Verify that an empty file fails to parse"""
        with self.assertRaises(Exception):
            self._run([])

    def test_valid_header_only(self):
        """Verify that a valid header parses without raising an exception"""
        self._run(self._valid_header)

    def test_invalid_magic(self):
        """Verify that an invalid header magic causes a failure"""
        with self.assertRaises(InvalidFileError):
            self._run([0] * _SPARSE_V1_FILE_HDR_SIZE)

    def test_invalid_major_version(self):
        """Verify that the parser checks the major version in the file header
        """
        with self.assertRaises(WrongVersionError):
            self._run(self._replace(self._valid_header, 4, [0x00, 0x00]))

        with self.assertRaises(WrongVersionError):
            self._run(self._replace(self._valid_header, 4, [0x02, 0x00]))

    def test_invalid_hdr_size(self):
        """Verify that a header with invalid header size fails"""
        with self.assertRaises(InvalidFileError):
            self._run(self._replace(self._valid_header, 8, [0x00, 0x00]))

    def test_invalid_chunk_header_size(self):
        """Verify that a header with invalid chunk header size fails"""
        with self.assertRaises(InvalidFileError):
            self._run(self._replace(self._valid_header, 10, [0x00, 0x00]))

    def test_header_hash(self):
        """Verify that the header hash is correct"""
        output = self._run(self._valid_header)
        self.assertEqual([ord(x) for x in output], self._valid_header_hash)

    def test_chunk_header_hash(self):
        """Verify that the hash of the chunk header is correct"""
        output = self._run(self._one_chunk(self._test_raw_chunk))
        self.assertEquals([ord(x) for x in output[32:64]],
                          self._test_raw_chunk_hdr_hash)

    def test_raw_hash(self):
        """Verify that the hash of a 'raw' chunk is correct"""
        output = self._run(self._one_chunk(self._test_raw_chunk))
        self.assertEquals([ord(x) for x in output[64:]],
                          self._test_raw_chunk_hash)

    def test_incomplete(self):
        """Verify that an incomplete file fails"""
        with self.assertRaises(IncompleteFileError):
            self._run(self._one_chunk(self._test_raw_chunk_hdr))

    def test_fill_hash(self):
        """Verify that the hash of a 'fill' chunk is correct"""
        output = self._run(self._one_chunk(self._test_fill_chunk))
        self.assertEquals([ord(x) for x in output[64:]],
                          self._test_fill_chunk_hash)

    def test_crc_hash(self):
        """Verify that the hash of a 'CRC32' chunk is correct"""
        output = self._run(self._one_chunk(self._test_crc_chunk))
        self.assertEquals([ord(x) for x in output[64:]],
                          self._test_crc_chunk_hash)

    def test_dont_care_no_hash(self):
        """Verify that a 'dont care' chunk does not output a hash"""
        output = self._run(self._one_chunk(self._test_dont_care_chunk))
        self.assertEquals(64, len(output))

    def test_invalid_chunk(self):
        """Verify that an invalid chunk type fails"""
        with self.assertRaises(InvalidChunkTypeError):
            self._run(self._one_chunk([0xaa] * _SPARSE_V1_CHUNK_HDR_SIZE))

if __name__ == '__main__':
    output_hash_list()
