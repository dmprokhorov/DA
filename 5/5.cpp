// 5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <map>

std::string string;
int n;
int m;

class TVertice {
public:

    TVertice(TVertice* parent, int first, int second) {
        indices = { first, second };
        suffix_link = nullptr;
        reverced = nullptr;
        this->parent = parent;
    }

    std::map<char, TVertice*> letters;
    std::vector<int> indices;
    TVertice* suffix_link;
    TVertice* reverced;
    TVertice* parent;
};

class TTrie {
public:

    TTrie(int second) {
        root = new TVertice(nullptr, 0, second);
    }

    TVertice* build(TVertice* vertice, int first, int current) {
        TVertice* new_vertice = new TVertice(vertice, first, current - 1);
        TVertice* child = vertice->letters[string[first]];
        vertice->letters[string[first]] = new_vertice;
        child->indices[0] = current;
        child->parent = new_vertice;
        new_vertice->letters = { {string[current], child} };
        return new_vertice;
    }

    TVertice* get(TVertice* begin, int first, int second) {
        if (begin == root) {
            return begin;
        }
        if (begin->suffix_link) {
            return begin->suffix_link;
        }
        if (begin->parent == root) {
            ++first;
            begin = root;
        }
        else {
            begin = begin->parent->suffix_link;
        }
        int current = 0;
        while (first <= second) {
            TVertice* child = begin->letters[string[first]];
            int left = child->indices[0];
            int right = child->indices[1];
            if (right - left <= second - first) {
                first += right - left + 1;
                begin = child;
            }
            else {
                current = left + second - first + 1;
                first = left;
                second = right;
                break;
            }
        }
        if (first >= second + 1) {
            return begin;
        }
        return build(begin, first, current);
    }

    int dfs(TVertice* vertice, std::string current, int& max, std::vector<std::string>& answer) {
        if (!vertice->letters.size()) {
            if (vertice->indices[0] <= n) {
                return 0;
            }
            return 1;
        }
        current += string.substr(vertice->indices[0], vertice->indices[1] - vertice->indices[0] + 1);
        std::vector<bool> children = { false, false };
        for (std::map<char, TVertice*>::iterator iterator = vertice->letters.begin(); iterator != vertice->letters.end(); ++iterator) {
            int value = dfs(iterator->second, current, max, answer);
            if (value == 2) {
                children = { true, true };
            }
            else {
                children[value] = true;
            }
        }
        if ((children[0]) && (children[1])) {
            int length = current.length();
            if (length > max) {
                max = length;
                answer.clear();
                answer = { current };
            }
            else if (length == max) {
                answer.push_back(current);
            }
            return 2;
        }
        else if (children[0]) {
            return 0;
        }
        return 1;
    }

    void clear(TVertice* vertice) {
        for (std::map<char, TVertice*>::iterator iterator = vertice->letters.begin(); iterator != vertice->letters.end(); ++iterator) {
            clear(iterator->second);
        }
        vertice->parent = nullptr;
        if (vertice->reverced) {
            vertice->reverced->suffix_link = nullptr;
            vertice->reverced = nullptr;
        }
        vertice->suffix_link = nullptr;
        delete vertice;
    }

    TVertice* root;
};

int main()
{
    std::string string1;
    std::string string2;
    std::cin >> string1 >> string2;
    string1 += ('z' + 1);
    n = string1.size();
    string2 += ('z' + 2);
    m = string2.size();
    unsigned size = n + m;
    string = string1 + string2;
    TTrie trie(-1);
    TVertice* vertice = trie.root;
    int first = -1;
    int current = -1;
    int second = -1;
    for (unsigned i = 0; i < size; ++i) {
        if (first == -1) {
            if (vertice->letters.find(string[i]) != vertice->letters.end()) {
                TVertice* child = vertice->letters[string[i]];
                first = child->indices[0];
                current = first + 1;
                second = child->indices[1];
                if (current > second) {
                    vertice = vertice->letters[string[first]];
                    first = -1;
                    second = -1;
                    current = -1;
                }
            }
            else {
                 while (true) {
                    TVertice* next = trie.get(vertice, first, second);
                    if (vertice->letters.find(string[i]) == vertice->letters.end()) {
                        vertice->letters[string[i]] = new TVertice(vertice, i, size - 1);
                    }
                    else {
                        first = vertice->letters[string[i]]->indices[0];
                        current = first + 1;
                        second = vertice->letters[string[i]]->indices[1];
                        if (current > second) {
                            vertice = vertice->letters[string[first]];
                            first = -1;
                            second = -1;
                            current = -1;
                        }
                        break;
                    }
                    if (vertice == trie.root) {
                        break;
                    }
                    vertice = next;
                 }
            }
        }
        else {
            if (string[current] == string[i]) {
                ++current;
                if (current > second) {
                    vertice = vertice->letters[string[first]];
                    first = -1;
                    second = -1;
                    current = -1;
                }
            }
            else {
                vertice = trie.build(vertice, first, current);
                while (true) {
                    first = vertice->indices[0];
                    current = first + 1;
                    second = vertice->indices[1];
                    TVertice* next = trie.get(vertice, first, second);
                    if (vertice != trie.root) {
                        vertice->suffix_link = next;
                        next->reverced = vertice;
                    }
                    if (vertice->letters.find(string[i]) == vertice->letters.end()) {
                        vertice->letters[string[i]] = new TVertice(vertice, i, size - 1);
                    }
                    else {
                        first = vertice->letters[string[i]]->indices[0];
                        current = first + 1;
                        second = vertice->letters[string[i]]->indices[1];
                        if (current > second) {
                            vertice = vertice->letters[string[first]];
                            first = -1;
                            second = -1;
                            current = -1;
                        }
                        break;
                    }
                    if (vertice == trie.root) {
                        first = -1;
                        second = -1;
                        current = -1;
                        break;
                    }
                    vertice = next;
                }
            }
        }
    }
    int max = 0;
    std::vector<std::string> answer;
    trie.dfs(trie.root, std::string(), max, answer);
    std::cout << max << "\n";
    for (unsigned i = 0; i < answer.size(); ++i) {
        std::cout << answer[i] << "\n";
    }
    trie.clear(trie.root);
    return 0;
}
