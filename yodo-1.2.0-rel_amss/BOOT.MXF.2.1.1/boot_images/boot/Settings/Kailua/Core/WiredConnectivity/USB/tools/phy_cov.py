'''
Created on Apr 30, 2019

@author: pohanw


Modified Apr 27, 2021
update write/print formatting for device tree DTSI 
@author: vpallapo


Modified Apr 30, 2019
parse excel table to table sequence
@author: pohanw
'''
import os
import tokenize
import datetime
from operator import itemgetter
import re
import argparse
import simplejson

ulog_version = 4.00

print ("\n ulog_parsing_version")
print (ulog_version)


class phy_table(object):
    def __init__ (self, input, output, prefix, postfix, table, index, comment, dft):
        self.addr_table = []
        self.data_table = []
        self.except_table = []
        self.phy_table = []
        self.table_name= table
        #self.line_proc =0
        self.total_row = 0
        self.total_except =0
        self.index_flag = index
        self.comment_flag = comment
        self.prefix = prefix
        self.postfix = postfix
        self.run_id = str(datetime.datetime.now())[:10]
        self.script_path = os.path.dirname(os.path.abspath(__file__))
        self.input_file = os.path.join(self.script_path, "usb_phy.txt")
        self.output_file = os.path.join(self.script_path, self.run_id + "_phy_tune.out")   #OUTPUT FILE
        self.dft = dft
        
        if (input):
            self.input_file = input
        if (not os.path.exists(self.input_file)):
            raise "input file not found"
        
        if(output):
            print(output)
            self.output_file = os.path.join(self.script_path, self.run_id +"_" + output +"_phy_tune.out")   #OUTPUT FILE    
            #if (not os.path.exists(output)):
            #    os.makedirs(output)
            #self.output_file = os.path.join(output, self.run_id + "_phy_tun.out")   #OUTPUT FILE    
        print("create output here" + self.output_file)
        #file_out = open(output_file, 'w')  #Overwrite the file

    def output_table(self, file_out, table, pbl_flag=False):
        total_row=0
        sep = "  //".ljust(90,'-')
        for line in table:
            print line
            file_out.write(line+"\n")
            total_row+=1
            if (pbl_flag and (total_row > 0) and ((total_row %4) == 0)):                
                print sep
                file_out.write(sep+"\n")
        if (self.dft):
            print(">;\n")
            file_out.write(">;\n")
        else:
            print("};\n")
            file_out.write("};\n")
        return total_row
                    

    def output_exception_row(self):
        file_out = open(self.output_file, 'w')  #Overwrite the file
        file_out.write("==========Exception list==========\n")
        for line in self.except_table:
            file_out.writelines( list( "%s " % item for item in line ))
            file_out.write("\n")
            print line
        file_out.write("==================================\n")
        file_out.close()

    def construct_addr_data_table(self):
        self.addr_table = []
        self.data_table = []
        self.except_table = []
        self.inputlog = open(self.input_file, 'r')  #INPUT FILE
        line_proc =0
        total_row =0
        self.total_except=0
        comment_row=[]
        for line in self.inputlog:
            row = line.replace(';', " ").replace(',', " ").split()  #removing ","  ";" and tokenize with SPACE          
            #print row
            ent_len = len(row)
            skip_pre_post = 0
            if (ent_len != 0):
                if ((ent_len == 1) and row[0]!="EMPTY" and row[0]!="END"):
                    row.insert(0,line_proc)
                    self.except_table.append(row)
                    self.total_except= self.total_except+1	
                else:
                    if (row[0]=="EMPTY"):
                        row[0] = "QUSB_HWIO_ADDR_EMPTY"
                        row.append("0x00")
                        ent_len = ent_len+1
                        skip_pre_post = 1
                    else:
                        if (row[0]=="END"):
                            row[0] = "QUSB_HWIO_ADDR_END"
                            row.append("0x00")
                            ent_len = ent_len+1
                            skip_pre_post = 1
                    try:
                        hex = str(int(row[ent_len-1],16))  #Check for error if last element not interger
                        addr= row[0]

                        if (skip_pre_post == 0):
                            if(self.prefix):
                                addr = self.prefix +"_"+addr
                            if(self.postfix):
                                addr = addr +"_"+ self.postfix                            
                            
                        ent = "  "+ addr + ","
                        ent = ent.ljust(78) + "  //   "
                        if(index_flag):
                            ent = ent + str(total_row).ljust(3) + "  :   "
                            
                        ent = ent + " ("+ row[ent_len-1] + ")"
                        #print ent
                        self.addr_table.append(ent)

                        ent = r"  /* " + addr + r","                       
                        ent = ent.ljust(79)
                        if(index_flag):
                            ent = ent + "      " +str(total_row).ljust(3)
                        ent = ent + "  */   ("+row[ent_len-1] + "),"
                        if (comment_flag ==1):
                            ent = ent + r"     // "
                            for i in xrange (1, ent_len-1):
                                if (row[i] != row[ent_len-1]):
                                    ent = ent + row[i] + ", "
                        self.data_table.append(ent)
                        total_row = total_row +1
                    except ValueError:
                        row.insert(0,line_proc)
                        self.except_table.append(row)
                        self.total_except= self.total_except+1
            line_proc = line_proc +1


    def output_addr_data_table(self):        
        #output result
        total_row =0
        file_out = open(self.output_file, 'a')  #Overwrite the file
        print("\n\n================================")
        print("========regular_phy_table===========")
        print("================================\n\n")
        file_out.write("\n\n//========phy_table===========\n")
        if (self.table_name):
            print(self.table_name+"_addr = {")
            file_out.write(self.table_name+"_address = {\n")
        else:
            print("{")
            file_out.write("{\n")
            
        total_row = self.output_table(file_out, self.addr_table)
        if (self.table_name):
            print(self.table_name+"_val = {")
            file_out.write(self.table_name+"_value = {\n")
        else:
            print("{")
            file_out.write("{\n")
        total_row = self.output_table(file_out, self.data_table)

        
        print("\n\n================================")
        print("========PBL_phy_table===========")
        print("================================\n\n")
        file_out.write("\n\n//========PBL_phy_table===========\n")
        if (self.table_name):
            print(self.table_name+"_addr = {")
            file_out.write(self.table_name+"_address = {\n")
        else:
            print("{")
            file_out.write("{\n")
        total_row = self.output_table(file_out, self.addr_table, pbl_flag=True)
        
        if (self.table_name):
            print(self.table_name+"_val = {")
            file_out.write(self.table_name+"_value = {\n")
        else:
            print("{")
            file_out.write("{\n")
        total_row = self.output_table(file_out, self.data_table,pbl_flag=True)
        
        file_out.write("\n\n\n\n\n")
        file_out.close()

        print("===================\n\n")		
        print "output File: " + self.output_file
        print(r"total row: "+ str(total_row))
        print(r"Except row: "+ str(self.total_except))
        for line in self.except_table:
            print line
        

        
    def construct_row(self, addr, data, index=None, comment=None):
        if (self.dft):
            #Updated print format for Device tree DTSI 
            ent = "    "+str(addr)
            ent = ent.ljust(80) + "  "+ str(data) + " // "
        else:
            ent = "  { "+ str(addr) + ","
            ent = ent.ljust(80) + "  ("+ str(data) + ") }, // "
                    
        if(self.index_flag and (index != None)):
            ent = ent + str(index).ljust(3)

        if (self.comment_flag ==1 and comment):
            ent = ent + r" :  "
            for i in range (0, len(comment)):
                if (comment[i] != data):
                    ent = ent + comment[i] + ", "
                
        #print ent
        return ent

    def construct_phy_table(self):
        self.phy_table = []
        self.except_table = []
        self.inputlog = open(self.input_file, 'r')  #INPUT FILE
        line_proc =0
        total_row =0
        self.total_except=0
        comment_row=[]
        for line in self.inputlog:            
            #print(line)
            row = line.replace(';', " ").replace(',', " ").split()  #removing ","  ";" and tokenize with SPACE
            #print row
            ent_len = len(row)
            
            if (ent_len != 0):
                if (ent_len == 1 and row[0]!="EMPTY"):
                    row.insert(0,line_proc+1)
                    self.except_table.append(row)
                    self.total_except= self.total_except+1
                elif (row[0]=="EMPTY"):
                    ent=self.construct_row("QUSB_HWIO_ADDR_EMPTY", "0x00", total_row)
                    phy_table.append(ent)
                    total_row = total_row +1
                else:
                    try:
                        hex = str(int(row[ent_len-1],16))  #Check for error if last element not interger
                        comment_row=[]
                        for i in range(1, ent_len-1):
                            comment_row.append(row[i])
                        addr =  row[0]
                        if(self.prefix):
                            addr = self.prefix +"_"+addr

                        if(self.postfix):
                            addr = addr +"_"+ self.postfix
                        ent = self.construct_row(addr, row[ent_len-1], total_row, comment_row)
                        self.phy_table.append(ent)

                        #data_table.append(ent)
                        total_row = total_row +1
                    except ValueError:
                        row.insert(0,line_proc+1)
                        self.except_table.append(row)
                        self.total_except= self.total_except+1
            line_proc = line_proc +1
        ent=self.construct_row("QUSB_HWIO_ADDR_END", "0x00", total_row)
        self.phy_table.append(ent)

    def output_phy_table(self):
        #output result
        total_row =0
        file_out = open(self.output_file, 'a')  #Overwrite the file
        print("\n\n===================================")
        print("========regular_phy_table===========")
        print("===================================\n\n")
        file_out.write("\n\n//========phy_table===========\n")
        
        if (self.dft):
            if (self.table_name):
                print(self.table_name+" = <")
                file_out.write(self.table_name+" = <\n")
            else:
                print("<")
                file_out.write("<\n")
        else:
            if (self.table_name):
                print(self.table_name+" = {")
                file_out.write(self.table_name+" = {\n")
            else:
                print("{")
                file_out.write("{\n")
            
        total_row = self.output_table(file_out, self.phy_table)
        
        print("\n\n================================")
        print("========PBL_phy_table===========")
        print("================================\n\n")
        file_out.write("\n\n//========pbl_phy_table===========\n")
        if (self.dft):
            if (self.table_name):
                print(self.table_name+" = <")
                file_out.write(self.table_name+" = <\n")
            else:
                print("<")
                file_out.write("<\n")
        else:
            if (self.table_name):
                print(self.table_name+" = {")
                file_out.write(self.table_name+" = {\n")
            else:
                print("{")
                file_out.write("{\n")
        
        total_row = self.output_table(file_out, self.phy_table,pbl_flag=True)
        
        file_out.write("\n\n\n\n\n")
        file_out.close()

        print("===================\n\n")		
        print "output File: " + self.output_file
        print(r"total row: "+ str(total_row))
        print(r"Except row: "+ str(self.total_except))
        for line in self.except_table:
            print line
        

if __name__ == "__main__":
    prefix = None
    postfix = None
    table_name = ""
    output_path = None
    input_path = None
    index_flag = 1
    comment_flag = 1
    separate_flag =0
    dft_flag = 1
    
    parser = argparse.ArgumentParser(description='Process argument')
    
    parser.add_argument("-pr", "--prefix", help="prefix for addr")
    parser.add_argument("-po", "--postfix", help="postfix for addr")
    parser.add_argument("-t", "--table_name", help='phy table name')
    parser.add_argument("-o", "--output_tag", help="output tag")
    parser.add_argument("-i", "--input", help="input_name")
    parser.add_argument("-n", "--index_flag", default = 1, help="attach index at the end")
    parser.add_argument("-c", "--comment_flag", default = 1, help="attach comment")   
    parser.add_argument("-s", "--separate_flag", default = 0, help="separate address and data")
    parser.add_argument("-d", "--dft_flag", default = 1, help="device tree format flag")
    args = parser.parse_args()
    print(args)
    if(args.prefix):
        print("prefix: "+ args.prefix)
        prefix = args.prefix
    if(args.postfix):
        print("postfix: "+ args.postfix)
        postfix = args.postfix
    
    if(args.table_name):
        print("table_name: "+ args.table_name)
        table_name = args.table_name

    if (args.output_tag):
        print("outputt_tag: "+ args.output_tag)
        output_tag = args.output_tag
        
    if (args.input):
        print("input: "+ args.input)
        input_path = args.input
    if (args.index_flag):
        print("index_flag: "+ str(args.index_flag))
        index_flag = int(args.index_flag)
    if (args.comment_flag):
        print("comment_flag: "+ str(args.comment_flag))
        comment_flag = int(args.comment_flag)
    
    if (args.separate_flag):
        print("separate_flag: "+ str(args.separate_flag))
        separate_flag = int(args.separate_flag)

    if (args.dft_flag):
        print("dft_flag: "+ str(args.dft_flag))
        dft_flag = int(args.dft_flag)


    builder = phy_table(input=input_path, output=output_tag, prefix=prefix, postfix=postfix, table=table_name, index=index_flag, comment=comment_flag, dft=dft_flag)
    
    
    if(separate_flag):
        builder.construct_addr_data_table()
        builder.output_exception_row()
        builder.output_addr_data_table()
    else:
        builder.construct_phy_table()
        builder.output_exception_row()
        builder.output_phy_table()    
