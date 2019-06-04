#include "node.hpp" // Node

ColumnNode* Node::head() const {
	return _head;
}
void Node::remove() {
	_right->_left = _left;
	_left->_right = _right;
}
void Node::restore() {
	_right->_left = this;
	_left->_right = this;
}
void Node::cover() {
	_up->_down = _down;
	_down->_up = _up;
}
void Node::uncover() {
	_up->_down = this;
	_down->_up = this;
}
void Node::insertBelow(Node* n) {
	n->_up = this;
	_down->_up = n;
	n->_down = _down;
	_down = n;
}
void Node::insertRight(Node* n) {
	n->_left = this;
	_right->_left = n;
	n->_right = _right;
	_right = n;
}
bool Node::operator==(const Node& rhs) const {
	return _left == rhs._left && _right == rhs._right && _up == rhs._up
		&& _down == rhs._down && _head == rhs._head;
}
bool Node::operator!=(const Node& rhs) const {
	return !(*this == rhs);
}
NodeRightIter Node::begin() {
	return NodeRightIter(this->_right);
}
NodeRightIter Node::end() {
	return NodeRightIter(this);
}
NodeDownIter Node::vbegin() {
	return NodeDownIter(this->_down);
}
NodeDownIter Node::vend() {
	return NodeDownIter(this);
}

bool NodeRightIter::operator==(const NodeRightIter& rhs) const {
	return cur == rhs.cur;
}
bool NodeRightIter::operator!=(const NodeRightIter& rhs) const {
	return !(*this == rhs);
}
Node* NodeRightIter::operator->() {
	return &**this;
}
NodeRightIter& NodeRightIter::operator++() {
	cur = cur->_right;
	return *this;
}
NodeRightIter NodeRightIter::operator++(int) {
	NodeRightIter clone(*this);
	++(*this);
	return clone;
}
NodeRightIter& NodeRightIter::operator--() {
	cur = cur->_left;
	return *this;
}
NodeRightIter NodeRightIter::operator--(int) {
	NodeRightIter clone(*this);
	--(*this);
	return clone;
}
Node& NodeRightIter::operator*() {
	return *cur;
}

bool NodeDownIter::operator==(const NodeDownIter& rhs) const {
	return cur == rhs.cur;
}
bool NodeDownIter::operator!=(const NodeDownIter& rhs) const {
	return !(*this == rhs);
}
Node* NodeDownIter::operator->() {
	return &**this;
}
NodeDownIter& NodeDownIter::operator++() {
	cur = cur->_down;
	return *this;
}
NodeDownIter NodeDownIter::operator++(int) {
	NodeDownIter clone(*this);
	++(*this);
	return clone;
}
NodeDownIter& NodeDownIter::operator--() {
	cur = cur->_up;
	return *this;
}
NodeDownIter NodeDownIter::operator--(int) {
	NodeDownIter clone(*this);
	--(*this);
	return clone;
}
Node& NodeDownIter::operator*() {
	return *cur;
}
