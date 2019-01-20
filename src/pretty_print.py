#!/usr/bin/python
import argparse
import re

format = list('''
    --  --
-----------
-----------
----------
--------
-------
--   --
-----------
'''[1:-1])

def setFormatString(index, value):
	position = -1
	for i in range(len(format)):
		if not format[i].isspace():
			position += 1
		if position == index:
			format[i] = value
			return
	assert False, 'Format string is shorter than maximum index.'

parser = argparse.ArgumentParser(description='Convert array notation into a visual output.')
parser.add_argument('solution', help='The solution to format. e.g. [0,1,1],[1,0,0]')

# Remove whitespace from string and split based on brackets
args = parser.parse_args()
solution = re.sub(r'\s+', '', args.solution, flags=re.UNICODE)
assert solution[0] == '[', 'Expected input to start with an open bracket.'
assert solution[-1] == ']', 'Expected input to end with a close bracket.'
solution = solution[1:-1]
# Indicate the location of each piece in the format string by a unique letter
char = 'a'
for piece in solution.split('],['):
	for index in piece.split(','):
		setFormatString(int(index), char)
	char = chr(ord(char) + 1)
print(''.join(format))
