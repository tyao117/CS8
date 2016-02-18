#ifndef DEQUE_H
#define DEQUE_H
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;
using std::string;
using std::stringstream;


enum DQUE_ERRORS{FRONT, BACK, DFULL, DEMPTY,SAME};

template<typename T>
class deque
{
    public:
        deque(size_t s = 10, DQUE_ERRORS which = SAME);
        ~deque();
        deque(const deque<T>& );
        deque<T>& operator=(const deque<T>& other);

        bool full();
        bool empty();
        size_t size();
        size_t max_size();
        void clear();
        DQUE_ERRORS getEnd();
        void setEnd(DQUE_ERRORS end);
        void resize(size_t s = 10);
        const T& peek(DQUE_ERRORS where);
        void enqueue(const T& data, DQUE_ERRORS where = SAME);
        const T& dequeue(DQUE_ERRORS where = SAME);
        deque<T>& operator<<(const T &data);
        deque<T>& operator>>(T &data);

        template<typename U>
        friend
        ostream& operator<<(ostream &out, const deque<U> &other);

        template<typename U>
        friend
        istream& operator>>(istream &in,  deque<U> &other);

    private:
        T *dque;
        size_t head, tail, max_qty, qty;
        DQUE_ERRORS whichEnd;
        void copy(const deque<T>& other);
        void nukem();
};

template<typename T>
deque<T>::deque(size_t s, DQUE_ERRORS e)
{
    whichEnd = e;
    resize(s);
}

template<typename T>
deque<T>::~deque()
{
    nukem();
}

template<typename T>
deque<T>::deque(const deque<T>& other)
{
    copy(other);
}

template<typename T>
deque<T>& deque<T>::operator=(const deque<T>& other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}


template<typename T>
bool deque<T>::full()
{
    return qty == max_qty;
}

template<typename T>
bool deque<T>::empty()
{
    return !qty;
}

template<typename T>
size_t deque<T>::size()
{
    return qty;
}

template<typename T>
size_t deque<T>::max_size()
{
    return max_qty;
}

template<typename T>
void deque<T>::clear()
{
    head = tail;
    qty = 0;
}

template<typename T>
void deque<T>::resize(size_t s )
{
    delete [] dque;
    dque = new T[max_qty = s]();
    head = tail = qty = 0;
}


template<typename T>
DQUE_ERRORS deque<T>::getEnd()
{
    return whichEnd;
}

template<typename T>
void deque<T>::setEnd(DQUE_ERRORS end)
{
    whichEnd = end;
}

template<typename T>
const T& deque<T>::peek(DQUE_ERRORS where)
{
    return where == BACK ? dque[tail] : dque[head];
}

template<typename T>
void deque<T>::enqueue(const T& data, DQUE_ERRORS where )
{
    if(full())
        throw DFULL;
    if(where == SAME ? whichEnd : where)
        dque[tail = (tail+1)%max_qty] = data;
    else
        dque[head = --head < 0 ? max_qty-1 : head] = data;
    ++qty;
}

template<typename T>
const T& deque<T>::dequeue(DQUE_ERRORS where)
{
    if(empty())
        throw DEMPTY;
    T data;
    if(where == SAME ? whichEnd : where)
    {
        data = dque[tail];
        tail = --tail < 0 ? max_qty-1:tail;
    }
    else
    {
        data = dque[head++];
        head %= max_qty;
    }
    --qty;
}

template<typename T>
void deque<T>::copy(const deque<T>& other)
{
    head = other.head;
    tail = other.tail;
    qty = other.qty;
    whichEnd = other.whichEnd;
    max_qty = other.max_qty;
    dque = new T[max_qty];
    for(size_t i = 0; i < max_qty; ++i )
        dque[i] = other.dque[i];
}

template<typename T>
void deque<T>::nukem()
{
    for(size_t i = head; i!=tail; i= (i+1)%max_qty)
        dque[i] = T();
    delete [] dque;
    dque = NULL;
    head = tail = max_qty = qty = 0;
}

template<typename U>
ostream& operator<<(ostream &out, const deque<U> &other)
{
    for(size_t i = other.head; i != other.tail; i = (i+1)%other.max_qty)
        out<<other.dque[i]<<", ";
    out<<"\b\b";
    return out;
}

template<typename U>
istream& operator>>(istream &in,  deque<U> &other)
{
    U data;
    while(in>>data)
        other<<data;
    return in;
}

#endif // DEQUE_H
