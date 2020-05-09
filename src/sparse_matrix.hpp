#pragma once
#include "columnnode.hpp" // ColumnNode
#include <string>         // string
#include <vector>         // vector

class Node;
class Solution;
enum class State : char;

// This class represents the given 2D list as a sparse matrix composed of
// doubly linked lists (i.e. a torus). The following input:
// {{0, 1, 1}, {1, 1, 0}, {0, 0, 1}}
// Would produce this structure:
// [-1]<=>[0]<=>[1]<=>[2]<=>
//         |     n <=> n <=>
//         n <=> n <=> |
//         |     |     n <=>
// Where -1, 0, 1, and 2 are ColumnNodes and each n is a Node. The solution to
// this particular problem, which is the last two rows, would be printed as:
// [0,1],[2]
class SparseMatrix {
public:
	SparseMatrix(const std::vector<std::vector<State>>& values);
	~SparseMatrix();
	// Print the first n pieces of each solution in the given format.
	void printSolutions(std::string format, int pieces);

private:
	// Perform Knuth's Algorithm X to discover the solutions to the puzzle.
	void findSolutions(int depth);
	// Place the given row into the given index of the current state.
	void setSolution(Node* value, int index);
	// Print the current state to the console.
	void printSolution() const;
	// Return the column connected to the fewest rows.
	ColumnNode* minColumn();

	// Root of the sparse matrix data structure.
	ColumnNode root;
	// Ordered list of selected rows, corresponding to current state of puzzle.
	std::vector<Node*> selected;
	// Ordered list of solutions found.
	std::vector<Solution> solutions;
};
