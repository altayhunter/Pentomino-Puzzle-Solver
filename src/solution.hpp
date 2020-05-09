#pragma once
#include "piece.hpp" // PieceName
#include <string> // string
#include <vector> // vector

class Node;

class Solution {
public:
	// Construct with a list of rows.
	Solution(const std::vector<Node*>& rows);
	// Print the solution unformatted (e.g. [[5,1,2],[0,4,3]]).
	void print() const;
	// Print the first n pieces of the solution.
	void print(const std::string& format, int pieces) const;

private:
	static PieceName fromIndex(int index);
	std::vector<std::vector<int>> solution;
};
