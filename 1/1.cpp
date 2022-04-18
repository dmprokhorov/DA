// 1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

struct TData {
	unsigned long long keys[2], value;
};

void Radixsort(std::vector<TData>& arr) {
	std::vector<unsigned long long> digits(256);
	std::vector<TData> aux(arr);
	unsigned long long n = arr.size();
	unsigned long long delimiter;
	for (long long l = 1; l >= 0; --l) {
		delimiter = 255;
		for (unsigned long long i = 0; i < 8; ++i) {
			std::fill(digits.begin(), digits.end(), 0);
			for (unsigned long long j = 0; j < n; ++j) {
				++digits[(arr[j].keys[l] & delimiter) >> 8 * i];
			}
			for (unsigned long long j = 1; j < 256; ++j) {
				digits[j] += digits[j - 1];
			}
			for (long long j = n - 1; j >= 0; --j) {
				unsigned long long index = (arr[j].keys[l] & delimiter) >> 8 * i;
				aux[digits[index] - 1] = arr[j];
				--digits[index];
			}
			arr = aux;
			delimiter <<= 8;
		}
	}
}

int main() {
	std::vector<TData> arr;
	std::string keys;
	unsigned long long value, key1, key2;
	while (std::cin >> keys >> value) {
		arr.push_back({ {std::stoull(keys.substr(0, 16), 0, 16), std::stoull(keys.substr(16, 16), 0, 16)}, value });
	}
	Radixsort(arr);
	for (unsigned long long i = 0; i < arr.size(); ++i) {
		std::cout << std::hex << std::setw(16) << std::setfill('0') << arr[i].keys[0] << std::setw(16) << std::setfill('0') << arr[i].keys[1] << "\t"
			<< std::dec << arr[i].value << "\n";
	}
	return 0;
}



/*
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

struct TData {
	unsigned long long keys[2], value;
};

void Radixsort(std::vector<TData>& arr) {
	std::vector<std::vector<TData>> digits(256);
	for (short l = 1; l >= 0; --l) {
		unsigned long long delimiter = 0x00000000000000ff, counter;
		for (unsigned short i = 0; i < 8; ++i) {
			for (unsigned j = 0; j < arr.size(); ++j) {
				unsigned long long interim = arr[j].keys[l] & delimiter;
				unsigned index = interim >> 8 * i;
				digits[index].push_back(arr[j]);
			}
			counter = 0;
			for (unsigned j = 0; j < 256; ++j) {
				for (unsigned k = 0; k < digits[j].size(); ++k) {
					arr[counter] = digits[j][k];
					++counter;
				}
				digits[j].clear();
			}
			delimiter <<= 8;
		}
	}
}

int main() {
	std::vector<TData> arr;
	std::string keys;
	unsigned long long value, key1, key2;
	while (std::cin >> keys >> value) {
		arr.push_back({ {std::stoull(keys.substr(0, 16), 0, 16), std::stoull(keys.substr(16, 16), 0, 16)}, value });
	}
	Radixsort(arr);
	for (unsigned i = 0; i < arr.size(); ++i) {
		std::cout << std::hex << std::setw(16) << std::setfill('0') << arr[i].keys[0] << std::setw(16) << std::setfill('0') << arr[i].keys[1] << "\t"
			<< std::dec << arr[i].value << "\n";
	}
	system("pause");
	return 0;
}*/


