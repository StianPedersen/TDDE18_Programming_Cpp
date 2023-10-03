#include "ordlista.h"
#include <utility>
#include <map>
#include <cmath>
#include <iomanip>

//TODO: Vid inmatning av felaktigt argument ska ett instruktivt
//felmeddelande ges, se labb instruktionerna.

//TODO: Använd biblioteket cctype för att kolla efter bokstäver och
//icke-bokstäver för att undvika fullständig uppräkning.

//TODO: Ni använder transform på ett felaktigt sätt vid
//utmatning. Transform ska endast användas vid modifiering av element
//i en container. Hint: Använd copy till en utström istället.

//TODO: mutable ska ej användas. Använd referens istället.



void get_file(std::fstream& fs, char* argv[])
{
	std::map<std::string, int> m;
	std::vector<std::string> app_words;
	std::string w;
	while (fs >> w)
	{
		erase_first(w);
		
		erase_last(w);
		
		erase_gen(w);
		

		if (std::string(argv[2]) == "-a") 
		{
			if (is_valid(w))
			{
				m[w]++;
			}
		}
		else if (std::string(argv[2]) == "-f")
		{
			if (is_valid(w))
			{
				m[w]++;
			}
		}
		else if (std::string(argv[2]) == "-o")
		{
			
			if (is_valid(w))
			{
				app_words.push_back(w);
			}
		}

	}		
	
		if (std::string(argv[2]) == "-a")
		{
			std::vector <std::pair<std::string, int>> test;
			test.assign(m.begin(), m.end());

			auto print = [test](std::pair<std::string, int> e)
			{
				unsigned int x = biggest_word(test) - e.first.size() + 2;
				std::cout	<< e.first <<std::setw(x)<<std::setfill(' ') <<	e.second << std::endl;
				return e;
			};

			std::transform(test.begin(), test.end(), test.begin(), print);
			
		}
		else if (std::string(argv[2]) == "-f")
		{
			std::vector <std::pair<std::string, int>> test;
			test.assign(m.begin(), m.end());	

			auto sortbysec = [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b)
			{
				return (a.second > b.second);
			};
			std::sort(test.begin(), test.end(), sortbysec);

			auto print = [test](std::pair<std::string, int> e)
			{
				std::cout << std::setw(biggest_word(test)) << e.first << "    " << e.second << std::endl;
				return e;
			};

			std::transform(test.begin(), test.end(), test.begin(), print);

		}
		else if (std::string(argv[2]) == "-o")
		{
			int g{ 0 };
			int N = std::stoi(argv[3]);
			auto print = [N, g](const std::string& w) mutable
			{
				g = w.size() + g;

				if (g >= N)
				{

					g = 0;
					std::cout << std::endl;
					g = w.size();
					std::cout << w << " ";
					++g;
				}
				else
				{
					std::cout << w << " ";
					++g;
				}
			};


			std::for_each(app_words.cbegin(), app_words.cend(), print);
		}
}

int biggest_word(std::vector<std::pair<std::string, int>> test)
{

		std::vector<std::pair<std::string, int>>::iterator result;
		result = std::max_element(test.begin(), test.end());
		return result->first.size();
}

int find_first_alpha(std::string const& w)
{
	std::string search_str = std::string("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	return  w.find_first_of(search_str);
}

int find_last_alpha(std::string const& w)
{
	std::string search_str = std::string("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	return  w.find_last_of(search_str);
};

int find_final_trash(std::string const& w)
{
	std::string search_str = std::string("~`!@#$%^&*()_+=|\n}]{[\"\':;?/>.<,");
	return w.find_last_of(search_str);
};

void erase_first(std::string& w)
{
	
	auto e = next(w.begin(), find_first_alpha(w));
	
	  w.erase(std::remove_if(w.begin(), e,
		  [](unsigned char x)
		 {
			  if ((x == '\'') or (x=='"') or (x== '(') )
			  {
				  return true;
			  }
			  else
			  {
				  return false;
			  }
		  })
		  ,e);
};

void erase_last(std::string& w)
{
	
	auto e = next(w.begin(), find_last_alpha(w));
	
	w.erase(std::remove_if(e, w.end(),
		[](unsigned char x)
		{
			if ((x == '!') or (x == '?') or (x == ';') or (x == ',') or (x == ':') or (x == '.') or (x == '"') or (x == '\'') or (x == ')'))
			{
				return true;
			}
			else
			{
				return false;
			}
		})
		, w.end());
};

void erase_gen(std::string& w)
{
	
	auto e = next(w.begin(), (find_last_alpha(w) - 1));

	w.erase(std::remove_if(e, w.end(),

		[](unsigned char x)
		{
			if ((x == '\'') or (x == 's'))
			{

				return true;
			}
			else
			{
				return false;
			}
		}), w.end());
}

bool is_valid(std::string& w) 
{

	auto it = std::adjacent_find(w.begin(), w.end());
	if (it == w.end())
	{
		if (find_final_trash(w)==w.npos)
		{
			if (w.size() > 2)
			{

				std::transform(w.begin(), w.end(), w.begin(),
				 [](unsigned char c){ return std::tolower(c); });
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}





