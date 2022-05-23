#include <iostream>
#include "AVL.h"

std::string to_lower(std::string& string) {
    for (unsigned i = 0; i < string.length(); ++i) {
        string[i] = std::tolower(string[i]);
    }
    return string;
}

int main()
{
    AVL tree;
    std::string command;
    while (std::cin >> command) {
        std::string key;
        unsigned long long value;
        if (command == "+") {
            std::cin >> key >> value;
            tree.insert(to_lower(key), value);
        }
        else if (command == "-") {
            std::cin >> key;
            tree.remove(to_lower(key));
        }
        else if (command == "!") {
            std::cin >> key;
            if (key == "Save") {
                std::string path;
                std::cin >> path;
                tree.begin_of_writing(path);
            }
            else if (key == "Load") {
                AVL copy;
                std::string path;
                std::cin >> path;
		tree.clear(tree.get_root());
		tree.set_root();
		tree.begin_of_reading(path);
            }
	    std::cout << "OK\n";
        }
        else {
            tree.begin_of_search(to_lower(command));
        }
    }
    tree.clear(tree.get_root());
    return 0;
}
