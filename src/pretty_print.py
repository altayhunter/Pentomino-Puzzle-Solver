#!/usr/bin/python
import argparse
import ast

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

# Print the given labels using the whitespace of format.
def printFormatted(labels):
	i = 0
	for c in format:
		if c.isspace():
			print(c, end='')
		else:
			print(labels[i], end='')
			i += 1
	print()

# Insert value into array at index, expanding array as necessary.
def insertAtIndex(array, index, value):
	while len(array) < index + 1:
		array.append(None)
	array[index] = value

# Input: [[3,2],[1,5],[4,0]]
# Output: ['c', 'b', 'a', 'a', 'c', 'b']
def createLabelArray(indexes):
	result = []
	for i in range(len(indexes)):
		label = chr(ord('a') + i)
		for index in indexes[i]:
			insertAtIndex(result, index, label)
	return result

def main():
	parser = argparse.ArgumentParser(description='Convert array notation into a visual output.')
	parser.add_argument('solution', help='The solution to format. e.g. [0,1,1],[1,0,0]')

	args = parser.parse_args()
	solution = ast.literal_eval(args.solution)
	labels = createLabelArray(solution)
	printFormatted(labels)

if __name__ == "__main__":
	main()
