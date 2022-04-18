#include <iostream>
#include "AVL.h"
#include <fstream>

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
        else {
            tree.begin_of_search(to_lower(command));
        }
    }
    tree.begin_of_clearing();
    system("pause");
    return 0;
}
