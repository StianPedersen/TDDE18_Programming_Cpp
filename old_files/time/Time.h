// Denna fil ska innehålla deklarationer för de typer och funktioner
// som behövs
#ifndef TIME_H_
# define TIME_H_
#include <iostream>

//TODO: Alla parametrar som inte modifieras ska ha const alt. const reference.
// Const satt på operator ++ och --

//Tänk på att alla parametrar som inte modifieras ska vara const alt. const reference.
//Exempel Time(std::string text) => Time(std::string const &text)
//Exempel Time(int h, int m, int s) => Time(int const h, int const m, int const s)
// ++ och -- operatorerna behöver inte ha const int, int är bara där för att berätta för
//kompilatorn att det är postfix.


class Time
{
//VÄNNER FÖR LIVET!!!!
friend std::ostream& operator <<(std::ostream &, Time const&);
friend std::istream& operator >>(std::istream&, Time &);


public:
//KONSTRUKTOR, EJ KONDUKTÖR
  Time();
  Time(int h, int m, int s);
  Time(std::string text);

//OPERANDER, OPERAR OPERASKA
Time operator +(int const& rhs)const;
Time operator -(int const& rhs)const;
Time& operator ++();
Time& operator --();
Time operator --(int const);
Time operator ++(int const);
operator std::string() const;

//JÄMFÖRELSEOPERATORER
bool operator ==(Time const& rhs)const;
bool operator <(Time const& rhs)const;
bool operator >(Time const& rhs)const;
bool operator !=(Time const& rhs)const;
bool operator >=(Time const& rhs)const;
bool operator <=(Time const& rhs)const;
//GREJER
  int get_hour() const;
  int get_minute() const;
  int get_second() const;
  bool is_am() const;
  std::string to_string(bool b=false) const;

private:
  int hour;
  int minute;
  int second;

};

#endif
