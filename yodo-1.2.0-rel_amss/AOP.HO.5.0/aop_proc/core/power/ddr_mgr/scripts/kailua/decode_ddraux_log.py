import sys
import os
import struct
import collections
import decode_msg11

aux_files = ("ddrlog.bin", )

def build_stats(arg):
  data = None
  filename = decode_msg11.get_file(arg, aux_files)
  if filename != None:
    print ("Got the file %s" % filename)
    try:
        with open(filename, mode='rb') as file:
            fileContent = file.read()
    except:
        print ("Could not open %s: %s", (filename, sys.exc_info()[0]))
        return None

  count=20
  offset = 0
  seq_ts_hi = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4
  seq_ts_lo = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4
  seq_end = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4
  seq_mida = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4
  seq_midb = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4
  seq_cp = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4
  seq_type = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4

  event_array=[]
  for idx in range(count):
    event = decode_msg11.LogEvent(seq_ts_hi[idx], seq_ts_lo[idx], seq_end[idx],
                                  seq_mida[idx], seq_midb[idx],
                                  seq_cp[idx], seq_type[idx])
    event_array.append(event)
  event_array.sort(key=decode_msg11.get_timestamp)

  offset += 4   # Hole in the HW data structure
  mc_history = struct.unpack("I", fileContent[offset:offset+4])
  offset += 4
  offset += 4   # Hole in the HW data structure
  shub_history = struct.unpack("I", fileContent[offset:offset+4])
  offset += 4
  offset += 4   # Hole in the HW data structure
  offset += 4   # Hole in the HW data structure

  count = 2
  mc_change_hi = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4
  mc_change_lo = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4
  shub_change_hi = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4
  shub_change_lo = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4

  mcshub = decode_msg11.McShub(mc_history, shub_history, 
                               mc_change_hi[0], mc_change_hi[1],
                               mc_change_lo[0], mc_change_lo[1],
                               shub_change_hi[0], shub_change_hi[1],
                               shub_change_lo[0], shub_change_lo[1])

  count=8
  seq_counts = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4
  seq_last_hi = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4
  seq_last_lo = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4
  seq_worst = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4
  seq_worst_a = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4
  seq_worst_b = struct.unpack("I"*count, fileContent[offset:offset+count*4])
  offset += count*4

  sequence_array = []
  for idx in range(8):
    seq = decode_msg11.SeqStats(seq_counts[idx], seq_last_hi[idx], seq_last_lo[idx],
                                seq_worst[idx], seq_worst_a[idx], seq_worst_b[idx])
    sequence_array.append(seq)

  data = {
    'events' : event_array,
    'sequences' : sequence_array,
    'stats' : mcshub,
  }

  return data


if __name__ == "__main__":
  if len(sys.argv) == 1:
    decode_msg11.usage()

  for arg in sys.argv[1:]:
    info = build_stats(arg)
    if info == None:
      print("Error returned from file")
    else:
      decode_msg11.print_ddrstats(info)
      decode_msg11.print_seqstats(info)
      decode_msg11.print_McShubstats(info)
