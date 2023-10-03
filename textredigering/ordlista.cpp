#include "ordlista.h"

int main(int argc, char *argv[])
{
    std::fstream fs;
    
        if (argc == 1)
            {
                std::cout << "Error: No arguments given." << std::endl;
                std::cout << "Usage: a.out FILE [-a] [-f] [-o N]" << std::endl;
                return 0;
		    }
        else if (argc == 2)
            {
                std::cout << "Error: Second argument missing or invalid." << std::endl;
                std::cout << "Usage: a.out FILE [-a] [-f] [-o N]" << std::endl;
                return 0;
            }

     fs.open(argv[1], std::fstream::in | std::fstream::app);
     get_file(fs, argv);
   
     fs.close();
    return 0;
}