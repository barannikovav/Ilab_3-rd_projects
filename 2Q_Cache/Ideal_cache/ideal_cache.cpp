#include <iostream>
#include <list>
#include <iterator>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>

using List_it = std::list<int>::iterator;

int Ideal_Cache (size_t cache_size, unsigned int page_buf_size, std::vector <int> &input_vector) {
	std::list <int> cache;
	List_it found_it;
	int hit_score = 0;

	for (unsigned int i = 0; i < page_buf_size; ++i) {
		if (cache.empty()) {
			cache.push_front(input_vector[i]);
			continue;
		}

		found_it = std::find(cache.begin(), cache.end(), input_vector[i]);

		if (found_it == cache.end()) {

			if (cache.size() >= cache_size) {
				
				std::map <int, List_it> future_points_map;

				for (List_it index = cache.begin(); index != cache.end(); ++index) {
					unsigned int distance = page_buf_size + 1;
					
					for (unsigned int j = i; j < page_buf_size; ++j) {
						
						if (input_vector[j] == *index) {
							distance = j - i;
							break;
						}

					}

					future_points_map[(int)distance] = index;
				}

				if (!future_points_map.empty()) {
				cache.erase(future_points_map.rbegin()->second);
				} else {std::cerr << "Rbegin on empty map\n";}
			}

			cache.push_front(input_vector[i]);

		} else {
			++hit_score;
		}

	}
	return hit_score;
}

int main (void) {
	size_t cache_s = 0;
	unsigned int num_of_pages = 0;
	

	std::cin  >> cache_s >> num_of_pages;

	std::vector <int> input(num_of_pages);

	assert(std::cin.good());

	for (unsigned int k = 0; k < num_of_pages; ++k) {
		int item;

		std::cin >> item;
		assert(std::cin.good());

		input[k] = item;
	}

	std::cout << Ideal_Cache(cache_s, num_of_pages, input) << std::endl;

	return 0;
}