#include "krets.h"
#include <iomanip>
using namespace std;

/////////////////////////////////////KONSTRUKTORER
  connection::connection(string name)
  :  name{name},charge{0} {}

  component::component(std::string n, connection& P, connection& N)
  :  name{n} , P{P} , N{N} {}

  resistor::resistor(string n, connection& P, connection& N, double o)
  :  component{n,P,N}, ohm{o} {}

  battery::battery(string n, connection& P, connection& N, double v)
  :  component{n,P,N}, volt{v} {}

  capacitor::capacitor(string n, connection& P, connection& N, double f)
  :  component{n,P,N}, fahrad{f}, savedvolt{0} {}

  circuit::circuit(string name)
  : net{}, connect{}, name{name} {}

/////////////////////////////////////DEKONSTRUKTOR
  component:: ~component()  {}
  resistor::  ~resistor()   {}
  battery::   ~battery()    {}
  capacitor:: ~capacitor()  {}
  circuit::   ~circuit()
  {
    for(unsigned int i{};i<net.size(); i++)
    {
      delete net[i];
    }
  }

string component::get_name()const
{
  return name;
}
/////////////////////////////////////FUNKTIONER

//////////////////////////////CONNECTIONS

    double connection::get_charge() const
    {
      return charge;
    }

    void connection::set_charge(double v)
    {
      charge=v;
    }

    string connection::get_name()const
    {
      return name;
    }


//////////////////////////////RESISTOR
    double resistor::get_volt()const
    {
      double volt{};
      if(P.get_charge()>N.get_charge())
      {
        volt=P.get_charge()-N.get_charge();
      }
      else
      {
        volt=N.get_charge()-P.get_charge();
      }
      return volt;
    }

    double resistor::get_current()const
    {
      return get_volt()/ohm;
    }


    void resistor::tick(double t)
    {
      double change= get_current()*t;
      double Ptot{};
      double Ntot{};
      if(P.get_charge()>N.get_charge())
      {
        Ptot=P.get_charge()-change;
        Ntot=N.get_charge()+change;
      }
      else
      {
        Ptot=P.get_charge()+change;
        Ntot=N.get_charge()-change;
      }

      P.set_charge(Ptot);
      N.set_charge(Ntot);
    }


//////////////////////////////BATTERY
    double battery::get_volt() const
    {
      return volt;
    }

    double battery::get_current()const
    {
      return 0;
    }


    void battery::tick(double)
    {
	     //TODO Vad gör detta? Vill ni ha bort varningen bör ni bara ta bort namnet på parametern. Alltså tick(double) istället för tick(double t)
       //FIXAT
      P.set_charge(volt);
      N.set_charge(0.0);
    }


//////////////////////////////CAPACITOR
    double capacitor::get_volt() const
    {
      double volt{};
      if(P.get_charge()>N.get_charge())
      {
        volt=P.get_charge()-N.get_charge();
      }
      else
      {
        volt=N.get_charge()-P.get_charge();
      }
      return volt;
    }

    double capacitor::get_current()const
    {
      return fahrad*(get_volt()-savedvolt);
    }


    void capacitor::tick(double t)
    {

        double volt{};
        double Ptemp{};
        double Ntemp{};

        volt=(get_volt()-savedvolt)*t*fahrad;
        savedvolt = volt + savedvolt;

        if(P.get_charge()>N.get_charge())
        {
          Ptemp = P.get_charge() - volt;
          Ntemp = N.get_charge() + volt;
        }
        else
        {
          Ntemp = N.get_charge() - volt;
          Ptemp = P.get_charge() + volt;
        }

        P.set_charge(Ptemp);
        N.set_charge(Ntemp);
    }


//////////////////////////////CIRCUIT
    connection& circuit::get_connection(string name)
    {
        for(unsigned int i{}; i<connect.size(); i++)
        {
          if(connect[i].get_name()==name)
          {
            return connect[i];
          }
        }
        throw std::invalid_argument("fel");
      }

    void circuit::add_component(component* comp)
    {
      net.push_back(comp);
    }

    void circuit:: add_connection(string name)
    {
      connection new_connect(name);
      connect.push_back(new_connect);
    }

    void circuit::simulate(int ticks, int lines, double time)const
    {
      cout<<" "<<name<<":"<<endl;
      for(unsigned int i{}; i<net.size(); i++)
      {
        cout<<setw(12)<<net[i]->get_name();
      }

        cout<<endl;

      for(unsigned int i{}; i<net.size();i++)
      {
        cout<<setw(6)<<"Volt"<<setw(6)<<"Curr";
      }

          cout<<endl;

      for(int i{}; i<lines; i++)
      {
        for (int y{}; y<ticks/lines; y++)
        {
          for(unsigned int k{}; k<net.size(); k++)
          {
          net[k]->tick(time);
          }
        }
        for(unsigned int x{}; x<net.size(); x++)
        {
         cout<<fixed<<setprecision(2)<<setw(6)<<net[x]->get_volt()<<setw(6)<<net[x]->get_current();
        }
        cout<<endl;
      }
      cout<<endl;
    }
