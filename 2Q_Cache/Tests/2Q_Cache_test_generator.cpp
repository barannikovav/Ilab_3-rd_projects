#include <iostream>

int main () {
	int cache_size = 0;
	int num_of_pages = 0;
	int module = 0;
	
	std::cin >> cache_size >> num_of_pages >> module;

	std::cout << cache_size << ' ' << num_of_pages << std::endl;

	for (int i = 0; i < num_of_pages; ++i) {
		std::cout << rand() % module + 1 << ' ';
	}

	return 0;
}