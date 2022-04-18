#include "Node.h"

class AVL {
private:
	Node* root;
public:
	AVL();
	void begin_of_search(std::string);
	void balancing(Node*, bool);
	void begin_of_clearing();
	void clear(Node*);
	void insert(std::string, unsigned long long);
	Node* min_in_right_subtree(Node*);
	void remove(std::string);
	void rotate_left(Node*);
	void rotate_right(Node*);
	Node* search(Node*, std::string);
	void search_place(Node*, std::string, unsigned long long);
	~AVL();
};
