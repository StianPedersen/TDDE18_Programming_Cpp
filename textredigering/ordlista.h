#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>


	void get_file(std::fstream & fs, char* argv[]);

	void erase_first(std::string& w);

	void erase_last(std::string& w);

	void erase_gen(std::string& w);

	int biggest_word(std::vector<std::pair<std::string, int>> test);

	int find_first_alpha(std::string const& w);

	int find_last_alpha(std::string const& w);

	int find_final_trash(std::string const& w);

	bool is_valid(std::string & w);
	
