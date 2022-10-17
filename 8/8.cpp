// 8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <vector>
#include <algorithm>

class TData {
public:
	std::vector<double> c;
	unsigned price;
	unsigned index;
};

unsigned N, M;
std::vector<TData> matrix;

std::pair<bool, std::vector<unsigned>> Array() {
	std::vector<unsigned> result;
	for (unsigned i = 0; i < N; ++i) {
		int index = -1;
		double min = 51.;
		for (unsigned j = i; j < M; ++j) {
			if ((matrix[j].c[i]) && (matrix[j].price < min)) {
				index = j;
				min = matrix[j].price;
			}
		}
		if (index == -1) {
			result.clear();
			return { false, result };
		}
		std::swap(matrix[i], matrix[index]);
		result.push_back(matrix[i].index);
		for (unsigned j = i + 1; j < M; ++j) {
			double coefficient = matrix[j].c[i] / matrix[i].c[i];
			matrix[j].c[i] = 0.;
			for (unsigned k = i + 1; k < N; ++k) {
				matrix[j].c[k] -= coefficient * matrix[i].c[k];
			}
		}
	}
	return { true, result };
}

int main() {
	std::cin >> M >> N;
	matrix.resize(M);
	for (unsigned i = 0; i < M; ++i) {
		matrix[i].c = std::vector<double>(N);
		for (unsigned j = 0; j < N; ++j) {
			std::cin >> matrix[i].c[j];
		}
		std::cin >> matrix[i].price;
		matrix[i].index = i + 1;
	}
	std::pair<bool, std::vector<unsigned>> data = Array();
	bool possible = data.first;
	std::vector<unsigned> result = data.second;
	std::sort(result.begin(), result.end());
	unsigned size = result.size();
	if (!possible) {
		std::cout << "-1";
	}
	for (unsigned i = 0; i < size; ++i) {
		std::cout << result[i] << " ";
	}
	std::cout << "\n";
	system("pause");
	return 0;
}


