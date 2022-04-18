#include "Node.h"

Node::Node() {
	balance = 0;
	left = right = parent = nullptr;
}

Node::Node(std::string key, unsigned long long value, Node* parent) {
	Node::Node();
	this->key = key;
	this->value = value;
	this->parent = parent;
}

short Node::get_balance() {
	return balance;
}

void Node::set_balance(short balance) {
	this->balance = balance;
}

std::string Node::get_key() {
	return key;
}

void Node::set_key(std::string key) {
	this->key = key;
}

Node* Node::get_left() {
	return left;
}

void Node::set_left(Node* left) {
	this->left = left;
}

Node* Node::get_parent() {
	return parent;
}

void Node::set_parent(Node* parent) {
	this->parent = parent;
}

Node* Node::get_right() {
	return right;
}

void Node::set_right(Node* right) {
	this->right = right;
}

unsigned long long Node::get_value() {
	return value;
}

void Node::set_value(unsigned long long value) {
	this->value = value;
}

Node::~Node() {}