#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <typeinfo>

using std::cin;
using std::cout;
using std::ostream;
using std::istream;
using std::endl;
using std::string;
using namespace std;

enum STACK_ERRORS {STACK_EMPTY, STACK_FULL, BAD_STACK_SIZE};

template<typename T>
class arrayStack
{
    public:
        arrayStack(size_t s = 10);
        ~arrayStack();
        arrayStack(const arrayStack<T>& other);
        arrayStack<T>& operator=(const arrayStack<T>& other);

        bool full();
        bool empty();
        size_t max_size();
        size_t size();
        void clear();
        void resize(size_t s);
        arrayStack<T>& operator<<(const T& data);
        arrayStack<T>& operator>>(T &data);
        void enqueue(const T&data);
        void dequeue(T &data);
        T& front() const;

        template<typename Y>
        friend
        ostream& operator<<(ostream &out, const arrayStack<Y>& q);

        template<typename Y>
        friend
        istream& operator>>(istream &in, arrayStack<Y>& q);

        friend
        istream& operator>>(istream &in, string q);

    private:
        T* que;
        size_t head, tail= 0, max_qty;

        void copy(const arrayStack<T>& other);
        void nukem();
};

template<typename T>
arrayStack<T>::arrayStack(size_t s )
{
    que = new T[max_qty = s+1];
    head = tail = 0;
}

template<typename T>
arrayStack<T>::~arrayStack()
{
    nukem();
}

template<typename T>
arrayStack<T>::arrayStack(const arrayStack<T>& other)
{
    copy(other);
}

template<typename T>
arrayStack<T>& arrayStack<T>::operator=(const arrayStack<T>& other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}


template<typename T>
bool arrayStack<T>::full()
{
    return (head + 1) == max_qty;
}

template<typename T>
bool arrayStack<T>::empty()
{
    return head == tail;
}

template<typename T>
size_t arrayStack<T>::max_size()
{
    return max_qty;
}

template<typename T>
size_t arrayStack<T>::size()
{
//    return (tail < head ? max_qty : 0) + tail - head;
    return (head - tail);
}

template<typename T>
void arrayStack<T>::clear()
{
    head = tail = 0;
}

template<typename T>
void arrayStack<T>::resize(size_t s)
{
    delete [] que;
    que = new T[max_qty = s +1];
    head = tail = 0;
}

template<typename T>
arrayStack<T>& arrayStack<T>::operator<<(const T& data)
{
    enarrayStack(data);
    return *this;
}

template<typename T>
arrayStack<T>& arrayStack<T>::operator>>(T &data)
{
   dearrayStack(data);
   return *this;
}

template<typename T>
void arrayStack<T>::enarrayStack(const T&data)
{
    if(full())
        throw arrayStack_FULL;
    que[tail++] = data;
    tail %= max_qty;
}

template<typename T>
void arrayStack<T>::dearrayStack(T &data)
{
    if(empty())
        throw arrayStack_FULL;
    data = que[head++];
    head %= max_qty;
}

template<typename T>
T& arrayStack<T>::front() const
{
   if(empty())
        throw arrayStack_EMPTY;
   return que[head];
}


template<typename T>
void arrayStack<T>::copy(const arrayStack<T>& other)
{
    que = new T[max_qty = other.max_qty];
    head = other.head;
    tail = other.tail;
    for(size_t i = head; i < tail; ++i, i%=max_qty)
            que[i] = other.que[i];
}

template<typename T>
void arrayStack<T>::nukem()
{
    for(size_t i = 0; i < max_qty; ++i)
        que[i] = T();
    head = tail = max_qty = 0;
    delete [] que;
}

template<typename Y>
ostream& operator<<(ostream &out, const arrayStack<Y>& q)
{
    string eol(out == cout ? ", " : "\n");
    for(size_t i = q.head; i < q.tail; ++i, i%= q.max_qty)
        out<<q.que[i]<<eol;
    if(out == cout)
        out<<"\b\b ";
    return out;

}

template<typename Y>
istream& operator>>(istream &in, arrayStack<Y>& q)
{
//    string input;
//    Y inputOther;
//    if(string(typeid(Y).name()) == "Ss")
//        while(getline(in,input))
//            q << input;
//    else
//        while(in>>inputOther)
//            q << inputOther;
//    return in;
    Y inputOther;
    while (in>>inputOther)
        q << inputOther;
    return in;

}

istream& operator>>(istream &in, string& q)
{
        string input;
        while(getline(in,input))
            q << input;
        return in;
}

#endif // ARRAYSTACK_H
