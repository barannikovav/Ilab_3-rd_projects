#include <iostream>
#include <list>
#include <iterator>
#include <unordered_map>
#include <cassert>
#include  <string>

//#define TEST //uncomment to turn on test mode

#ifdef TEST
#define ERROR_REPORT(ERROR_TEXT) \
do { \
	auto MACRO_tmp = (ERROR_TEXT); \
	using std::cerr; \
  using std::endl; \
	cerr << "[!] ERROR [!]" << endl; \
  cerr << "File:        " << __FILE__ << endl; \
  cerr << "Line:        " << __LINE__ << endl; \
  cerr << "Function:    " << __func__ << endl; \
  cerr << "Error text:  " << MACRO_tmp << endl; \
  assert(false); \
} while (0)
#endif

#ifndef TEST
#define ERROR_REPORT(ERROR_TEXT) \
do { \
	auto MACRO_tmp = (ERROR_TEXT); \
	using std::cerr; \
  using std::endl; \
	cerr << "[!] ERROR [!]" << endl; \
  cerr << "Function:    " << __func__ << endl; \
  cerr << "Error text:  " << MACRO_tmp << endl; \
  assert(false); \
} while (0)
#endif


//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

enum List_type {
	A_IN,
	A_OUT,
	A_MAIN
};

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template <typename Data> struct List_item {
	
	Data data;

	List_type type;
};

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template <typename Key, typename Data> struct Univ_List {
	size_t Size_list;

	std::list<List_item<Data> > List;
	
	Univ_List() {};

	Univ_List(size_t size) {
		Size_list = size;
	}

	bool Full () const {
		return (Size_list < List.size());
	}

	size_t size () const {
		return Size_list;
	}

};

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

namespace caches {

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


	template <typename Key, typename Data> struct Cache_2Q {

		private:
	 		


	 		size_t Cache_size;

	 		int hit_score;

	 		unsigned long size_division;

	 		Univ_List<Key, Data> A_in;
   		Univ_List<Key, Data> A_main;
   		Univ_List<Key, Data> A_out;

	 		using List_It = typename std::list<List_item<Data> >::iterator;
   		using Map_It  = typename std::unordered_map<Key, List_It>::iterator;

   		std::unordered_map<Key, List_It> Hash_Map;

   		
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::  		

   		void Transfer_between_lists (Map_It object, Univ_List<Key, Data> &From, Univ_List<Key, Data> &To, List_type new_list_type) {

   			To.List.splice(To.List.begin(), From.List, object->second);

   			object->second = To.List.begin();

   			object->second->type = List_type(new_list_type);

   			return;
   		}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   		void Kick_last_item (List_type aim_list) {
   			
   			switch (aim_list) 
   			{

   				case A_OUT: {
   					auto outgoing_out = Hash_Map.find(A_out.List.back().data);
   				
   					A_out.List.pop_back();

   					Hash_Map.erase(outgoing_out);

   					break;
   				}

   				case A_MAIN: {
   					auto outgoing_main = Hash_Map.find(A_main.List.back().data);
   			
   					A_main.List.pop_back();

   					Hash_Map.erase(outgoing_main);

   					break;
   				}

   				default: {
   					
   					ERROR_REPORT("unknown list type");

   					break;
   				}
   			}
   				

   				return;
   		}
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

   		void Insert_new_item (const List_item<Data> &new_item) {

   			auto inserted = A_in.List.insert(A_in.List.begin(), new_item);

   			Hash_Map.insert({new_item.data, inserted});

   			return;
   		}


//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

   		void Process_existing_item (List_It existing_item) {

   			switch (existing_item->type) 
   			{
   				case A_IN: 
   				{
   					break;
   				}
   				

					case A_OUT: 
					{
   					
   					Transfer_between_lists(Hash_Map.find(existing_item->data), A_out, A_main, A_MAIN);
   					
   					break;
   				}
   				case A_MAIN: 
   				{

   					existing_item->type = A_MAIN;
   					A_main.List.splice(A_main.List.begin(), A_main.List, Hash_Map.find(existing_item->data)->second);

   					break;
   				}

   				default: {
 
						ERROR_REPORT("unknown list type");
   					break;
   				}
   			}

   			return;
   		}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

   		void Is_full_check () {

   			if (A_in.Full()) {
   				
   				if (A_in.List.empty()) {
   					
   					return;
   				}

   				Transfer_between_lists(Hash_Map.find(A_in.List.back().data), A_in, A_out, A_OUT);

   			} 
   			
   			if (A_out.Full()) {
   				
   				Kick_last_item(A_OUT);
   				
   			}

   			while (A_main.Full()) {
   				
   				Kick_last_item(A_MAIN);

   				
   			}

   			return;
   		}


   	public: 

   		Cache_2Q (const size_t size, const unsigned long division = 4): 
   			Cache_size {size}, hit_score {0}, size_division {division},

   			A_in {(size_t)((size / size_division) > 1 ? (size / size_division) : 1) }, 
   			A_main {(size_t)((size / size_division) > 1 ? (size / size_division) : 1)}, 
   			A_out {(size_t)(size > 2 ? (Cache_size - A_in.size() - A_main.size()) : 1) }

   			{}
 
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::  

   		template <typename F> bool get (Key key, F slow_get_page) {

   			if (Hash_Map.empty()) {
   				List_item<Data> new_item = {slow_get_page(key), A_IN};
   				Insert_new_item(new_item);
   				Is_full_check();

   				

   				return false;
   			}

   			auto item = Hash_Map.find(key);

   			if (item == Hash_Map.end()) {
   				
   				List_item<Data> new_item = {slow_get_page(key), A_IN};
   				Insert_new_item(new_item); 
   				Is_full_check();

   				return false;
   			} else {

   				Process_existing_item(item->second);
   				Is_full_check();

   				++hit_score;

   				return true;
   			}

   			return false;
   		}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::		

   		int Hit_Score () const {
   			return hit_score;
   		}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

   		void Print_sizes () const {
   			
   			std::cout << "Size of A_in: " << A_in.size() << " | Size of A_out: " << A_out.size() << " | Size of A_main: " << A_main.size() << std::endl;
   			return;
   		} 

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::   		

   		void cur_sizes () const {
   			std::cout << "Elements in A_in: " << A_in.List.size() << " Elements in A_out: " << A_out.List.size() << " Elements in A_main: " << A_main.List.size() << " Elements in Hash: " << Hash_Map.size() << std::endl;
   			return;
   		}

	};

};