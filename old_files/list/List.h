#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <vector>
#include <initializer_list>
#include <iterator>

//TODO: Indentera all kod i era filer.
//FIXAT

//TODO: er lista ska ha en pekare till första Noden och en pekare till sista noden.********
//FIXAT, NODE*LAST SKAPAT

//TODO: funktioner som inte ändrar på objektet ska deklareras const.*************
//FIXAT, GET ELEMENT,BEGIN,END & OPERATOR !=,* SATT TILL CONST

//TODO: Er iterator exponerar en Node i det publika gränssnittet. En
//användare ska inte veta hur er Lista är uppbygt
//FIXAT, LAGT I PRIVATE.
class List
   {
friend std::ostream& operator <<(std::ostream &, List const&);

private:
    class Node
    {
      public:
        ~Node(); //DEKONSTRUKTOR NODE
        //VARIABLER/PEKARE NODE
        int item;
        Node* next;
        Node* prev;
    };

    void clear();                      //Clear Funktion
    //VARIABLER/PEKARE LIST
    Node* first;
    Node* last;
    int   size;


public:
  //KONSTRUKTORER
    List();                            //standardkonstruktor
    List(List const&);                 //kopieringskonstruktor
    List(List &&);                     //flyttkonstruktor
    List(std::initializer_list<int>);  //initialized list


  //DEKONSTRUKTOR LIST
    ~List();

//FUNKTIONER LIST
    bool is_empty()  const;
    void insert(int const &);
    void remove(int const &);
    void print_list()const;
    int get_size()   const;
    int get_element(int const &) const;

//OPERATOR LIST
    List& operator =(List const&);      //kopieringstilldelning
    List& operator =(List &&);          //flytttilldelning

class It
{
  Node* current;
  public:
      //KONSTRUKTOR IT
      It();
      It(Node*);
      //OPERATOR IT
      bool operator !=(It) const;
      It& operator  ++ ();
      int operator  * () const;
};
//FUNKTIONER FÖR IT
      It begin()const;
      It end()  const;
};

#endif
