#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

void Tolower(std::string& string) {
    unsigned short n = string.length();
    for (unsigned short i = 0; i < n; ++i) {
        string[i] = std::tolower(string[i]);
    }
}

std::vector<std::string> Reverse(std::vector<std::string>& vector) {
    std::vector<std::string> reversed(vector);
    std::reverse(reversed.begin(), reversed.end());
    return reversed;
}

std::vector<unsigned> Z(std::vector<std::string>& vector) {
    unsigned n = vector.size();
    unsigned l = 0;
    unsigned r = 0;
    std::vector<unsigned > z(n, 0);
    for (unsigned i = 1; i < n; ++i) {
        if (r >= i) {
            z[i] = std::min(z[i - l], r - i + 1);
        }
        while ((z[i] + i < n) && (vector[z[i]] == vector[z[i] + i])) {
            ++z[i];
        }
        if (r < i + z[i] - 1) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main()
{
    std::string first = std::string();
    std::getline(std::cin, first);
    std::stringstream ss(first);
    std::string word;
    std::map<std::string, std::vector<unsigned>> symbols;
    std::vector<std::string> pattern;
    unsigned counter = 0;
    while (ss >> word) {
        Tolower(word);
        pattern.push_back(word);
        if (symbols.find(word) != symbols.end()) {
            symbols[word].push_back(counter);
        }
        else {
            symbols[word] = {counter};
        }
        ++counter;
    }
    unsigned m = counter;
    std::vector<unsigned> shifts(m);
    std::vector<std::string> reversed = Reverse(pattern);
    std::vector<unsigned> z = Z(reversed);
    for (int i = m - 1; i >= 0; --i) {
        if (z[i]) {
            shifts[m - z[i]] = i;
        }
    }
    z = Z(pattern);
    for (int i = m - 1; i >= 0; --i) {
        if (i + z[i] == m) {
            unsigned index = i;
            while (i >= 0) {
                if (z[i]) {
                    index = i;
                }
                if (!shifts[i]) {
                    shifts[i] = index;
                }
                --i;
            }
        }
        else if (!shifts[i]) {
            shifts[i] = m;
        }
    }
    counter = 0;
    ss.str(std::string());
    ss.clear();
    std::vector<unsigned> amount;
    unsigned size = 0;
    unsigned n = 0;
    int line = -1;
    std::vector<std::string> text;
    std::string another;
    while (std::getline(std::cin, another)) {
        ss.str(another);
        while (ss >> word) { 
            Tolower(word);
            text.push_back(word);
            ++counter;
            ++n;
        }
        amount.push_back(counter);
        if ((line == -1) && (counter)) {
            line = size;
        }
        ++size;
        counter = 0;
        ss.str(std::string());
        ss.clear();
    }
    std::vector<std::pair<unsigned, unsigned>> answers;
    unsigned symbol = 0;
    for (unsigned i = m - 1; i < n; ++i) {
        unsigned j = m - 1;
        unsigned begin = i;
        while (text[i] == pattern[j]) {
            if (!j) {
                answers.push_back({line + 1, symbol + 1});
                j = m;
                break;
            }
            --i;
            --j;
        }
        unsigned bad = 1;
        unsigned good = 1;
        if (j != m) {
            if (symbols.find(text[i]) != symbols.end()) {
                std::vector<unsigned> indexes = symbols[text[i]];
                std::vector<unsigned>::iterator position = std::lower_bound(indexes.begin(), indexes.end(), j);
                if (position != indexes.begin()) {
                    bad = j - indexes[position - indexes.begin() - 1];
                }
                else {
                    bad = j + 1;
                }
            }
            else {
                bad = j + 1;
            }
            if (j != m - 1) {
                good = shifts[j + 1];
            }
        }
        else {
            good = shifts[0];
        }
        unsigned shift = std::max(bad, good);
        i = begin;
        while ((line < size) && (amount[line] - symbol < shift + 1)) {
            i += amount[line] - symbol;
            shift -= amount[line] - symbol;
            ++line;
            symbol = 0;          
        }
        if ((line < size) && (shift)) {
            symbol += shift;
            i += shift;
        }
        --i;
    }
    size = answers.size();
    for (unsigned i = 0; i < size; ++i) {
        std::cout << answers[i].first << ", " << answers[i].second << "\n";
    }
    return 0;
}
