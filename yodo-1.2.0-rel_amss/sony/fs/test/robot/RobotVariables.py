#!/usr/bin/env python3

from Definitions import *

class FastbootResponse:
	status = "OKAY"
	value = "No value yet"

class TestContentVariables:
	filename = "filename"

class VarLists:
	getvar_list = []
	getvar_all_list = []
	getvar_all_result = "No value yet"

### Global variables ###
gFastbootResponse = FastbootResponse()
gTCV = TestContentVariables()
gVarLists = VarLists()
