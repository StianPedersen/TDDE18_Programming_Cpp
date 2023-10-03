#ifndef LIST_H
#define LIST_H
#include <memory>
#include <initializer_list>
#include <iterator>
#include "catch.hpp"

//TODO: Node-konstruktorn ska ta en unique_ptr till next. FIXAT LAGT TILL EN NY KONSTRUKTOR SOM TAR IN UNIQUE_PTR PÅ NEXT.

//TODO: back() och front() ska returnera en referens då T kan vara en
//komplex datatyp vi inte vill kopiera. LAGT TILL REFERENS PÅ BACK() OCH FRONT()

//TODO: List_Iterator ska ligga publikt. Efter att ni ändrat detta,
//tänk på att endast Listan ska kunna skapa en List_Iterator via begin
//och end.
//Hint: Lägg List_iterator-konstruktorer där användaren inte kan nå dem. KLART LAGT LIST_ITERATOR KONSTRUKTORN I PRIVATE

//TODO: begin() och end() ska inte vara const. Användaren ska kunna
//ändra på objektet som ligger på platsen begin/end i samma rad som
//funktionen anropas. TAGIT BORT CONST

//TODO: Ni ska inte använda Unique_ptr.release(). TAGIT BORT! ANVÄNDER MOVE ISTÄLLET!

//TODO: ni testar -> på rb vilket inte är en List_Iterator. Alltså
//använder den inte er -> funktion.
//Hint: Testa den istället på ett objekt ni endast kört begin()/end() på. ÄNDRAT I TEST-CASET SÅ VI SKAPAR "AUTO IT = lst.BEGIN() osv..."

//TODO: Kompilerar ej. Ger felmeddelandet error: expected
//nested-name-specifier before ?T' typename T
//List_NS::List<T>::front() const noexcept.
//T är ingen nästlad datatyp. TAGIT BORT TYPENAME PÅ DEM FUNKTIONERNA DÄR DET INTE BEHÖVS



namespace List_NS
{

    template <typename T>
    class List
    {

    private:

        struct Node
        {
            Node() = default;
            Node(T v, Node* p, Node* n)
                : value{ v }, prev{ p }, next{ n } {}

            Node(T v, Node* p, std::unique_ptr<Node> n)
                : value{ v }, prev{ p }, next{std::move( n ) } {}

            T value{};
            Node* prev{};
            std::unique_ptr<Node> next{};
            ~Node() = default;
        };

        std::unique_ptr<Node> head{};
        Node* tail{};
        int sz{};


        public:
            class List_Iterator
            {
                friend List;
            private:

                List_Iterator(Node* c) : current{ c } {};

            public:
                typedef std::bidirectional_iterator_tag iterator_category;
                typedef T   value_type;
                typedef int difference_type;
                typedef T* pointer;
                typedef T& reference;



                List_Iterator& operator ++();
                List_Iterator operator ++(int);

                List_Iterator& operator --();
                List_Iterator operator --(int);

                T& operator *();
                bool operator ==(List_Iterator) const;
                bool operator != (List_Iterator)const;
                T* operator ->()const;
                Node* current;

            };

        List();
        ~List()=default;
        List(List const&);
        List(List&&) noexcept;
        List(std::initializer_list<T>);

        List& operator=(List const&)&;
        List& operator=(List&&)&noexcept;

        void push_front(T);
        void push_back(T);

        T& back() const noexcept;
        T& back() noexcept;

        T& front() const noexcept;
        T& front() noexcept;

        T& at(int idx);
        T const& at(int idx) const;

        int size() const noexcept;
        bool empty() const noexcept;

        void swap(List& other) noexcept;

        List_Iterator begin();
        List_Iterator end();

    };




#include "template_list.tcc"
}

#endif //"LIST_H"
