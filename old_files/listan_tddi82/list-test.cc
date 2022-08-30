#include "List.h"
#include <iostream>
#include "catch.hpp"



TEST_CASE("Create list")
{

    List_NS::List<int> lst{ 1,4,2,6,8,9 };
    CHECK(lst.at(2) == 2);
    CHECK(lst.size() == 6);
    List_NS::List<int> l2;
    l2 = lst;
    CHECK(l2.size() == lst.size());
    CHECK(l2.front() == lst.front());
    CHECK(l2.back() == lst.back());
}

TEST_CASE("Push front and Push Back")
{
    List_NS::List<int> lst{ 1,2,3};
    lst.push_front(0);
    CHECK(lst.at(0) == 0);
    lst.push_back(4);
    CHECK(lst.at(4) == 4);
}

TEST_CASE("Swap")
{
    List_NS::List<int> lst{ 1,2,3};
    List_NS::List<int> lst2{ 3,2,1 };
    lst.swap(lst2);

    CHECK(lst.at(0) == 3);
    CHECK(lst.at(1) == 2);
    CHECK(lst.at(2) == 1);

    CHECK(lst2.at(0) == 1);
    CHECK(lst2.at(1) == 2);
    CHECK(lst2.at(2) == 3);
}

TEST_CASE("Empty")
{
    List_NS::List<int> lst;
    List_NS::List<int> lst2{ 1 };
    CHECK(lst.empty() == true);
    CHECK(lst2.empty() == false);
}

TEST_CASE("Iterator")
{
    List_NS::List<int> lst{ 2,3,1,5 };
    auto rb{ std::make_reverse_iterator(lst.end()) };
    auto re{ std::make_reverse_iterator(lst.begin()) };
    for (auto it = rb; it != re; ++it)
    {
        std::cout << *it << ' ';
    }

}

TEST_CASE("Create list string")
{
    List_NS::List<std::string> lst{"en","to","tre"};
    CHECK(lst.at(0)  == "en");
    CHECK(lst.size() == 3);

    lst.push_front("noll");
    CHECK(lst.at(0) == "noll");
    lst.push_back("fyra");
    CHECK(lst.at(4) == "fyra");

    List_NS::List<std::string> lst1{"en","to","tre"};
    List_NS::List<std::string> lst2{"tre","to","en"};
    lst1.swap(lst2);

    CHECK(lst1.at(0) == "tre");
    CHECK(lst1.at(1) == "to");
    CHECK(lst1.at(2) == "en");

    CHECK(lst2.at(0) == "en");
    CHECK(lst2.at(1) == "to");
    CHECK(lst2.at(2) == "tre");
}


TEST_CASE("Iterator string list")
{

    List_NS::List<std::string> lst{ "tva","tre","ett","fem" };
    auto rb{ std::make_reverse_iterator(lst.end()) };
    auto re{ std::make_reverse_iterator(lst.begin()) };
    for (auto it = rb; it != re; ++it)
    {
        std::cout << *it << ' ';
    }


}

TEST_CASE("operator ->")
{
    List_NS::List<int> lst{ 1,2,3 };
    for (List_NS::List<int>::List_Iterator it = lst.begin(); it != lst.end(); ++it)
    {

        std::cout << (it).operator->() << std::endl;
    }

}
