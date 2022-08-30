#include <string>
#include <iostream>
#include <iomanip>

int main()
{
    // One of each
    int i{};
    double d{};
    char c{};
    std::string s{};

    // 1
    int int_number{};
    std::cout << "Enter one integer: ";
    std::cin >> int_number;
    std::cout << "You entered the number: " << int_number << "\n\n";
    std::cin.ignore(1000, '\n');

    // // 2
    std::cout << "Enter four integers: ";
    std::cin >> i;
    std::cout
        << "You entered the numbers: " << i << " ";
    std::cin >> i;
    std::cout << i << " ";
    std::cin >> i;
    std::cout << i << " ";
    std::cin >> i;
    std::cout << i << "\n\n";
    std::cin.ignore(1000, '\n');

    // 3
    std::cout << "Enter one integer and one real number: ";
    std::cin >> i >> d;
    std::cout << "The real is: " << std::setprecision(4) << std::setw(11) << d << "\n";
    std::cout << "The integer is: " << std::setw(8) << i << "\n\n";
    std::cin.ignore(1000, '\n');

    // 4
    std::cout << "Enter one real and one integer number: ";
    std::cin >> d >> i;
    std::cout << "The real is: " << std::setprecision(3) << std::fixed << std::setw(11) << std::setfill('.') << d << "\n";
    std::cout << "The integer is: " << std::setw(8) << std::setfill('.') << i << "\n\n";
    std::cin.ignore(1000, '\n');

    // 5
    std::cout << "Enter a character: ";
    std::cin >> c;
    std::cout << "You entered: " << c << "\n\n";
    std::cin.ignore(1000, '\n');

    // // 6
    std::cout << "Enter a word: ";
    std::cin >> s;
    std::cout << "The word '" << s << "' has " << s.length() << " character(s).\n\n";
    std::cin.ignore(1000, '\n');

    // 7
    std::cout << "Enter an integer and a word: ";
    std::cin >> i >> s;
    std::cout << "You entered '" << i << "' and '" << s << "'.\n\n";
    std::cin.ignore(1000, '\n');

    // 8
    std::cout << "Enter an character and a word: ";
    std::cin >> c >> s;
    std::cout << "You entered the string " << '"' << s << '"' << " and the character '" << c << "'.\n\n";
    std::cin.ignore(1000, '\n');

    // 9
    std::cout << "Enter a word and real number: ";
    std::cin >> s >> d;
    std::cout << "You entered " << '"' << s << '"' << " and " << '"' << std::setprecision(3) << std::fixed << d << '"' << ".\n\n";
    std::cin.ignore(1000, '\n');

    // 10
    std::cout << "Enter a text-line: ";
    std::getline(std::cin, s);
    std::cout << "You entered: " << '"' << s << '"' << "\n\n";

    // 11
    std::cout << "Enter a second line of text: ";
    std::getline(std::cin, s);
    std::cout << "You entered: " << '"' << s << '"' << "\n\n";

    // 12
    std::cout << "Enter three words: ";
    std::cin >> s;
    std::cout << "You entered: '" << s << " ";
    std::cin >> s;
    std::cout << s << " ";
    std::cin >> s;
    std::cout << s << "'\n";
}