#pragma once
#include "state.hpp" // State

class ColumnNode;
class NodeRightIter;
class NodeDownIter;

class Node {
public:
	// Nodes cannot be default constructed. They must have a ColumnNode.
	Node() = delete;
	Node(ColumnNode* cn) : _head(cn) {}
	// Nodes cannot be copied or assigned to. They are immutable.
	Node(const Node&) = delete;
	Node& operator=(const Node&) = delete;
	// Nodes cannot be inherited from.
	~Node() = default;
	// Return a pointer to the head of the column this node is in.
	ColumnNode* head() const;
	// Disconnect this node from its right and left neighbors.
	void remove();
	// Reconnect this node to its right and left neighbors.
	void restore();
	// Disconnect this node from its top and bottom neighbors.
	void cover();
	// Reconnect this node to its top and bottom neighbors.
	void uncover();
	// Permanently connect this node above the given node.
	void insertBelow(Node* n);
	// Permanently connect this node left of the given node.
	void insertRight(Node* n);
	// Comparison operators.
	bool operator==(const Node& rhs) const;
	bool operator!=(const Node& rhs) const;
	// Horizontal and vertical iterators. Note that iteration skips over this node.
	friend class NodeRightIter;
	friend class NodeDownIter;
	using iterator = NodeRightIter;
	using vertical_iterator = NodeDownIter;
	iterator begin();
	iterator end();
	vertical_iterator vbegin();
	vertical_iterator vend();

private:
	Node* _left = this;
	Node* _right = this;
	Node* _up = this;
	Node* _down = this;
	ColumnNode* const _head = nullptr;
};

class NodeRightIter {
public:
	using value_type = Node;
	using pointer = value_type*;
	using reference = value_type&;
	using difference_type = ptrdiff_t;
	using iterator_category = std::bidirectional_iterator_tag;

	NodeRightIter() = default;
	NodeRightIter(Node* n) : cur(n) {}
	NodeRightIter(const NodeRightIter&) = default;
	~NodeRightIter() = default;
	NodeRightIter& operator=(const NodeRightIter&) = default;
	bool operator==(const NodeRightIter& rhs) const;
	bool operator!=(const NodeRightIter& rhs) const;
	Node* operator->();
	NodeRightIter& operator++();
	NodeRightIter operator++(int);
	NodeRightIter& operator--();
	NodeRightIter operator--(int);
	Node& operator*();
private:
	Node* cur;
};

class NodeDownIter {
public:
	using value_type = Node;
	using pointer = value_type*;
	using reference = value_type&;
	using difference_type = ptrdiff_t;
	using iterator_category = std::bidirectional_iterator_tag;

	NodeDownIter() = default;
	NodeDownIter(Node* n) : cur(n) {}
	NodeDownIter(const NodeDownIter&) = default;
	~NodeDownIter() = default;
	NodeDownIter& operator=(const NodeDownIter&) = default;
	bool operator==(const NodeDownIter& rhs) const;
	bool operator!=(const NodeDownIter& rhs) const;
	Node* operator->();
	NodeDownIter& operator++();
	NodeDownIter operator++(int);
	NodeDownIter& operator--();
	NodeDownIter operator--(int);
	Node& operator*();
private:
	Node* cur;
};
