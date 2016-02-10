#ifndef QUEUE_H
#define QUEUE_H
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


enum QUEUE_ERRORS {QUEUE_EMPTY, QUEUE_FULL, BAD_QUEUE_SIZE};

template<typename T>
class queue
{
    public:
        queue(size_t s = 10);
        ~queue();
        queue(const queue<T>& other);
        queue<T>& operator=(const queue<T>& other);

        bool full();
        bool empty();
        size_t max_size();
        size_t size();
        void clear();
        void resize(size_t s);
        queue<T>& operator<<(const T& data);
        queue<T>& operator>>(T &data);
        void enqueue(const T&data);
        void dequeue(T &data);
        T& front() const;

        template<typename Y>
        friend
        ostream& operator<< (ostream &out, const queue<Y>& q);

        template<typename Y>
        friend
        istream& operator>> (istream &in, queue<Y>& q);

        template<typename Y>
        friend
        istream& operator>> (istream &in, queue<string>& q);

    private:
        T* que;
        size_t head, tail, max_qty;

        void copy(const queue<T>& other);
        void nukem();
};


template<typename T>
queue<T>::queue(size_t s )
{
    que = new T[max_qty = s+1];
    head = tail = 0;
}

template<typename T>
queue<T>::~queue()
{
    nukem();
}

template<typename T>
queue<T>::queue(const queue<T>& other)
{
    copy(other);
}

template<typename T>
queue<T>& queue<T>::operator=(const queue<T>& other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}


template<typename T>
bool queue<T>::full()
{
    return (tail + 1)%max_qty == head;
}

template<typename T>
bool queue<T>::empty()
{
    return head == tail;
}

template<typename T>
size_t queue<T>::max_size()
{
    return max_qty;
}

template<typename T>
size_t queue<T>::size()
{
    return (tail < head ? max_qty : 0) + tail - head;
}

template<typename T>
void queue<T>::clear()
{
    head = tail = 0;
}

template<typename T>
void queue<T>::resize(size_t s)
{
    delete [] que;
    que = new T[max_qty = s];
    head = tail = 0;
}

template<typename T>
queue<T>& queue<T>::operator<<(const T& data)
{
    enqueue(data);
    return *this;
}

template<typename T>
queue<T>& queue<T>::operator>>(T &data)
{
   dequeue(data);
   return *this;
}

template<typename T>
void queue<T>::enqueue(const T&data)
{
    if(full())
        throw QUEUE_FULL;
    que[tail++] = data;
    tail %= max_qty;
}

template<typename T>
void queue<T>::dequeue(T &data)
{
    if(empty())
        throw QUEUE_FULL;
    data = que[head++];
    head %= max_qty;
}

template<typename T>
T& queue<T>::front() const
{
   if(empty())
        throw QUEUE_EMPTY;
   return que[head];
}


template<typename T>
void queue<T>::copy(const queue<T>& other)
{
    que = new T[max_qty = other.max_qty];
    head = other.head;
    tail = other.tail;
    for(size_t i = head; i < tail; ++i, i%=max_qty)
            que[i] = other.que[i];
}

template<typename T>
void queue<T>::nukem()
{
    for(size_t i = 0; i < max_qty; ++i)
        que[i] = T();
    head = tail = max_qty = 0;
    delete [] que;
}

template<typename Y>
ostream& operator<<(ostream &out, const queue<Y>& q)
{
    string eol(&out == &cout ? ", " : "\n");
    for(size_t i = q.head; i < q.tail; ++i, i%= q.max_qty)
        out<<q.que[i]<<eol;
    if(&out == &cout)
        out<<"\b\b ";
    return out;
}

template<typename Y>
istream& operator>>(istream &in, queue<Y>& q)
{
    Y inputOther;
    while (in>>inputOther)
        q << inputOther;
    return in;
}

template<typename Y>
istream& operator>>(istream &in, queue<string>& q)
{
        string input;
        while(getline(in,input))
            q << input;
        return in;
}

#endif // QUEUE_H
