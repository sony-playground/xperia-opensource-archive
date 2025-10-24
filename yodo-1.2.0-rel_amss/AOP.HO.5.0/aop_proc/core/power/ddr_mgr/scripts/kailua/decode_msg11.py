import sys
import os
import struct
import collections

# Create the dictionary entries for the logfile
LogDict = collections.namedtuple("LogDict", "config_offset log_offset log_end")
LogConfig = collections.namedtuple("LogConfig",
        "test_info test_count op_info config_status alc_override_lo alc_override_hi ddr_cmd_timeout log_stop_time")
LogEvent = collections.namedtuple("LogEvent",
        "time_hi time_lo end_time mid_a mid_b seq_cp seq_type")
SeqStats = collections.namedtuple("SeqStats",
        "count last_hi last_lo worst_end mid_a mid_b")
McShub = collections.namedtuple("McShub",
        "mc_history shub_history " +
        "last_mc_hi_1 last_mc_hi_2 last_mc_lo_1 last_mc_lo_2 " +
        "last_shub_hi_1 last_shub_hi_2 last_shub_lo_1 last_shub_lo_2 ")

#        Idle  SHUB        MC        Parallel   Restore     Colapse   Flush     Abort       SW_Seq
mid_a_str = ("",   "Voltage", "Voltage", "Voltage", "Voltage", "LLC Collapse", "QActive", "NA",       "NA",  "NA")
mid_b_str = ("",   "Cmds",    "Cmds",    "Cmds",    "Cmds",    "Cmds",    "",        "Aborted",  "NA",    "NA")

#checks if path is a directory
msg11_files = ("MSGRAM11.BIN", "aop_msg11_")

def get_type(evt):
    acv = (evt & 0x0F000000) >> 24
    alc = (evt & 0x00F00000) >> 20
    ps  = (evt & 0x000F0000) >> 16
    evt = (evt & 0x0000000F)
    if (evt == 0):
        seq_type = "Idle"
    elif (evt == 1):
        seq_type = "SHUB"
    elif (evt == 2):
        seq_type = "MC"
    elif (evt == 3):
        seq_type = "Parallel"
    elif (evt == 4):
        seq_type = "Restore"
    elif (evt == 5):
        seq_type = "Collapse"
    elif (evt == 6):
        seq_type = "Flush"
    elif (evt == 7):
        seq_type = "Abort"
    elif (evt == 8):
        seq_type = "SW_SEQ"
    elif (evt == 9):
        seq_type = "CALL_PATH"
    else:
        seq_type = ("SubSeq:%d"%(evt))
    return (acv, alc, ps, evt, seq_type)

def get_cps(info):
    next_shub = (info & 0x0F000000) >> 24
    curr_shub = (info & 0x00F00000) >> 20
    bcm__shub = (info & 0x000F0000) >> 16

    next_mc = (info & 0x0F00) >> 8
    curr_mc = (info & 0x00F0) >> 4
    bcm__mc = (info & 0x000F) >> 0
    return(next_shub, curr_shub, bcm__shub, next_mc, curr_mc, bcm__mc)

def get_rel(a,b):
    if a == 0:
        return ("N/A")
    else:
        us = (b - a)/19.2   # Convert to us
        if (us > 1000000):
            return("%2.1fsec" % (us / 1000000))
        elif (us > 1000):
            return("%2.1fms" % (us / 1000))
        else:
            return("%d us" % (us))

def usage():
    print("Usage: %s [<filename>|<directory name>]" % (sys.argv[0]))
    exit(0)

def get_file(fpath, files):
    retval = None
    if os.path.isfile(fpath):
        retval = fpath
    elif os.path.isdir(fpath):
        for entry in os.listdir(fpath):
            for chkfile in files:
                if chkfile in entry:
                    print (entry, "matches", chkfile)
                    retval = os.path.join(fpath, entry)
                    break
    return (retval)

def get_ps(ps):
    val = ("0 (D4)",    "1 (D3)",    "2 (LL)",    "3 (D0)",      "4 (Col+1)",  "5 (Col+2)",   "6 (Col+3)",   "7 (Col+4)", 
           "8 (Col+5)", "9 (Col+6)", "10 (Col+7)", "11 (Col+8)", "12 (Col+9)", "13 (Col+10)", "14 (Col+11)", "15 (Max)")
    return (val[ps])

def print_ddrstats(data):
    #dataconfig = data['config']
    #datastats = data['stats']
    event_array = data['events']
    #print ("TestInfo:0x%08.8X, TestCount:%d, OpInfo:%08.8X, Status:%08.8X, ALC=%08.8X%08.8X, cmd_time=%4.3fus log_stop_time=%08.8X" %
    #                   (dataconfig.test_info, dataconfig.test_count, dataconfig.op_info, dataconfig.config_status,
    #                   dataconfig.alc_override_hi, dataconfig.alc_override_lo, (dataconfig.ddr_cmd_timeout/19.2),  dataconfig.log_stop_time))
    #print(datastats)
    last_time = 0
    last_idle = 0
    last_mc = -1
    last_shub = -1
    next_time = 0
    next_time_buffer = 48

    print ("             |         |    Sub- |   |   |DDR Power|    MC        |   SHUB    |")
    print ("   Timestamp |Rel Time |Sequence |ALC|ACV|State ARC|BCM|  Change  |BCM| Change| Relative Timestamp Notes and Info")
    print ("-------------+---------+---------+---+---+---------+---+----------+---+-------+----------------------------------")
    for event in event_array:
        new_time = (event.time_hi << 32) + event.time_lo
        if (new_time == 0):
            continue

        if (next_time != 0) and (new_time > next_time + 48):
            print (next_line)
            last_time = next_time

        next_time = 0

        rel = get_rel(last_time, new_time)
        (acv, alc, ps, seq_idx, seq_type) = get_type(event.seq_type)
        (to_shub, from_shub, bcm_shub, to_mc, from_mc, bcm_mc) = get_cps(event.seq_cp)

        mc_dir = " "
        shub_dir = " "
        ps = get_ps(ps)

        if (last_mc != -1):
            if (last_mc < bcm_mc):
                mc_dir = "^"
            elif (last_mc > bcm_mc):
                mc_dir = "."
            if (last_shub < bcm_shub):
                shub_dir = "^"
            elif (last_shub > bcm_shub):
                shub_dir = "."
        if (from_mc == to_mc):
            mc_change = "%2d | %2d"%(from_mc, to_mc)
        else:
            mc_change = "%2d +>%2d"%(from_mc, to_mc)

        if (from_shub == to_shub):
            shub_change = "%1d | %1d"%(from_shub, to_shub)
        else:
            shub_change = "%1d +>%1d"%(from_shub, to_shub)

        last_mc   = bcm_mc
        last_shub = bcm_shub
        last_time = new_time
        
        #"time_hi time_lo end_time mid_a mid_b seq_cp seq_type")
        mid_a = ""
        mid_b = ""
        elapsed = "  Sequence Did not end"
        ref_time = new_time
        start = "Start"
        bar = "|"
        if (event.mid_a) != 0xDEADBEEF:
            mid_a = "%s->Mid A(%s)%s" % (start, mid_a_str[seq_idx], get_rel(ref_time, new_time+event.mid_a))
            ref_time = new_time+event.mid_a 
            start = ""
        if (event.mid_b) != 0xDEADBEEF:
            mid_b = "%s->Mid B(%s)%s" % (start, mid_b_str[seq_idx], get_rel(ref_time, new_time+event.mid_b))
            ref_time = new_time+event.mid_b 
        if (event.end_time) != 0xDEADBEEF:
            elapsed  = "Total(%s) " % (get_rel(new_time, new_time+event.end_time))
            if event.end_time > 800*19.2:
              bar = ">"

        print(" %11X %s %7s |%8s |%2s |%2s | %7s |%2s%s|%10s|%2s%s|%6s | %15s %s%s"%
                (new_time, bar, rel, seq_type, alc, acv, ps, bcm_mc, mc_dir,
                 mc_change.center(10), bcm_shub, shub_dir, shub_change,
                 elapsed, mid_a, mid_b))
        mc_change   = "%2d | %2d"%(to_mc, to_mc)
        shub_change = "%1d | %1d"%(to_shub, to_shub)

        if (event.end_time != "0xDEADBEEF"):
            next_line = " %11X | %7s |%8s |%2s |%2s | %7s |%2s%s|%10s|%2s%s|%6s |" %\
                (new_time + event.end_time, get_rel(new_time, new_time+event.end_time),
                 "IDLE", alc, acv, ps, bcm_mc, " ", mc_change.center(10), bcm_shub, " ", shub_change)
            next_time = new_time + event.end_time
    
    if (next_time != 0 and elapsed != "  Sequence Did not end"):
        print (next_line)

    print ("-------------+---------+---------+---+---+---------+---+----------+---+-------+----------------------------------")
    print ("   Timestamp |Rel Time |    Sub- |ALC|ACV|DDR Power|BCM|  Change  |BCM| Change| Relative Timestamp Notes and Info")
    print ("             |         |Sequence |   |   |State ARC|    MC        |   SHUB    |")


def get_timestamp(arg):
    return ((arg.time_hi << 32) + arg.time_lo)

def print_seqstats(data):
    # "count last_hi last_lo worst_end mid_a mid_b")
    print ()
    sequence_array = data['sequences']
    names = ("SHUB", "MC", "PARALLEL", "RESTORE", "COLLAPSE", "LLC FLUSH", "FLUSH ABORT", "SW SEQUENCE", "CALL PATH")
    seq_idx = 0;
    for seq in sequence_array:
        name = names[seq_idx]
        seq_idx += 1
        time = seq.last_hi << 32 | seq.last_lo
        worst_end = get_rel(1, seq.worst_end)
        if (seq.mid_a == 0xDEADBEEF):
            mid_a = ""
        else:
            mid_a = "Mid_A(%s):%s " % (mid_a_str[seq_idx], get_rel(1, seq.mid_a))
        if (seq.mid_b == 0xDEADBEEF):
            mid_b = ""
        else:
            mid_b = "Mid_b(%s):%s " % (mid_b_str[seq_idx], get_rel(1, seq.mid_b))
        print ("Sequence %12s: Count:%6d; Last Timestamp:%11X; Worstcase Times:%7s %15s %15s" % (name, seq.count, time, worst_end, mid_a, mid_b));

def print_McShubstats(arg):
    #"mc_history shub_history " +
    #"last_mc_hi_1 last_mc_hi_2 last_mc_lo_1 last_mc_lo_2 " +
    #"last_shub_hi_1 last_shub_hi_2 last_shub_lo_1 last_shub_lo_2 ")
    data = arg['stats']
    print ()
    print ("MC History OLDEST->%08.8X<-NEWEST" % (data.mc_history))
    print ("Last two MC changes: %11X and %11X" % ((data.last_mc_hi_1 << 32 | data.last_mc_lo_1), (data.last_mc_hi_2 << 32 | data.last_mc_lo_2)))
    print ("SHUB History OLDEST->%08.8X<-NEWEST" % (data.shub_history))
    print ("Last two SHUB changes: %11X and %11X" % ((data.last_shub_hi_1 << 32 | data.last_shub_lo_1), (data.last_shub_hi_2 << 32 | data.last_shub_lo_2)))

def process_stats(arg):
    print ("Arg is ", arg)
    filename = get_file(arg, msg11_files)
    data = None
    if filename != None:
        print ("Got the file %s" % filename)
        # The first 4 32 bit words is the dictionary
        try:
            with open(filename, mode='rb') as file:
                fileContent = file.read()
        except:
            print ("Could not open %s: %s", (filename, sys.exc_info()[0]))
            return None

        datadict = LogDict(*struct.unpack("III", fileContent[:12]))
        #dataconfig = LogConfig(*struct.unpack("IIIIIIII", fileContent[:datadict.config_offset+32]))

        current_offset = 48

        event_array = []
        event_offset = current_offset
        event_size = 7*4
        #for event_num in range(datadict.num_events):

        for event_num in range(20):
            offset = event_offset+event_num*event_size
            current_offset += event_size
            event = LogEvent(*struct.unpack("I"*7, fileContent[offset:offset+event_size]))
            event_array.append(event)

        event_array.sort(key=get_timestamp)

        sequence_array = []
        sequence_offset = current_offset
        sequence_size = 6*4

        for sequence_num in range(9):
            offset = sequence_offset+sequence_num*sequence_size
            current_offset += sequence_size
            sequence = SeqStats(*struct.unpack("I"*6, fileContent[offset:offset+sequence_size]))
            sequence_array.append(sequence)

        McShubStats = McShub(*struct.unpack("I"*10, fileContent[current_offset:current_offset+40]))
        current_offset += 40

        data = {
                'dict' : datadict,
                #'config' : dataconfig,
                'stats'  : McShubStats,
                'events'  : event_array,
                'sequences' : sequence_array,
               }

        print ("Config Offset:0x%08.8X, Log_Offset:%08.8X, Log_End:0x%08.8X" %(datadict.config_offset, datadict.log_offset, datadict.log_end))

    return data

if __name__ == "__main__":
    if len(sys.argv) == 1:
        usage()

    for arg in sys.argv[1:]:
        info = process_stats(arg)
        if info == None:
            print ("Error returned from file")
        else:
            print_ddrstats (info)
            print_seqstats( info)
            print_McShubstats( info)
