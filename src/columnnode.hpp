#pragma once
#include "node.hpp" // Node

class ColumnRightIter;
class ColumnDownIter;

class ColumnNode {
public:
	// ColumnNodes cannot be default constructed. They must have an id.
	ColumnNode() = delete;
	ColumnNode(int id) : _id(id) {}
	// ColumnNodes cannot be copied or assigned to. They are immutable.
	ColumnNode(const ColumnNode&) = delete;
	ColumnNode& operator=(const ColumnNode&) = delete;
	// ColumnNodes cannot be inherited from.
	~ColumnNode();
	// Insert a new ColumnNode in this row and return a pointer to it.
	ColumnNode* insertRight(int id);
	// Insert a new node in this column and return a pointer to it.
	Node* insertBelow();
	// Disconnect all nodes in this column and all nodes in their rows.
	void cover();
	// Reconnect all nodes in this column and all nodes in their rows.
	void uncover();
	// The numeric identifier for the column.
	int id() const;
	// Comparison operator for finding the column with the fewest nodes.
	bool operator<(const ColumnNode& rhs) const;
	// Ostream operator for printing the id of the column.
	friend std::ostream& operator<<(std::ostream& out, const ColumnNode& cn);
	// Horizontal and vertical iterators. Note that iteration skips over this column.
	friend class ColumnRightIter;
	friend class ColumnDownIter;
	using iterator = ColumnRightIter;
	using vertical_iterator = ColumnDownIter;
	iterator begin();
	iterator end();
	vertical_iterator vbegin();
	vertical_iterator vend();

private:
	// A unique identifier to use as the name for this column.
	const int _id;
	// A node to link this column to the rest of the node matrix.
	Node* _node = new Node(this);
	// The number of nodes in the column, excluding the head.
	int _count = 0;
};

class ColumnRightIter {
public:
	using value_type = ColumnNode;
	using pointer = value_type*;
	using reference = value_type&;
	using difference_type = ptrdiff_t;
	using iterator_category = std::forward_iterator_tag;

	ColumnRightIter() = default;
	ColumnRightIter(ColumnNode* n) : cur(n) {}
	ColumnRightIter(const ColumnRightIter&) = default;
	~ColumnRightIter() = default;
	ColumnRightIter& operator=(const ColumnRightIter&) = default;
	bool operator==(const ColumnRightIter& rhs) const;
	bool operator!=(const ColumnRightIter& rhs) const;
	ColumnRightIter& operator++();
	ColumnRightIter operator++(int);
	ColumnNode& operator*();
private:
	ColumnNode* cur;
};

class ColumnDownIter {
public:
	using value_type = Node;
	using pointer = value_type*;
	using reference = value_type&;
	using difference_type = ptrdiff_t;
	using iterator_category = std::forward_iterator_tag;

	ColumnDownIter() = default;
	ColumnDownIter(Node* n) : cur(n) {}
	ColumnDownIter(const ColumnDownIter&) = default;
	~ColumnDownIter() = default;
	ColumnDownIter& operator=(const ColumnDownIter&) = default;
	bool operator==(const ColumnDownIter& rhs) const;
	bool operator!=(const ColumnDownIter& rhs) const;
	ColumnDownIter& operator++();
	ColumnDownIter operator++(int);
	Node& operator*();
private:
	Node* cur;
};
