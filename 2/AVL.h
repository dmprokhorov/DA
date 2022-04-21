#include "Node.h"

class AVL {
private:
	Node* root;
public:
	AVL();
	void begin_of_search(std::string);
	void balancing(Node*, bool);
	void begin_of_clearing();
	void begin_of_reading(std::string);
	void begin_of_writing(std::string);
	//void build_tree(Node*, Node*);
	void clear(Node*);
	Node* get_root();
	void insert(std::string, unsigned long long);
	Node* min_in_right_subtree(Node*);
	//void operator=(AVL&);
	void reading(Node*, std::ifstream&, bool);
	void remove(std::string);
	void rotate_left(Node*);
	void rotate_right(Node*);
	Node* search(Node*, std::string);
	void search_place(Node*, std::string, unsigned long long);
	void set_root();
        void writing(Node*, std::ofstream&);
	~AVL();
};
