#include <string>
#include <iostream>

class Node {
private:
	short balance;
	std::string key;
	unsigned long long value;
	Node *left, *right, *parent;
public:
	Node();
	Node(std::string, unsigned long long, Node*);
	short get_balance();
	void set_balance(short);
	std::string get_key();
	void set_key(std::string);
	Node* get_left();
	void set_left(Node*);
	Node* get_parent();
	void set_parent(Node*);
	Node* get_right();
	void set_right(Node*);
	unsigned long long get_value();
	void set_value(unsigned long long);
	~Node();
};


