#include <string>
#include <iostream>
#include <sstream>

#include "catch.hpp"
#include "Time.h"

using namespace std;

// här lägger ni era testfall.
// Jobba enligt TDD;
//  1. Lägg till testfall
//  2. Testa
//  3. Lägg till (minsta möjliga) implementation
//  4. Testa alla testfall
//  5. Refaktorera (skriv om) så att allt ser bra ut

TEST_CASE ("Default constructor")
{
    Time t;

    CHECK(t.get_hour() == 0);
    CHECK(t.get_minute() == 0);
    CHECK(t.get_second() == 0);
}

// the following line will halt the compilation process. Move it
// one test case at the time and then start creating your own test
// cases

TEST_CASE ( "Constructor with numeric arguments" )
{
    Time t{12,13,14};
    CHECK(t.get_hour() == 12);
    CHECK(t.get_minute() == 13);
    CHECK(t.get_second() == 14);
}

TEST_CASE ("Constructor with faulty argument")
{
    CHECK_THROWS( Time{41,0,0} );
    CHECK_THROWS( Time{0,99,0} );
    CHECK_THROWS( Time{0,0,99} );
}

TEST_CASE ("String constructor")
{
    Time t{"12:23:12"};
    CHECK(t.get_hour() == 12);
    CHECK(t.get_minute() == 23);
    CHECK(t.get_second() == 12);

    SECTION ("Throws as well")
    {
        CHECK_THROWS( Time{"02:11:74"} );
    }
}



TEST_CASE ("am or pm")
{
    Time t{12,12,31};
    CHECK_FALSE(t.is_am());
    Time t2{1,2,3};
    CHECK(t2.is_am());
}

TEST_CASE ("Convert to string" )
{
    CHECK( Time{12,12,12}.to_string()     ==    "12:12:12" );
    CHECK( Time{12, 1, 2}.to_string()     ==    "12:01:02" );
    CHECK( Time{14,33,12}.to_string(true) == "02:33:12 pm" );
}

TEST_CASE ("Conversion to string" )
{
    CHECK( string(Time{2,4,1}) == "02:04:01" );
}

TEST_CASE ("Output operator" )
{
    stringstream ss;
    SECTION("Simple output")
    {
        ss << Time{2,5,1};
        CHECK(ss.str() == "02:05:01");

    }
    SECTION("Chained output")
    {
        ss << Time{23,10,32} << "---";
        CHECK(ss.str() == "23:10:32---");
    }
    SECTION("Const time")
    {
        Time const t{23,23,23};
        ss << t;
        CHECK(ss.str() == "23:23:23");
    }
}

//TODO: Testa så att t inte modifieras tex t2 = t + n.
//KLAR LAGT TILL MODULUS osv
TEST_CASE("Add time" )
{
Time t{23,59,5};
int n{125};

Time t2=t+n;

CHECK(t2.get_hour() ==0);
CHECK(t2.get_minute() ==1);
CHECK(t2.get_second() ==10);
}
TEST_CASE("2 * 86400" )
{
Time t{23,59,5};
int n{172800};

Time t2=t+n;

CHECK(t2.get_hour() ==23);
CHECK(t2.get_minute() ==59);
CHECK(t2.get_second() ==5);
}

//TODO: Samma som testet för + operatorn.
//KLAR LAGT TILL MODULUS osv
TEST_CASE("Minska time" )
{
Time t{1,58,5};
int n{86400};

Time t2=t-n;

CHECK(t2.get_hour() ==1);
CHECK(t2.get_minute() ==58);
CHECK(t2.get_second() ==5);
}

TEST_CASE("-60 sekunder" )
{
Time t{1,58,5};
int n{60};

Time t2=t-n;

CHECK(t2.get_hour() ==1);
CHECK(t2.get_minute() ==57);
CHECK(t2.get_second() ==5);
}
TEST_CASE("-3600 sekunder" )
{
Time t{1,58,5};
int n{3600};

Time t2=t-n;

CHECK(t2.get_hour() ==0);
CHECK(t2.get_minute() ==58);
CHECK(t2.get_second() ==5);
}

TEST_CASE("-3600 sekunder v.2" )
{
Time t{0,58,5};
int n{3600};

Time t2=t-n;

CHECK(t2.get_hour() ==23);
CHECK(t2.get_minute() ==58);
CHECK(t2.get_second() ==5);
}


//TODO: Testar inte pre delen av incrementen.
// TO_STRING LAGT TILL, GAMLA CHECKS OCKSÅ BEHÅLLT
// LIKA FÖR ALLA PRE-INC/DEC, LIKA FÖR ALLA POST-INC/DEC
TEST_CASE("pre increment" )
{
Time t{1,1,5};
Time t2{1,1,5};
//
CHECK((++t).to_string() =="01:01:06");
//

CHECK(t.get_hour() ==1);
CHECK(t.get_minute() ==1);
CHECK(t.get_second() ==6);
}

TEST_CASE ("23:59:59")
{
Time t{23,59,59};
//
CHECK((++t).to_string() =="00:00:00");
//
CHECK(t.get_hour() ==0);
CHECK(t.get_minute() ==0);
CHECK(t.get_second() ==0);
}

TEST_CASE ("23:58:59")
{
Time t{23,58,59};
//
CHECK((++t).to_string() =="23:59:00");
//
CHECK(t.get_hour() ==23);
CHECK(t.get_minute() ==59);
CHECK(t.get_second() ==0);
}

TEST_CASE ("22:59:59")
{
Time t{22,59,59};
//
CHECK((++t).to_string() =="23:00:00");
//
CHECK(t.get_hour() ==23);
CHECK(t.get_minute() ==0);
CHECK(t.get_second() ==0);
}

//TODO: Testar inte post delen av incrementen.
TEST_CASE("Post increment" )
{
Time t{1,1,5};
CHECK((t++).to_string() =="01:01:05");
CHECK(t.get_hour() ==1);
CHECK(t.get_minute() ==1);
CHECK(t.get_second() ==6);
}

//TODO: Testar inte pre delen av decrementen.
TEST_CASE("pre decrement" )
{
Time t{1,1,5};
//
CHECK((--t).to_string() =="01:01:04");
//

CHECK(t.get_hour() ==1);
CHECK(t.get_minute() ==1);
CHECK(t.get_second() ==4);
}

TEST_CASE("00:00:00" )
{
Time t{0,0,0};
//
CHECK((--t).to_string() =="23:59:59");
//
CHECK(t.get_hour() ==23);
CHECK(t.get_minute() ==59);
CHECK(t.get_second() ==59);
}

//TODO: Testar inte post delen av decrementen.
TEST_CASE("post decrement" )
{
Time t{1,1,5};
//
CHECK((t--).to_string() =="01:01:05");
//

CHECK(t.get_hour() ==1);
CHECK(t.get_minute() ==1);
CHECK(t.get_second() ==4);
}

TEST_CASE("likalika med")
{
Time t{1,1,1};
Time s{1,1,1};
CHECK(t==s);
}

TEST_CASE("mindre än")
{
Time t{1,1,1};
Time s{1,1,2};
CHECK(t<s);
}

TEST_CASE("större än")
{
Time t{1,1,1};
Time s{1,1,0};
CHECK(t>s);
}

TEST_CASE("icke lika")
{
Time t{1,1,1};
Time s{1,1,0};
CHECK(t!=s);
}

TEST_CASE("större/likamed")
{
Time t{1,1,1};
Time s{1,1,1};
CHECK(t>=s);
}


TEST_CASE("mindre/likamed")
{
Time t{1,1,1};
Time s{1,1,1};
CHECK(t<=s);
}

//TODO: testa chained input och att failflaggan sätts.
TEST_CASE("INSTREAM")
{
  stringstream ss;
  string test{"02:03:04"}; //chained
  string test2{"01:02:05"}; // chained
  string test3{"-01:03:05"}; //failflagga

  ss<<test<< " " <<test2; //<<" "<<test2;   //Time{25,3,4};
  Time k{};
  Time h{};
  Time r{};
  ss>>k>>h;
  CHECK(k.get_hour() == 2);
  CHECK(k.get_minute() == 3);
  CHECK(k.get_second() == 4);


  CHECK(h.get_hour() == 1);
  CHECK(h.get_minute() == 2);
  CHECK(h.get_second() == 5);

  ss.clear();

  ss<<test3;
  ss>>r;
  CHECK(ss.fail()==true);
  CHECK(r.get_hour() == 0);
  CHECK(r.get_minute() == 0);
  CHECK(r.get_second() == 0);

/*  CHECK(ss.fail()==false);

  ss<<test2;
  ss>>h;
  CHECK(ss.fail()==true);


  CHECK(k.get_hour() == 2);
  CHECK(k.get_minute() == 3);
  CHECK(k.get_second() == 4);

  CHECK(h.get_hour() == 1);
  CHECK(h.get_minute() == 2);
  CHECK(h.get_second() == 5);
*/
}
#if 0

#endif
