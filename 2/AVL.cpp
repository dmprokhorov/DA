#include "AVL.h"

AVL::AVL() {
	root = nullptr;
}

void AVL::begin_of_search(std::string key) {
	if (!root) {
		std::cout << "NoSuchWord\n";
		return;
	}
	Node* result = search(root, key);
	if (!result) {
		std::cout << "NoSuchWord\n";
	}
	else {
		std::cout << "OK: " << result->get_value() << "\n";
	}
}

Node* AVL::min_in_right_subtree(Node* node) {
	while (node->get_left()) {
		node = node->get_left();
	}
	return node;
}

void AVL::remove(std::string key) {
	if (!root) {
		std::cout << "NoSuchWord\n";
		return;
	}
	Node* result = search(root, key);
	if (!result) {
		std::cout << "NoSuchWord\n";
	}
	else {
		Node* parent = result->get_parent();
		if ((!result->get_left()) && (!result->get_right())) {
			if (parent) {
				result->set_parent(nullptr);
				if (parent->get_left() == result) {
					parent->set_balance(parent->get_balance() - 1);
					parent->set_left(nullptr);
				}
				else {
					parent->set_balance(parent->get_balance() + 1);
					parent->set_right(nullptr);
				}
				balancing(parent, false);
			}
			else {
				root = nullptr;
				std::cout << "OK\n";
			}
			delete result;
		}
		else if (!result->get_right()) {
			Node* left = result->get_left();
			left->set_parent(nullptr);
			result->set_key(left->get_key());
			result->set_value(left->get_value());
			result->set_balance(result->get_balance() - 1);
			result->set_left(nullptr);
			delete left;
			balancing(result, false);
		}
		else {
			Node* min = min_in_right_subtree(result->get_right()), *parent_min = min->get_parent(), *right_min = min->get_right();
			result->set_key(min->get_key());
			result->set_value(min->get_value());
			if (parent_min == result) {
				parent_min->set_right(right_min);
				parent_min->set_balance(parent_min->get_balance() + 1);
			}
			else {
				parent_min->set_left(right_min);
				parent_min->set_balance(parent_min->get_balance() - 1);				
			}
			if (right_min) {
				right_min->set_parent(parent_min);
			}
			min->set_right(nullptr);
			min->set_parent(nullptr);
			delete min;
			balancing(parent_min, false);
		}
	}
}

Node* AVL::search(Node* node, std::string key) {
	if (!node) {
		return nullptr;
	}
	std::string node_key = node->get_key();
	if (node_key == key) {
		return node;
	}
	else if (node_key > key) {
		return search(node->get_left(), key);
	}
	else {
		return search(node->get_right(), key);
	}
}

void AVL::insert(std::string key, unsigned long long value) {
	if (!root) {
		root = new Node(key, value, nullptr);
		std::cout << "OK\n";
	}
	else {
		search_place(root, key, value);
	}
}

void AVL::search_place(Node* current, std::string key, unsigned long long value) {
	std::string node_key = current->get_key();
	if (node_key == key) {
		std::cout << "Exist\n";
		return;
	}
	else if (node_key > key) {
		Node* left = current->get_left();
		if (!left) {
			left = new Node(key, value, current);
			Node* parent = left->get_parent();
			parent->set_left(left);
			parent->set_balance(parent->get_balance() + 1);
			balancing(parent, true);
			return;
		}
		else {
			search_place(left, key, value);
		}
	}
	else {
		Node* right = current->get_right();
		if (!right) {
			right = new Node(key, value, current);
			Node* parent = right->get_parent();
			parent->set_right(right);
			parent->set_balance(parent->get_balance() - 1);
			balancing(parent, true);
			return;
		}
		else {
			search_place(right, key, value);
		}
	}
}

void AVL::rotate_left(Node* x) {
	Node* y = x->get_right(), * a = y->get_left();
	Node* x_parent = x->get_parent();
	if (!x_parent) {
		root = y;
	}
	y->set_parent(x_parent);
	if (x_parent) {
		if (x_parent->get_left() == x) {
			x_parent->set_left(y);
		}
		else {
			x_parent->set_right(y);
		}
	}
	if (a) {
		a->set_parent(x);
	}
	x->set_right(a);
	y->set_left(x);
	x->set_parent(y);
}

void AVL::rotate_right(Node* x) {
	Node* y = x->get_left(), *b = y->get_right();
	Node* x_parent = x->get_parent();
	if (!x_parent) {
		root = y;
	}
	y->set_parent(x_parent);
	if (x_parent) {
		if (x_parent->get_left() == x) {
			x_parent->set_left(y);
		}
		else {
			x_parent->set_right(y);
		}
	}
	if (b) {
		b->set_parent(x);
	}
	x->set_left(b);
	y->set_right(x);
	x->set_parent(y);
}

void AVL::balancing(Node* x, bool insert) {
	short x_balance = x->get_balance();
	while ((x) && (((insert) && (x_balance != 0)) || ((!insert) && ((x_balance == -2) || (!x_balance) || (x_balance == 2))))) {
		if ((x) && ((x_balance >= -1) && (x_balance <= 1))) {
			Node* parent = x->get_parent();
			if (parent) {
				if (((insert) && (parent->get_left() == x)) || ((!insert) && (parent->get_right() == x))) {
					parent->set_balance(parent->get_balance() + 1);
				}
				else if (((!insert) && (parent->get_left() == x)) || ((insert) && (parent->get_right() == x))) {
					parent->set_balance(parent->get_balance() - 1);
				}
			}
			x = parent;
			if (x) {
				x_balance = x->get_balance();
			}
		}
		else if (x_balance == 2) {
			Node* y = x->get_left();
			short y_balance = y->get_balance();
			if (y_balance >= 0) {
				if (y_balance == 1) {
					x->set_balance(0);
					y->set_balance(0);
					x_balance = 0;
				}
				else {
					x->set_balance(1);
					y->set_balance(-1);
					x_balance = -1;
				}
			}
			else {
				Node* z = y->get_right();
				short z_balance = z->get_balance();
				x_balance = 0;
				if (z_balance == -1) {
					x->set_balance(0);
					y->set_balance(1);
				}
				else if (!z_balance) {
					x->set_balance(0);
					y->set_balance(0);
				}
				else {
					x->set_balance(-1);
					y->set_balance(0);
				}
				z->set_balance(0);
				rotate_left(y);
			}
			rotate_right(x);
			x = x->get_parent();
		}
		else {
			Node* y = x->get_right();
			short y_balance = y->get_balance();
			if (y_balance <= 0) {
				if (y_balance == -1) {
					x->set_balance(0);
					y->set_balance(0);
					x_balance = 0;
				}
				else {
					x->set_balance(-1);
					y->set_balance(1);
					x_balance = 1;
				}
			}
			else {
				Node* z = y->get_left();
				short z_balance = z->get_balance();
				x_balance = 0;
				if (z_balance == -1) {
					x->set_balance(1);
					y->set_balance(0);
				}
				else if (!z_balance) {
					x->set_balance(0);
					y->set_balance(0);
				}
				else {
					x->set_balance(0);
					y->set_balance(-1);
				}
				z->set_balance(0);
				rotate_right(y);
			}
			rotate_left(x);
			x = x->get_parent();
		}
	}
	std::cout << "OK\n";
}

void AVL::begin_of_clearing() {
	clear(root);
}

void AVL::clear(Node* node) {
	if (!node) {
		return;
	}
	clear(node->get_left());
	clear(node->get_right());
	node->set_left(nullptr);
	node->set_right(nullptr);
	node->set_parent(nullptr);
	delete node;
}

AVL::~AVL() {}

