import sys
from fastboot import FBProt

class VendorFBProt(FBProt):
	def __init__(self, verbose=False):
		FBProt.__init__(self, verbose)

def continue_cmd():
	r = fbp.continue_cmd()
	print("{}{}".format(r[0], r[1]))

def getvar(variable):
	r = fbp.getvar(variable)
	print("{}{}".format(r[0], r[1]))

if __name__ == '__main__':
	actions = {
		'continue': continue_cmd,
		'getvar': getvar }
	try:
		action = sys.argv[1]
	except IndexError:
		print('No arguments were given')
		sys.exit(1)
	args = sys.argv[2:]

	fbp = VendorFBProt()
	msn = fbp.connect(0x0dde) # This is the product id for vendor fastboot
	if msn:
		actions[action](*args)
	else:
		print('No device found')
