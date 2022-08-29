// I denna fil läggs definitionerna (implementationen) av de funktioner
// som deklarerats i Time.h
#include "Time.h"
#include <exception>
#include <stdexcept>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

//Kommentar: Försök att indentera koden.
Time::Time() : hour{0}, minute{0}, second{0} {

}
//////////////////////////////////////////////////////////////
Time::Time(int h, int m, int s) :
hour{h}, minute{m}, second{s}
{
if (h>23)
{
throw std::invalid_argument("fel timme");
}

if (m>59)
{
throw std::invalid_argument("fel minut");
}

if (s>59)
{
throw std::invalid_argument("fel sekund");
}
}

/////////////////////////////////////////////////////////////
Time::Time(std::string text) :
hour{}, minute{}, second{}
{

  std::istringstream is(text);
  is >> hour;
  is.ignore(1);
  is >> minute;
  is.ignore(1);
  is >> second;

  if (hour>23 or hour <0)
  {
  throw std::invalid_argument("fel timme");
  }

  if (minute>59 or minute <0)
  {
  throw std::invalid_argument("fel minut");
  }

  if (second>59 or second <0)
  {
  throw std::invalid_argument("fel sekund");
  }

}

/////////////////////////////////////////////////////////////
int Time::get_hour() const
{
  return hour;
}

int Time::get_minute() const
{
  return minute;
}

int Time::get_second() const
{
  return second;
}

bool Time::is_am() const
{
  if (hour >= 12)
    {
      return false;
    }
    return true;
}

/////////////////////////////////////////////////////////////
string Time::to_string(bool b) const
{
  stringstream ss;
if(b==false)
{

  if(hour<10)
  {
    ss<<"0";
  }
  ss<<hour<<':';

  if(minute<10)
  {
    ss<<"0";
  }
  ss<<minute<<':';

  if (second<10)
  {
  ss<<"0";
  }
  ss<<second;
}
else
{

  if (is_am())
  {
    if(hour<10)
    {
      ss<<"0";
    }
    ss<<hour<<':';

    if(minute<10)
    {
      ss<<"0";
    }
    ss<<minute<<':';

    if (second<10)
    {
    ss<<"0";
    }
    ss<<second<<" am";
  }

else {
  if(hour>12)
  {
    int G{hour};
    G = (G-12);
    ss<<"0"<<G<<':';
  }
  if(hour<10)
  {
    ss<<"0";
    ss<<hour<<':';
  }


  if(minute<10)
  {
    ss<<"0";
  }
  ss<<minute<<':';

  if (second<10)
  {
  ss<<"0";
  }
  ss<<second<<" pm";


}
}
  return ss.str();
}

/////////////////////////////////////////////////////////////
Time::operator string() const
{
  return to_string();
}

/////////////////////////////////////////////////////////////
ostream& operator <<(ostream& lhs,Time const & rhs)
{
  lhs<<rhs.to_string();
  return lhs;
}


/////////////////////////////////////////////////////////////
istream& operator >>(istream& lhs,Time & rhs)
{
int temp_hour{};
int temp_minute{};
int temp_second{};


lhs>>temp_hour;
lhs.ignore(1);
lhs>>temp_minute;
lhs.ignore(1);
lhs>>temp_second;
if (temp_hour > 23 or temp_hour < 0 or temp_minute > 59 or temp_minute < 0 or temp_second > 59 or temp_second < 0)
{

  lhs.setstate(ios_base::failbit);
  return lhs;
}
/*
lhs>>temp_hour;
if (temp_hour > 23 or temp_hour < 0)
{
  lhs.setstate(ios_base::failbit);
  return lhs;
}

lhs.ignore(1);
lhs>>temp_minute;

if (temp_minute > 59 or temp_minute < 0)
{
  lhs.setstate(ios_base::failbit);
  return lhs;
}

lhs.ignore(1);
lhs>>temp_second;
lhs.ignore(1);
if (temp_second > 59 or temp_second < 0)
{
  lhs.setstate(ios_base::failbit);
  return lhs;
}
*/
rhs.hour = temp_hour;
rhs.minute = temp_minute;
rhs.second = temp_second;

return lhs;
}

//TODO: Det här är en väldigt inneffektiv implementation.
//Tips, ni kan använda modulus och delat för att ta bort "överflödig tid".
//Tex om användaren matar in mer än 86400s (över en dag).
//FIXAT, TESTAT MED MÅNGA STORA SIFFROR, TOG CA 0,004ms snabbare

/////////////////////////////////////////////////////////////
Time Time::operator +(int const& rhs)const
{
Time P{hour,minute,second};
P.second = (rhs % 60) + P.second;
P.minute = (rhs / 60) + P.minute;
if (P.minute>59)
{
  P.hour = P.hour + (P.minute / 60);

  P.minute = P.minute % 60;
}
if(P.hour>23)
{
  P.hour = P.hour % 24;
}
  return P;
}



//Fråga: Samma som + operatorn.
/////////////////////////////////////////////////////////////
Time Time::operator -(int const& rhs) const
{
  Time P{hour,minute,second};

  P.second = P.second - (rhs%60);
  if (P.second < 0)
  {

    P.minute = P.minute -1;
    P.second = 60 + P.second;
  }

  P.minute = P.minute - (rhs / 60);
  if (P.minute<0)
  {
    P.minute = ((P.minute*-1) % 60) ;
    P.minute = 60 - P.minute;
  }


  P.hour= P.hour - (rhs / 3600);
  if (P.hour<0)
  {
    P.hour = ((P.hour*-1) % 24) ;
    P.hour = 24 - P.hour;
  }
    return P;
}

/////////////////////////////////////////////////////////////
Time& Time::operator ++()
{
  second += 1;
  if (second > 59)
  {
    second = 0;
    minute +=1;
    if (minute> 59)
    {
      minute = 0;
      hour += 1;
      if(hour > 23)
      {
        hour = 0;
      }
    }
  }
  return *this;
}

/////////////////////////////////////////////////////////////
Time Time::operator ++(int const)
{
  Time tmp{*this};
  second += 1;
  if (second > 59)
  {
    second = 0;
    minute +=1;
    if (minute> 59)
    {
      minute = 0;
      hour += 1;
      if(hour > 23)
      {
        hour = 0;
      }
    }
  }
  return tmp;
}

/////////////////////////////////////////////////////////////
Time& Time::operator --()
{
  second-=1;
  if (second <0)
  {
    second = 59;
    minute -=1;
    if (minute < 0)
    {
      minute = 59;
      hour -= 1;
      if(hour < 0)
      {
        hour = 23;
      }
    }
  }
  return *this;
}

/////////////////////////////////////////////////////////////
Time Time::operator --(int const)
{
  Time tmp{*this};
  second -= 1;
  if (second <0)
  {
    second = 59;
    minute -=1;
    if (minute < 0)
    {
      minute = 59;
      hour -= 1;
      if(hour < 0)
      {
        hour = 23;
      }
    }
  }
  return tmp;
}

/////////////////////////////////////////////////////////////
bool Time::operator ==(Time const& rhs) const
{
if (hour==rhs.hour)
{
  if(minute==rhs.minute)
  {
    if(second==rhs.second)
    {
      return true;
    }
  }
}
return false;
}

/////////////////////////////////////////////////////////////
bool Time::operator <(Time const& rhs) const
{
if (hour<rhs.hour)
{
  return true;
}
if(hour==rhs.hour && minute<rhs.minute)
{
  return true;
}

if(hour==rhs.hour && minute==rhs.minute && second < rhs.second)
{
  return true;
}

return false;

}

/////////////////////////////////////////////////////////////
bool Time::operator >(Time const& rhs) const
{
if(*this<rhs or *this==rhs)
{
  return false;
}
  return true;
}

/////////////////////////////////////////////////////////////
bool Time::operator !=(Time const& rhs) const
{
  if(*this==rhs)
  {
    return false;
  }
  return true;
}

/////////////////////////////////////////////////////////////
bool Time::operator >=(Time const& rhs)const
{
if(*this==rhs or *this>rhs)
{
return true;
}
return false;
}

/////////////////////////////////////////////////////////////
bool Time::operator <=(Time const& rhs)const
{
if(*this==rhs or *this<rhs)
{
return true;
}
return false;
}
