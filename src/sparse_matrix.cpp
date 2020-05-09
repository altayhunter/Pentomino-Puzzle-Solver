#include "sparse_matrix.hpp" // SparseMatrix
#include "columnnode.hpp"    // ColumnNode
#include "iter_util.hpp"     // reverse, vertical
#include "solution.hpp"      // Solution
#include "state.hpp"         // State
#include "node.hpp"          // Node
#include <algorithm>         // max_element, min_element
#include <cassert>           // assert
#include <iostream>          // cout, endl
#include <iterator>          // distance
#include <vector>            // vector

using std::cout;
using std::endl;
using std::find_if;
using std::min_element;
using std::max_element;
using std::vector;

SparseMatrix::SparseMatrix(const vector<vector<State>>& values) :
		root(-1) {
	// Construct sparse matrix on a 2D vector scaffolding.
	assert(values.size() > 0);
	const int width = max_element(values.begin(), values.end(),
			[](const auto& a, const auto& b) {
				return a.size() < b.size();
			})->size();
	vector<vector<Node*>> grid(values.size(), vector<Node*>(width));
	// Create a column for each column in values; leave rows unlinked for now.
	for (int i = 0; i < width; i++) {
		// TODO: Insert left and above to keep columns and rows in expected order.
		ColumnNode* cn = root.insertRight(i);
		for (int j = 0; j < values.size(); j++) {
			if (values[j][i] == State::full) {
				grid[j][i] = cn->insertBelow();
			} else {
				assert(values[j][i] == State::invalid ||
						values[j][i] == State::empty);
			}
		}
	}
	// Iterate scaffolding to link sparse matrix rows together.
	for (const auto& row : grid) {
		auto non_null = [](Node* n) { return n; };
		auto prev = find_if(row.begin(), row.end(), non_null);
		if (prev == row.end()) break;
		auto iter = find_if(next(prev), row.end(), non_null);
		while (iter != row.end()) {
			(**prev).insertRight(*iter);
#if DEBUG
cout << "Row " << std::distance(grid.begin(), std::find(grid.begin(), grid.end(), row)) << ": Linking column " << *(**prev).head() << " to column " << *(**iter).head() << endl;
#endif
			prev = iter;
			iter = find_if(next(iter), row.end(), non_null);
		}
	}
}

SparseMatrix::~SparseMatrix() {
	// Only need to clean up each ColumnNode; they handle the rest.
	vector<ColumnNode*> columns;
	for (ColumnNode& cn : root) {
		columns.push_back(&cn);
	}
	for (ColumnNode* cn : columns) {
		delete cn;
	}
}

void SparseMatrix::findSolutions(int depth) {
	if (root.begin() == root.end()) {
#if DEBUG
cout << "Printing solution at depth " << depth << endl;
#endif
		solutions.emplace_back(selected);
		return;
	}
	ColumnNode* c = minColumn();
#if DEBUG
cout << "Depth " << depth << ": covering column " << *c << endl;
#endif
	c->cover();
	for (Node& r : vertical(*c)) {
		setSolution(&r, depth);
		for (const Node& j : r) {
			j.head()->cover();
		}
		findSolutions(depth + 1);
		// Knuth's algorithm says to assign r = *selected[depth] here.
		// However, it doesn't seem to be necessary, so assert instead.
		assert(r == *selected[depth]);
		c = r.head();
		for (const Node& j : reverse(r)) {
			j.head()->uncover();
		}
	}
#if DEBUG
cout << "Depth " << depth << ": uncovering column " << *c << endl;
#endif
	c->uncover();
}

void SparseMatrix::printSolutions(std::string format, int pieces) {
	if (solutions.empty()) {
		findSolutions(0);
	}
	for (Solution solution : solutions) {
		solution.print(format, pieces);
	}
}

void SparseMatrix::setSolution(Node* value, int index) {
	if (index >= selected.size()) {
		selected.resize(index + 1);
	}
	selected[index] = value;
}

ColumnNode* SparseMatrix::minColumn() {
	return &*min_element(root.begin(), root.end());
}
