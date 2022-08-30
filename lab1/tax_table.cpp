#include <iostream>
#include <iomanip>

int main()
{
    double first_price{}, last_price{}, stride{}, tax_percent{};
    std::cout << "INPUT PART\n"
              << "==========\n"
              << "Enter first price: ";
    std::cin >> first_price;
    if (first_price < 0)
        std::cerr << "Must be above 0";
    std::cout << "Enter last price : ";
    std::cin >> last_price;
    std::cout << "Enter stride     : ";
    std::cin >> stride;
    std::cout << "Enter tax percent: ";
    std::cin >> tax_percent;
    std::cout << "\nTAX TABLE\n=========\n";
    std::cout << "       Price            Tax        Price with tax"
              << "\n";
    std::cout << "-------------------------------------------------\n";

    while (first_price <= last_price)
    {
        std::cout << std::setprecision(2) << std::fixed << std::setw(12) << first_price << std::setw(15) << (first_price * tax_percent) / 100 << std::setw(22) << first_price + ((first_price * tax_percent) / 100) << "\n";
        first_price = first_price + stride;
    }
}