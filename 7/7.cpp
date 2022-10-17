// 7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <queue>

class TData {
public:
    unsigned long long sum;
    unsigned short operation;
};

int main()
{
    unsigned n;
    std::cin >> n;
    std::vector<TData> data(n + 1);
    data[1] = { 0, 0 };
    for (unsigned i = 2; i < n + 1; ++i) {
        data[i] = { data[i - 1].sum + i, 1 };
        if ((!(i % 2)) && (data[i / 2].sum + i < data[i].sum)) {
            data[i] = { data[i / 2].sum + i, 2 };
        }
        if ((!(i % 3)) && (data[i / 3].sum + i < data[i].sum)) {
            data[i] = { data[i / 3].sum + i, 3 };
        }
    }
    std::queue<unsigned short> way;
    unsigned current = n;
    while (current > 1) {
        unsigned short operation = data[current].operation;
        way.emplace(operation);
        if (operation == 1) {
            --current;
        }
        else {
            current /= operation;
        }
    }
    std::cout << data[n].sum << "\n";
    while (way.size()) {
        unsigned short operation = way.front();
        if (operation == 1) {
            std::cout << "-";
        }
        else {
            std::cout << "/";
        }
        std::cout << operation << " ";
        way.pop();
    }
    std::cout << "\n";
    system("pause");
    return 0;
}


