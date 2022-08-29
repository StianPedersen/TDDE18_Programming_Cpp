#ifndef KRETS_H
#define KRETS_H

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

/*
TODO:

Funktioner som ser likadana ut i alla subklasser bör inte vara pure-virtual utan istället ligga i basklassen.

5-4 //GJORT OM GET_NAME SÅ DEN ENDAST LIGGER I BASKLASSEN

Funktioner/operatorer som inte ska modifera objektet ska vara const
LAGT TILL CONST I GET_CURRENT OCH GET_VOLT
 */


class connection
{
public:
  connection(std::string);
  double get_charge() const;
  void set_charge(double);
  std::string get_name() const;

private:
  std::string name;
  double charge;
};

class component
{
public:
  component(std::string n, connection& P, connection& N);
  virtual ~component();
    //funktioner
  virtual double      get_volt()const=0;
  virtual double      get_current()const=0;
  virtual std::string get_name()const;
  virtual void        tick(double)=0;

protected:
  //Variabler ish
  std::string name;
  connection& P;
  connection& N;
};


class resistor : public component
{
public:
  resistor(std::string n,connection& P, connection& N, double o);
  ~resistor();
  double get_volt()const             override;
  double get_current()const          override;
  void tick(double)                override;

private:
  double ohm;
};


class battery : public component
{
public:
  battery(std::string n,connection& P, connection& N, double v);
  ~battery();
  double get_volt()const             override;
  double get_current()const          override;
  void tick(double)                override;

private:
  double volt;
};


class capacitor : public component
{
public:
  capacitor(std::string n, connection& P, connection& N, double f);
  ~capacitor();
  double get_volt()const             override;
  double get_current()const          override;
  void tick(double)                override;
private:
double fahrad;
double savedvolt;
};


class circuit
{
public:
circuit(std::string); //defualt construct
~circuit(); //destructor


//FUNKTIONER

void add_component(component*);
void add_connection(std::string);
void simulate(int,int,double)const;

connection& get_connection(std::string);

private:

std::vector<component*> net;
std::vector<connection> connect;
std:: string name;
};



#endif
