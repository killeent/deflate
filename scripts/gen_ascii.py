"""
Generates a file containing 1 of each ASCII character. Used to
generates the ascii.txt file in test/files.
"""

import sys
import struct

def main():
	"""main"""

	if len(sys.argv) != 2:
		print("usage: python3 gen_ascii.py output_file", file=sys.stderr)
		sys.exit(1)

	output = None
	try:
		output = open(sys.argv[1], mode='w+b')
	except OSError:
		print("could not create output file", file=sys.stderr)
		sys.exit(1)

	for i in range(0, 256):
		output.write(struct.pack('i', i))

	output.close()

if __name__ == '__main__':
	main()