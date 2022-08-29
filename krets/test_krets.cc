#include "krets.h"
#include <vector>
using namespace std;



int main(int argc, char** argv)
{
  int ticks,lines{};
  double time,volt{};

  try
  {
    if(argc!=5)
    {
      cout<<"To many arguments\n";
      throw 5;
    }
  }
  catch(int i)
    {
      cout<<"It should be: "<<i<<" arguments";
      return 0;
    }

    try
    {
      ticks = stoi(argv[1]);
      lines = stoi(argv[2]);
      time  = stod(argv[3]);
      volt  = stod(argv[4]);
    }
    catch (std::invalid_argument& e)
    {
      cout<<"invalid argument in command line"<<endl;
      return 0;
    }


circuit a("Krets 1");


  a.add_connection("p");
  a.add_connection("n");
  a.add_connection("q124");
  a.add_connection("q23");
  a.add_connection("l");
  a.add_connection("r");
try
{
  a.add_component(new battery("Bat", a.get_connection("p"), a.get_connection("n"), volt));
  a.add_component(new resistor("R1", a.get_connection("p"), a.get_connection("q124"), 6.0));
  a.add_component(new resistor("R2", a.get_connection("q124"), a.get_connection("q23"), 4.0));
  a.add_component(new resistor("R3", a.get_connection("q23"), a.get_connection("n"), 8.0));
  a.add_component(new resistor("R4", a.get_connection("q124"), a.get_connection("n"), 12.0));
}
catch (std::invalid_argument& e)
{
  cout<<"Wrong, connection does not exist"<<endl;
  return 0;
}

  a.simulate(ticks,lines,time);
  circuit b("Krets 2");
  b.add_connection("p2");
  b.add_connection("n2");
  b.add_connection("l2");
  b.add_connection("r2");


  b.add_component(new battery("Bat", b.get_connection("p2"), b.get_connection("n2"), volt));
  b.add_component(new resistor("R1", b.get_connection("p2"), b.get_connection("l2"), 150.0));
  b.add_component(new resistor("R2", b.get_connection("p2"), b.get_connection("r2"), 50.0));
  b.add_component(new resistor("R3", b.get_connection("l2"), b.get_connection("r2"), 100.0));
  b.add_component(new resistor("R4", b.get_connection("l2"), b.get_connection("n2"), 300.0));
  b.add_component(new resistor("R5", b.get_connection("r2"), b.get_connection("n2"), 250.0));

  b.simulate(ticks,lines,time);



  circuit c("Krets 3");
  c.add_connection("p");
  c.add_connection("n");
  c.add_connection("l");
  c.add_connection("r");

  c.add_component(new battery   ("Bat", c.get_connection("p"), c.get_connection("n"), volt));
  c.add_component(new resistor  ("R1", c.get_connection("p"), c.get_connection("l"), 150.0));
  c.add_component(new resistor  ("R2", c.get_connection("p"), c.get_connection("r"), 50.0));
  c.add_component(new capacitor ("C3", c.get_connection("r"), c.get_connection("l"), 1.0));
  c.add_component(new resistor  ("R4", c.get_connection("l"), c.get_connection("n"), 300.0));;
  c.add_component(new capacitor ("C4", c.get_connection("r"), c.get_connection("n"), 0.75));

  c.simulate(ticks,lines,time);


  return 0;
}
