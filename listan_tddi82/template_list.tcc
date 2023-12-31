#include <utility>
#include <stdexcept>





template<typename T>
    List_NS::List<T>::List()
    : head{ std::make_unique<Node>() }, tail{}, sz{}
{
    T val;
    head->next = std::make_unique<Node>(val, head.get(), nullptr);
    tail = head->next.get();
}

template<typename T>
    List_NS::List<T>::List(List const& other)
    : List{}
{
    for (Node* tmp{ other.head->next.get() }; tmp != other.tail; )
    {
        push_back(tmp->value);
        tmp = tmp->next.get();
    }
}
template<typename T>
List_NS::List<T>::List(List&& tmp) noexcept
    :List{}
{
    swap(tmp);
}


template<typename T>
List_NS::List<T>::List(std::initializer_list<T> lst)
    : List{}
{
    for (auto val : lst)
    {
        push_back(val);
    }
}

template<typename T>
void List_NS::List<T>::push_front(T value)
{
    Node* old_first{ head->next.get() };
    head->next = std::make_unique<Node>(value, head.get(), std::move(head->next));
    old_first->prev = head->next.get();
    ++sz;
}


template<typename T>
void List_NS::List<T>::push_back(T value)
{
    Node* old_last{ tail->prev };
    old_last->next = std::make_unique<Node>(value, old_last, std::move(old_last->next));
    tail->prev = old_last->next.get();
    ++sz;
}

template<typename T>
bool List_NS::List<T>::empty() const noexcept
{
    return head->next.get() == tail;
}

template<typename T>
T& List_NS::List<T>::back() const noexcept
{
    return tail->prev->value;
}
template<typename T>
T& List_NS::List<T>::back() noexcept
{
    return tail->prev->value;
}

template<typename T>
  T& List_NS::List<T>::front() const noexcept
{
    return head->next->value;
}

template<typename T>
 T& List_NS::List<T>::front() noexcept
{
    return head->next->value;
}


template<typename T>
 T& List_NS::List<T>::at(int idx)
{
    return const_cast<T&>(static_cast<List const*>(this)->at(idx));
}


template<typename T>
T const& List_NS::List<T>::at(int idx) const
{
    if (idx >= sz)
        throw std::out_of_range{ "Index not found" };
    Node* tmp{ head->next.get() };
    while (idx > 0)
    {
        tmp = tmp->next.get();
        --idx;
    }
    return tmp->value;
}


template<typename T>
int List_NS::List<T>::size() const noexcept
{
    return sz;
}


template<typename T>
void List_NS::List<T>::swap(List& other) noexcept
{
    using std::swap;
    swap(head, other.head);
    swap(tail, other.tail);
    swap(sz, other.sz);
}


template<typename T>
List_NS::List<T>& List_NS::List<T>::operator=(List const& rhs)&
{
    List{ rhs }.swap(*this);
    return *this;
}


template<typename T>
List_NS::List<T>& List_NS::List<T>::operator=(List&& rhs) & noexcept
{
    swap(rhs);
    return *this;
}


template<typename T>
typename List_NS::List<T>::List_Iterator& List_NS::List<T>::List_Iterator::operator ++()
{

    current = current->next.get();

    return *this;
}


template<typename T>
typename List_NS::List<T>::List_Iterator List_NS::List<T>::List_Iterator::operator ++(int)
{
    List_Iterator tmp{ *this };
    ++* this;
    return tmp;
}


template<typename T>
typename List_NS::List<T>::List_Iterator& List_NS::List<T>::List_Iterator::operator --()
{
    current = current->prev;
    return *this;
}


template<typename T>
typename List_NS::List<T>::List_Iterator List_NS::List<T>::List_Iterator::operator --(int)
{
    List_Iterator tmp{ *this };
    --* this;
    return tmp;
}


template<typename T>
 T& List_NS::List<T>::List_Iterator::operator *()
{
    return current->value;
}


template<typename T>
bool List_NS::List<T>::List_Iterator::operator ==(List_Iterator rhs) const
{
    if ((current->next == rhs.current->next) || (current->prev == rhs.current->prev))
    {
        return true;
    }
    else
    {
        return false;
    }
}


template<typename T>
bool List_NS::List<T>::List_Iterator::operator !=(List_Iterator rhs) const
{
    if ((current->next == rhs.current->next) || (current->prev == rhs.current->prev))
    {
        return false;
    }
    else
    {
        return true;
    }
}


template<typename T>
typename List_NS::List<T>::List_Iterator List_NS::List<T>::begin()
{
    return List_Iterator{ head->next.get() };
}



template<typename T>
typename List_NS::List<T>::List_Iterator List_NS::List<T>::end()
{
    return List_Iterator{ tail };
}



template<typename T>
 T* List_NS::List<T>::List_Iterator::operator ->() const
{
    T* tmp = &(current->value);
    return tmp;
}
