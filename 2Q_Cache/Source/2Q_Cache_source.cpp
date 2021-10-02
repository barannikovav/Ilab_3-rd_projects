#include "2Q_Cache_header.hpp"

int slow_get_page_int (int key) {
		int data = key;

		return data;
	}

int main () {

	size_t cache_size = 0;
	int num_of_pages = 0;

	//std::cout << "Insert size of cache and number of pages: ";
	std::cin  >> cache_size >> num_of_pages;


	assert(std::cin.good());

	caches::Cache_2Q<int, int> Cache{cache_size};

	

	for  (int i = 0; i < num_of_pages; ++i) {
		int item;

		std::cin >> item;
		assert(std::cin.good());

		Cache.get(item, &slow_get_page_int);

	}

	//std::cout <<"Number of hits:" << Cache.Hit_Score() << std::endl;
	std::cout << Cache.Hit_Score() << std::endl;


	return 0;
}