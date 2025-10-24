'''
Created on Jul 18, 2013

@author: pohanw

Modified Aug 18, 2014
Added event buffer parsing
Added markers at the first entry of each log category
@author: psapin

Copyright  2013-2018 by Qualcomm Technologies, Inc. All Rights Reserved.
'''
import os
import tokenize
from operator import itemgetter
import re
 
period_per_ms = 32
listfile = os.listdir("./")

log=[]  #temp array of all the entries
for i in listfile:
  #Sort all the file end with .cir (only .cir, ignore other...)
  if (re.search(".*.cir", i)):
    cat = i.split(".")[0]  #Use file name as Category
    print (cat)
    inputlog = open(i, 'r')
    for line in inputlog:
      if (re.search("    \(\d+?,", line)):   #Only sort the file that start with "    (12345,"
        row = line.lstrip("    \(").rstrip("),\n").split(",")  #removing extra stuff and Tokenizer the row with ", "

        #event buffer parsing
        if(cat == "event"):
          cnt = int(row[1].strip())
          #create new log entry for each item in timetick list
          if cnt != 0:
            core = int(row[0].strip())
            id_0 = row[2]
            log_depth_index = int(row[3].strip())
            timetick_index = 4 if '(' in row[4] else 5 
            row[timetick_index] = row[timetick_index].lstrip(' (')
            timeticks = row[timetick_index:]
            for tick in timeticks:
              curr_timetick = int(tick.strip())
              if curr_timetick != 0:
                milliseconds = float(curr_timetick)/period_per_ms
                new_row = [curr_timetick, milliseconds, cat, core, id_0]
                log.append(new_row)

        else:
          if (int(row[0])!=0):  #remove the 0 entries
            log.append(row)
            log[-1].insert(1, cat)  #insert Category to each row
            if (cat == "qmidata"):
              start_index = 2
              end_index   = 7
              j = start_index
              for entry in log[-1][start_index:end_index]: # extract data fields to convert to bytes.  TODO modify the range depending on # of bytes stored
                if (re.search(' \(', entry)):  # sanitize input
                  entry = entry.lstrip(" \(")
                if (re.search(' ', entry)):
                  entry = entry.lstrip(" ")
                if (re.search('\)', entry)):
                  entry = entry.rstrip("\)")
                
                print ("input " + entry)

                entry = '%08x' % int(entry)
                print ("input in hex " + entry)
                out_list = []
                # big endian
  #              for i in range(0, len(entry), 2):
  #                out_list.insert(0, entry[i:i+2])

                # little endian
                for i in range(0, len(entry), 2):
                  out_list.append(entry[i:i+2])

                log[-1][j] = " ".join(out_list)
                print( "output " + log[-1][j])
                j = j + 1

  #         a = log[-1][0]
  #         b = str((int(log[-1][0])*32)/1000)
            log[-1][0] = int(log[-1][0]) # timetick
            log[-1].insert(1, (float(log[-1][0])/period_per_ms)) #convert timetick to millisecond 

    inputlog.close()
    
log.sort(key=itemgetter(0))

#add markers at the first entry of each log category
seen = [] #temp array of seen categories
for indx, val in enumerate(log):
  if val[2] not in seen:
    log.insert(indx, [val[0], val[1], val[2], '### first '+val[2]+' entry ###'])
    seen.append(val[2])

final_file = open("./~result.out", 'w')  #Overwrite the file
final_file.write("Timetick  \tTime(ms)       \tTimeDiff(ms)   \tCategory  \tOther:\n")
previous_row = log[0][1]
for item in log:
  diff = "(+%.3fms)" %(item[1]-previous_row) #Time different from last row, with resolution of 3 decimal
  previous_row = item[1]
  item[1] = "%.3fms" %item[1]  #make time with resolution of 3 decimal and add unit
  final_file.write("%s\t%s\t%s\t%s\t%s\n" %(str(item[0]).ljust(10), item[1].ljust(15), diff.ljust(15), item[2].ljust(10), str(item[3:])))
  
final_file.close()
