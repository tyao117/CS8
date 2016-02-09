#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "node.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::ostream;
using std::istream;

enum PQ_ERRORS {EMPTY_PQ, FULL_PQ};

template<typename D, typename P>
class priorityQueue
{
    public:
        priorityQueue(size_t m = 10);
        ~priorityQueue();
        priorityQueue(const priorityQueue<D,P> &other);
        priorityQueue<D,P>& operator=(const priorityQueue<D,P> &other);
        bool full();
        bool empty();
        void resize(size_t newSize = 10);
        size_t size();
        size_t max_size();
        void clear();
        void enqueue(const D& data, const P& priority);
        const D& peek() const;
        void dequeue(D& data);
        priorityQueue<D,P>& operator>>(D &data);

        template<typename T, typename U>
        friend
        ostream& operator<<(ostream &out, const priorityQueue<T,U> &queue);


        template<typename T, typename U>
        friend
        istream& operator>>(istream &in, priorityQueue<T,U> &queue);



    private:
        node<D,P> *head, *tail;
        size_t qty, max_qty;

        void copy(const priorityQueue<D,P> &other);
        void nukem();
};


template<typename D, typename P>
priorityQueue<D,P>::priorityQueue(size_t m )
{
    resize(m);
}

template<typename D, typename P>
priorityQueue<D,P>::~priorityQueue()
{
    nukem();
}

template<typename D, typename P>
priorityQueue<D,P>::priorityQueue(const priorityQueue<D,P> &other)
{
    copy(other);
}

template<typename D, typename P>
void priorityQueue<D,P>::clear()
{
    resize(max_qty);
}

template<typename D, typename P>
priorityQueue<D,P>& priorityQueue<D,P>::operator=(const priorityQueue<D,P> &other)
{
    if(this != other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename D, typename P>
bool priorityQueue<D,P>::full()
{
    return qty == max_qty;
}

template<typename D, typename P>
bool priorityQueue<D,P>::empty()
{
    return !head;
}

template<typename D, typename P>
void priorityQueue<D,P>::resize(size_t newSize)
{
    nukem();
    max_qty = newSize;
}

template<typename D, typename P>
size_t priorityQueue<D,P>::size()
{
    return qty;
}

template<typename D, typename P>
size_t priorityQueue<D,P>::max_size()
{
    return max_qty;
}

template<typename D, typename P>
void priorityQueue<D,P>::enqueue(const D& data, const P& priority)
{
    if(full())
        throw FULL_PQ;
    node<D,P> *newNode = new node<D,P>(data,priority);
    if(!head)
        head = tail = newNode;
    else
    {
       node<D,P> *ptr;
       for( ptr = tail;
            ptr && (*newNode > *ptr);
            ptr = ptr->prevNode());
       switch((size_t)ptr)
       {
           case (size_t)NULL: newNode->nextNode() = head;
                              head->prevNode() = newNode;
                              head = newNode;
                              break;

             default:         if(ptr == tail)
                              {
                                tail->nextNode() = newNode;
                                newNode->prevNode() = tail;
                                tail = newNode;
                              }
                              else
                              {
                                newNode->prevNode() = ptr;
                                newNode->nextNode() = ptr->nextNode();
                                ptr->nextNode()->prevNode() = newNode;
                                ptr->nextNode() = newNode;
                              }
       }
    }
    ++qty;
}

template<typename D, typename P>
const D& priorityQueue<D,P>::peek() const
{
    if(!head)
        throw EMPTY_PQ;
    return head->getData();
}

template<typename D, typename P>
void priorityQueue<D,P>::dequeue(D& data)
{
    if(!head)
        throw EMPTY_PQ;
    node<D,P> *ptr = head;
    data = head->getData();
    head = head->prevNode();
    head->nextNode() = NULL;
    delete ptr;
}

template<typename D, typename P>
priorityQueue<D,P>& priorityQueue<D,P>::operator>>(D &data)
{
    dequeue(data);
    return *this;
}


template<typename D, typename P>
void priorityQueue<D,P>::copy(const priorityQueue<D,P> &other)
{
    qty = other.qty;
    max_qty = other.max_qty;
    for(node<D,P> *ptr = other.head; ptr; ptr = ptr->prevNode())
        enqueue(ptr->getData(), ptr->getPriority());
}

template<typename D, typename P>
void priorityQueue<D,P>::nukem()
{
    for(node<D,P> *ptr = head; ptr; ptr = head)
    {
        head = head->nextNode();
        delete ptr;
    }
    qty = 0;
    max_qty = 0;
    head = tail = NULL;
}

template<typename T, typename U>
ostream& operator<<(ostream &out, const priorityQueue<T,U> &queue)
{
    for(node<T,U> *ptr = queue.head; ptr; ptr = ptr->prevNode())
       if(&out == &cout)
            out<<ptr->getData();
        else
            cout<<ptr->getData()<<" /007/007 "<<ptr->getPriority()<<endl;
     return out;
}

template<typename T, typename U>
istream& operator>>(istream &in, priorityQueue<T,U> &queue)
{
      stringstream ss;
      string line;
      T data;
      U priority;
      if(&in == &cin)
         while(1)
         {
             cout<<"Data: ";
             getline(in,line);
             if(!line.size())
                 break;
             ss<<line;
             ss>>data;
             ss.clear();
             cout<<"Priority: ";
             getline(in,line);
             ss<<line;
             ss>>priority;
             ss.clear();
             queue.enqueue(data,priority);
         }
      else
         while(getline(in,line))
         {
             ss<<line.substr(0,line.find(" /007/007 "));
             ss>>data;
             ss.clear();
             ss<<line.substr(line.find(" /007/007 "+4));
             ss>>priority;
             ss.clear();
             queue.enqueue(data,priority);
         }
      return in;
}


#endif // PRIORITYQUEUE_H
