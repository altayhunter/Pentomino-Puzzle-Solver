#pragma once
#include "columnnode.hpp" // ColumnNode
#include <vector>         // vector

class Node;
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
	void findSolution(int depth);

private:
	void setSolution(Node* value, int index);
	void printSolution() const;
	ColumnNode* minColumn();

	ColumnNode root;
	std::vector<Node*> solution;
};
