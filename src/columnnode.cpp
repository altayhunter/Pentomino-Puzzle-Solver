#include "columnnode.hpp" // ColumnNode
#include "iter_util.hpp"  // reverse, vertical
#include <cassert>        // assert
#include <vector>         // vector
#include <iostream>       // cout

using std::ostream;
using std::vector;

// A ColumnNode cleans up only the Nodes directly below itself.
ColumnNode::~ColumnNode() {
	vector<Node*> nodes;
	for (Node& n : vertical(*_node)) {
		nodes.push_back(&n);
	}
	for (Node* n : nodes) {
		delete n;
	}
	delete _node;
}
ColumnNode* ColumnNode::insertRight(int id) {
	ColumnNode* cn = new ColumnNode(id);
	_node->insertRight(cn->_node);
	return cn;
}
Node* ColumnNode::insertBelow() {
	Node* n = new Node(this);
	_node->insertBelow(n);
	_count++;
	return n;
}
void ColumnNode::cover() {
#if DEBUG
std::cout << " Covering ColumnNode " << *this << " of size " << _count << std::endl;
#endif
	_node->remove();
	for (Node& row : vertical(*_node)) {
		for (Node& n : row) {
			n.cover();
			assert(_count > 0);
			n.head()->_count--;
#if DEBUG
std::cout << "  Covering node of column " << *n.head() << "; decrementing count to " << n.head()->_count << std::endl;
#endif
		}
	}
}
void ColumnNode::uncover() {
#if DEBUG
std::cout << "Uncovering ColumnNode " << *this << " of size " << _count << std::endl;
#endif
	for (Node& row : reverse(vertical(*_node))) {
		for (Node& n : reverse(row)) {
			n.uncover();
			n.head()->_count++;
		}
	}
	_node->restore();
}
bool ColumnNode::operator<(const ColumnNode& rhs) const {
	return _count < rhs._count;
}
ostream& operator<<(ostream& out, const ColumnNode& cn) {
	return out << cn._id;
}

ColumnRightIter ColumnNode::begin() {
	return ColumnRightIter(_node->begin()->head());
}
ColumnRightIter ColumnNode::end() {
	return ColumnRightIter(this);
}
ColumnDownIter ColumnNode::vbegin() {
	return ColumnDownIter(&*_node->vbegin());
}
ColumnDownIter ColumnNode::vend() {
	return ColumnDownIter(_node);
}

bool ColumnRightIter::operator==(const ColumnRightIter& rhs) const {
	return cur == rhs.cur;
}
bool ColumnRightIter::operator!=(const ColumnRightIter& rhs) const {
	return !(*this == rhs);
}
ColumnRightIter& ColumnRightIter::operator++() {
	cur = cur->_node->begin()->head();
	return *this;
}
ColumnRightIter ColumnRightIter::operator++(int) {
	ColumnRightIter clone(*this);
	++(*this);
	return clone;
}
ColumnNode& ColumnRightIter::operator*() {
	return *cur;
}

bool ColumnDownIter::operator==(const ColumnDownIter& rhs) const {
	return cur == rhs.cur;
}
bool ColumnDownIter::operator!=(const ColumnDownIter& rhs) const {
	return !(*this == rhs);
}
ColumnDownIter& ColumnDownIter::operator++() {
	cur = &*cur->vbegin();
	return *this;
}
ColumnDownIter ColumnDownIter::operator++(int) {
	ColumnDownIter clone(*this);
	++(*this);
	return clone;
}
Node& ColumnDownIter::operator*() {
	return *cur;
}
/*
// Unit test
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
int main() {
	ColumnNode root(-1);
	for (int i = 0; i < 3; i++) {
		root.insertRight(i);
	}
	int j = 1;
	for (auto& cn : root) {
		for (int i = 0; i < j; i++) {
			cn.insertBelow();
		}
		j++;
	}
	// Iterate right from root.
	for (auto& cn : root) {
		cout << cn << endl;
	}
	// Iterate down from first column.
	ColumnNode& min = *std::min_element(root.begin(), root.end());
	cout << "Minimum column " << min << " has nodes:" << endl;
	for (auto& n : vertical(min)) {
		cout << &n << endl;
	}
	// Iterate down from last column.
	ColumnNode& max = *std::max_element(root.begin(), root.end());
	cout << "Maximum column " << max << " has nodes:" << endl;
	for (auto& n : vertical(max)) {
		cout << &n << endl;
	}
	// Remove first and last column.
	min.cover();
	max.cover();
	cout << "Middle columns are:" << endl;
	for (auto& cn : root) {
		cout << cn << endl;
	}
	// Restore last column.
	max.uncover();
	cout << "Non-first columns are:" << endl;
	for (auto& cn : root) {
		cout << cn << endl;
	}
	return 0;
}
*/
