import sys
from fastboot import FBProt

class BadFBProt(FBProt):
	def __init__(self, verbose=False):
		FBProt.__init__(self, verbose)

	def bad_authenticate_challenge(self, f):
		self.put_request('SAKE-Authenticate:challenge=1')
		rs, rd = self.get_response()
		while rs == 'DATA':
			data = self.get_data(rd)
			if data != None:
				f.write(data)
			rs, rd = self.get_response()
		return rs,rd

	def bad_authenticate_response(self, data):
		rs, rd = self.download(data)
		if rs == 'OKAY':
			self.put_request('SAKE-Authenticate:response,1')
			r = self.get_response()
		return r

def bad_authenticate_challenge(arg):
	challenge = arg
	f = open(challenge, "wb")
	r = fbp.bad_authenticate_challenge(f)
	f.close()
	print("{}{}".format(r[0], r[1]))

def bad_authenticate_response(response):
	f = open(response, "rb")
	data = f.read()
	f.close()
	r = fbp.bad_authenticate_response(data)
	print("{}{}".format(r[0], r[1]))

if __name__ == '__main__':
	actions = {
		'Authenticate:challenge': bad_authenticate_challenge,
		'Authenticate:response': bad_authenticate_response }
	try:
		action = sys.argv[1]
	except IndexError:
		print('No arguments were given')
		sys.exit(1)
	args = sys.argv[2:]

	fbp = BadFBProt()
	msn = fbp.connect()
	if msn:
		actions[action](*args)
	else:
		print('No device found')
