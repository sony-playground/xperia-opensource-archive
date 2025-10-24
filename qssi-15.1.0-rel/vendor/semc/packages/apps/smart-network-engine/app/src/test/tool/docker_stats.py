#!python3.6.9
#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import re

units = ("B", "KIB", "MIB", "GIB", "TIB")
units2 = ("B", "KB", "MB", "GB", "TB")

def convert_size_binary(size, unit, convert_unit="B"):
    i = units.index(unit.upper()) - units.index(convert_unit.upper())
    size = size * (1024 ** i)

    #return f"{size} {convert_unit}"
    return f"{size}"

def convert_size_decimal(size, unit, convert_unit="B"):
    i = units2.index(unit.upper()) - units2.index(convert_unit.upper())
    size = size * (1000 ** i)

    #return f"{size} {convert_unit}"
    return f"{size}"

try:
    line = sys.stdin.readline()
except:
    sys.exit(1)

if not line:
    print("no line")
    sys.exit(0)

list = [x.strip() for x in line.split(',')]
result = []
for item in list:
    data = None
    item_size = re.sub(r"[^\d.]", "", item)
    item_unit = re.sub(r"[\d.]", "", item)
    if item_unit.upper() in units2:
        data = convert_size_decimal(float(item_size), item_unit, "MB")
    elif item_unit.upper() in units:
        data = convert_size_binary(float(item_size), item_unit, "MiB")
    elif "%" in item:
        data = re.sub(r"%", "", item)
    else:
        data = item

    result.append(data)

sys.stdout.write(",".join(result))

sys.exit(0)
