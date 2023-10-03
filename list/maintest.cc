#include "List.h"
#include <iostream>
using namespace std;

//TODO: copy assignment ska testas då den tilldelade listan har
//element i sig redan.
//FIXAT TESTCASE PÅ RAD 153

int main()
{

cout<<"TEST CASE 1: DEFAULT CONSTRUCTOR"<<endl;
  List l;

//**********************************************//
cout<<"TEST CASE 2: CHECK IF EMPTY"<<endl;
if(l.is_empty())
    {
    cout<<"tom"<<endl<<endl;
    }
else
    {
      cout<<"icke tom"<<endl<<endl;
    }

//**********************************************//
cout<<"TEST CASE 3: ADD TO LIST"<<endl;
  l.insert(1);
  l.insert(3);
  l.insert(2);
  l.insert(4);
  l.insert(2);
  l.insert(1);
  l.insert(10);
  l.insert(7);

if(l.is_empty())
  {
  cout<<"inget adderat"<<endl;
  }
else
  {
    cout<<"adderat"<<endl<<endl;
  }

//**********************************************//
cout<<"TEST CASE 4: VAD FINNS I LISTAN"<<endl;
l.print_list();

//**********************************************//
cout<<"TEST CASE 5: HUR STOR ÄR LISTAN"<<endl;
cout<<l.get_size();
cout<<endl;

//**********************************************//
cout<<"TESTA KOPIERNGSKONSTRUKTOR"<<endl;
cout<<"-----------------"<<endl;
List copy_construct (l);          //kopierar listan
cout<<"-----------------"<<endl;
cout<<"skriver ut nya listan"<<endl;
cout<<"-----------------"<<endl;
copy_construct.print_list();      //skriver ut nya listan
copy_construct.insert(7);         //lägger till en sjua i den nya listan
cout<<"-----------------"<<endl;
cout<<"skriver ut nya listan med en extra sjua"<<endl;
cout<<"-----------------"<<endl;
copy_construct.print_list();
cout<<"-----------------"<<endl;
cout<<"skriver ut gamla listan"<<endl;
cout<<"-----------------"<<endl;
l.print_list();                   //skriver ut gamla listan och jämför att dem ska vara likadana förutom att den nya ska ha en extra 7:a
cout<<endl<<endl;

//**********************************************//
cout<<"TESTA KOPIERINGSTILLDELNING"<<endl;
cout<<"-----------------"<<endl;
List copy_asign;
copy_asign=l;
cout<<"-----------------"<<endl;
cout<<"skriv ut kopierade listan"<<endl;
cout<<"-----------------"<<endl;
copy_asign.print_list();
cout<<"-----------------"<<endl;
cout<<"skriv ut orginal listan"<<endl;
cout<<"-----------------"<<endl;
l.print_list();

//**********************************************//
cout<<"TESTA L=L"<<endl;
l=l;
l.print_list();
cout<<endl;

//**********************************************//
cout<<"TA BORT ELEMENT PÅ DEN PLATS DU SKRIVER IN"<<endl;
cout<<"-----------------"<<endl;
cout<<"försöker ta bort elementet på index 0"<<endl;
cout<<"-----------------"<<endl;
l.remove(0);                    //går ej ta bort element på index 0
cout<<"-----------------"<<endl;
cout<<"försöker ta bort element med för stort index"<<endl;
cout<<"-----------------"<<endl;
l.remove(20);                   //element med index 20 finns ej
cout<<"-----------------"<<endl;
cout<<"tar bort element nr 8(sista),nr 3(i mitten) och nr 1(första) "<<endl;
cout<<"-----------------"<<endl;
l.remove(8);                    //tar bort det element som finns på plats nummer 8 i listan
l.remove(3);                    //tar bort 3:de elementet i listan
l.remove(1);                    //tar bort första elementet i listan
l.print_list();                 //printar "nya" listan
cout<<endl;

//**********************************************//
cout<<"TESTA TA BORT ELEMENT I TOM LISTA"<<endl;
cout<<"-----------------"<<endl;
List empty_list;
empty_list.remove(3);            //går ej ta bort då listan är tom

//**********************************************//
cout<<"ÅTKOMST TEST LISTA "<<endl;
cout<<"-----------------"<<endl;
List atkomstlist {1,2,3,0,0,0,7,8,9,10};
cout<<"Ska komma åt plats 5, som är en 2a:"<<endl;
cout<<atkomstlist.get_element(5)<<endl;
cout<<"Ska komma åt plats 1;2;3, som är en nollor:"<<endl;
cout<<atkomstlist.get_element(1)<<"-"<<atkomstlist.get_element(2)<<"-"<<atkomstlist.get_element(3)<<endl;
cout<<"Ska komma åt plats 11, som ej finns:"<<endl;
cout<<atkomstlist.get_element(11)<<endl;
cout<<endl;

//**********************************************//
cout<<"TESTA FLYTTKONSTRUKTOR"<<endl;
List move_test{move(l)};          //listan l flyttas till move_test
l.print_list();                   //Listan l är nu tom och skriver ej ut något
cout<<"-----------------"<<endl;
move_test.print_list();           //skriver ut det som l innehöll

//**********************************************//
cout<<"TESTA FLYTTILLDELNING"<<endl;
l=move(move_test);                //flyttar tillbaka listan till l
move_test.print_list();           //denna lista är nu tom och skriver ej ut något
cout<<"-----------------"<<endl;
l.print_list();                   //skriver nu ut listan

//**********************************************//
cout<<"TESTA FLYTTA TILL LISTA SOM REDAN HAR"<<endl;
List move_test1{2,3,4,5};          //Skapar lista med värden
move_test1=move(l);                //raderar denns värden och ersätter med l.
move_test1.print_list();
move_test1=move(move_test1);       //går ej att flytta till sig själv
cout<<"INITIALIZED LIST "<<endl;
cout<<"-----------------"<<endl;
List il {2, 3 , 6 , 8};
cout<<"This is the list: "<<endl;
il.print_list();

//**********************************************//
cout<<"BONUS"<<endl;
cout<<"-----------------"<<endl;
List lista{2};
for(List::It it = lista.begin(); it != lista.end(); ++it)
{
  cout << *it << endl;
}

//**********************************************//
cout<<endl<<"INITIALIZED LIST "<<endl;
cout<<"-----------------"<<endl;
List i {7,8,9};
cout<<"This is the list: "<<endl;
i.remove(1);
cout<<*i.end();

//**********************************************//
cout<<endl<<endl<<"DELETE LISTS"<<endl;
cout<<"-----------------"<<endl;



    return 0;
}
