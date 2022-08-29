
#include "List.h"
#include <initializer_list>
#include <iostream>
using namespace std;

//KONSTRUKTOR DEFAULT
List::List()                 : first(nullptr), last(nullptr), size{0} { cout<<"List default constructor called"<<endl<<endl;}
List::It::It()               : current(nullptr) {}
List::It::It (Node* current) : current(current){}
//KONSTRUKTOR
List::List(std::initializer_list<int> sortlist)
:first(nullptr), last(nullptr), size{0}
{cout<<"initializer list constructor called, size of init list: "<<sortlist.size()<< endl;
  for (int n : sortlist)
  {
    insert(n);
  }
}


//TODO: Här försöker ni sortera en redan sorterad lista vid varje
//insättning. Detta är onödigt.
//FIXAT ONÖDIG SORTERING VID KOPIERING

//kopieringskonstruktor
List::List(List const& l) :first(nullptr), last(nullptr), size{l.size}
{
  cout<<"List copy constructor called"<<endl;
  Node* tmp=l.first;
  if(l.first != nullptr)
  {
    first=new Node{tmp->item,nullptr,nullptr};
    last=first;

    for(int i{1}; i<l.size; i++)
    {
      tmp=tmp->next;
      last->next=new Node{tmp->item,nullptr,last};
      last=last->next;
    }
  }
  else
  {
    cout<<"finns inget att kopiera"<<endl<<endl;
  }
}

//FLYTTKONSTRUKTOR
List::List(List && l) :first(nullptr), last(nullptr), size{0}
  {
    cout<<"List move constructor called"<<endl;
    first=l.first;
    size=l.size;
    l.first=nullptr;
    l.size=0;
  }

//TODO: Ta bort onödig kod/kommentarer
//FIXAT

//DESTRUKTOR LIST OCH NODE
List::~List()
{
  cout<<"List is being deleted"<<endl;
  clear();
}
List::Node::~Node()
{
}

//////////////////////Tar bort hela listan////////////////////////
void List::clear()
{
  Node* curr = first;
  while(first != nullptr)
  {
    curr->prev=curr;
    curr = curr->next;
    delete first;
    first = curr;
  }
  delete curr;
}


//TODO: Vad händer med de gamla värdena vid tilldelning av en ny lista?
//FIXAT: Nu raderar vi dem gamla värdena innan vi tilldelar listan dem nya

//Efter detta är fixat, vad händer i fallet då t.ex. l = l?
//OM L = L KOMMER ETT MEDDELANDE SOM SÄGER ATT MAN INTE KAN TILLDELA EN LISTA SIG SJÄLV
//OCH SEDAN GÅ UT UR OPERATORN

//TODO: Här försöker ni sortera en redan sorterad lista vid varje
//insättning. Detta är onödigt.
// FIXAT SÅ DEN EJ SORTERAS TVÅ GÅNGER

////////////////////kopieringstilldelning//////////////////////////
List& List::operator =(List const& rhs)
{
  Node* tmp=rhs.first;

  if(first==rhs.first)
  {
    cout<<"Du försöker kopiera listan till sig själv"<<endl;
  }
  else
  {

    if(first != nullptr)
    {
      clear();
      size=0;
    }

    if(rhs.first != nullptr)
    {
    first=new Node{tmp->item,nullptr,nullptr};
    last=first;

      for(int i{1}; i<rhs.size; i++)
      {
        tmp=tmp->next;
        last->next=new Node{tmp->item,nullptr,last};
        last=last->next;
        ++size;
      }
    ++size;
    }
  else
  {
  cout<<"finns inget att kopiera"<<endl<<endl;
  }
  }
  return *this;
}

////////////////////flytttilldelning//////////////////////////
List& List::operator =(List && rhs)
{
  if(first==rhs.first)
  {
    cout<<"Du försöker flytta listan till sig själv"<<endl;
  }
  else
  {
    if(first != nullptr)
    {
      clear();
      size=0;
    }
  first=rhs.first;
  size=rhs.size;
  rhs.first=nullptr;
  rhs.size=0;
  }
  return *this;
}
/////////////////////sätt in element i listan///////////////////////////////////////
void List::insert(int const & i)
{
  if (first==nullptr)
  {
    first=new Node{i,nullptr,nullptr};
    last=first;
  }
  else
  {
    Node* curr=new Node{i,nullptr,nullptr};
    Node* tmp=first;

  //OM PEKARE HAR ENDAST EN NOD I SIN LISTA
  //curr->item är större än första noden

        if((first->next==nullptr) & (curr->item>first->item))
        {
          first->next=curr;
          curr->prev=first;
          last=curr;
          tmp=nullptr;
        }

  //curr->item är mindre eller lika stor som första noden
        if((first->prev==nullptr) & (curr->item<=first->item))
        {
          curr->next=first;
          first->prev=curr;
          first=curr;
          tmp=nullptr;
        }
  //OM DET FINNS FLER NODER
        while(tmp!=nullptr)
        {
          //om curr->item ej är större än nästa item i listan
          if((curr->item<=tmp->item) & (tmp!=nullptr))
          {
            curr->next=tmp;
            curr->prev=tmp->prev;
            curr->prev->next=curr;
            tmp->prev=curr;
            tmp=nullptr;
          }
          //om curr->item är större än sista elementet
          else if((curr->item>tmp->item) & (tmp->next == nullptr))
          {
            curr->prev=tmp;
            tmp->next=curr;
            last=curr;
            tmp=nullptr;
          }
          //annars kolla nästa element
          else
          {
            tmp=tmp->next;
          }
        }
}
++size;
}

//////////////////ta bort element ur listan///////////////////////////////////////
void List::remove(int const& index)
{
  Node* tmp=first;
  if(is_empty()==false)
  {
  if ((index<=size) & (index>0))
  {
    if(size==1)
    {
      first=nullptr;
      last=nullptr;
      delete tmp;
    }

    //ta bort första elementet i listan
    else if(index==1)
    {
      first=first->next;
      first->prev=nullptr;
      tmp->next=nullptr;
      delete tmp;
    }
    //ta bort något annat element i listan
    else
    {
      for(int i{1}; i<index; i++)
      {
        tmp=tmp->next;
      }
      //ta bort sista elementet i Listan
      if(tmp->next==nullptr)
      {
        last=last->prev;
        tmp->prev->next=nullptr;
        tmp->prev=nullptr;
        delete tmp;
      }
      //ta bort ett element i mitten av listan
      else
      {
        tmp->next->prev=tmp->prev;
        tmp->prev->next=tmp->next;
        tmp->next=nullptr;
        tmp->prev=nullptr;
        delete tmp;
      }
    }
    --size;
  }
  else
  {
    cout<<"Det index du skrev in finns ej i listan"<<endl<<endl;
  }
  }
  else
  {
    cout<<"Listan har inga element att ta bort"<<endl<<endl;
  }
}
/////////////////////GET ELEMENT///////////////////////////////
int List::get_element(int const & index) const
{
  Node* tmp = first;

  if ((tmp != nullptr) && (index <= size))
  {

    for (int i{1}; i<index;i++)
    {
      tmp = tmp->next;
  }

    return tmp->item;
  }
    else
    {
      cout<<"Index finns ej";
      return 0;
    }
}


////////////returnerar listans storlek////////////////////////
int List::get_size() const
{
  return size;
}

/////////////////utskrift operator//////////////////////////////////////
ostream& operator <<(ostream& lhs,List const & rhs)
{
  for (int i{}; i<rhs.size; ++i)
  {
    lhs<<rhs.first->item;
  }
  return lhs;
}

//////////////////kollar om listan är tom/////////////////////////////////
bool List::is_empty()const
{
  if(first==nullptr)
  {
    return true;
  }
    return false;
}

///////////////////////skriver ut listan//////////////////////////////
void List::print_list()const
{
  Node* tmp=first;
  for(int i{}; i<size; i++)
  {
    cout<<tmp->item<<endl;
    tmp=tmp->next;
  }
}


///////////////////////LIST BEGIN//////////////////////////////
List::It List::begin()const
{
  return It{first};
}

//TODO: Man ska ej behöva iterera genom hela listan för att hitta
//sista noden i denna lista
//FIXAT

///////////////////////LIST END//////////////////////////////
List::It List::end()const
{
    return It{last};
}



///////////////////////OPERATORER///////////////////////////////////

List::It& List::It::operator ++()
{
  current=current->next;
  return *this;
}

int List::It::operator *() const
{
  int g{};
  if(current!=nullptr)
  {
    g=current->item;
  }
  return g;
}

bool List::It::operator !=(It rhs) const
{
if(current==rhs.current)
{
  if(rhs.current!=nullptr)
  {
    cout<<current->item;
  }
  return false;

}
else
{
  return true;
}
}
