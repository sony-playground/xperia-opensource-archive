import os
import time
import string
import argparse

parser = argparse.ArgumentParser(description="Run a tool for all files in a directory tree")
parser.add_argument("tool", help="tool that should be executed for all files")
parser.add_argument("build_root", help="build root directory")
parser.add_argument("directory", help="root directory of the files which should be handled")
parser.add_argument("excludeFile", help="file which contain a list of files (full path from build root) that should be excluded")
args=parser.parse_args()


filelist = []

if os.path.exists(args.excludeFile):
#	print ("Listing files to exclude:")
	fp = open(args.excludeFile, "r")
	line = fp.readline()
	while (line != ""):
		line = line.strip()
		filelist.append(args.build_root + "/" + line)
		line = fp.readline()
	fp.close()
#	print filelist

fullpath = args.build_root + "/" + args.directory

print("Searching for files in directory " + fullpath)

if os.path.exists(fullpath):
	for root, dirs, files in os.walk(fullpath):
		for name in files:
			fullpathname = os.path.join(root,name)
			if (fullpathname not in filelist):
				command = args.tool + " " + fullpathname + " > /dev/null"
				ret = os.system(command)
				if (ret != 0):
					command = args.tool + " " + fullpathname
					print (command + '\n')
					# Rerun command and show output if a problem occurred
					ret = os.system(command)
