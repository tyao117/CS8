#ifndef LinkedListQueue_H
#define LinkedListQueue_H
#include "linkedlist.h"
#include "basenode.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
enum QUEUE_ERRORS {QUEUE_EMPTY,QUEUE_FULL};

using std::istream;
using std::ostream;

template<typename T>
class LinkedListQueue : public linkedList
{
public:
    LinkedListQueue(size_t size = 10);
    ~LinkedListQueue();
    LinkedListQueue(const LinkedListQueue<T>&other);
    LinkedListQueue<T>& operator = (const LinkedListQueue<T> &other);

    LinkedListQueue<T>& operator <<(const T& d); //Push chainable
    LinkedListQueue<T>& operator >>(T &d);       //Pop chainable

    T dequeue();                      //pops out the first element
    T top();                      //looks at the top element
    void push(const T& d);        //push elements into the array
    bool full();                  //checks if the stack is full
    bool empty();                 //check if the stack is empty
    void clear();                 //clears the stack
    size_t size();                //returns the current size of the stack
    size_t max_size();            //returns the max size of the stack

    template<typename Y>
    friend
    ostream& operator<<(ostream &out, const LinkedListQueue<Y> &stack);

    template<typename Y>
    friend
    istream& operator>>(istream &in, LinkedListQueue<Y> &stack);

private:
    void copy(const LinkedListQueue<T>& other);
    void nukem();
};

template<typename T>
LinkedListQueue<T>::LinkedListQueue(size_t size)
{
    maxQty = size;
    anchor = new baseNode;
}

template<typename T>
LinkedListQueue<T>::~LinkedListQueue()
{
   nukem();
   delete anchor;
}

template<typename T>
LinkedListQueue<T>::LinkedListQueue(const LinkedListQueue<T> &other)
{
    copy (other);
}

template<typename T>
LinkedListQueue<T>& LinkedListQueue<T>::operator = (const LinkedListQueue<T> &other)
{
    if (this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}
template<typename T>
LinkedListQueue<T>& LinkedListQueue<T>::operator <<(const T& d) //Push chainable
{
   push(d);
   return *this;
}

template<typename T>
LinkedListQueue<T>& LinkedListQueue<T>::operator >>(T &d)       //Pop chainable
{
    d = pop();
    return d;
}

template<typename T>
T LinkedListQueue<T>::dequeue()                      //pops out the first element
{
    if (empty())
        throw STACK_EMPTY;
    baseNode *ptr = anchor->nextNode();
    T data = *(T*)(ptr->getFirst());
    linkedList::erase(ptr);
    return data;
}

template<typename T>
T LinkedListQueue<T>::top()                     //looks at the top element
{
    if (empty())
        throw STACK_EMPTY;
    baseNode *ptr = anchor->nextNode();
    //for (;ptr->nextNode(); ptr = ptr->nextNode());
    T data = *(T*)(ptr->getFirst());
    return data;
}

template<typename T>
void LinkedListQueue<T>::push(const T& d)        //push elements into the array
{
    if (!(qty-maxQty))
        throw STACK_EMPTY;
    baseNode* ptr = new baseNode();
    ptr->setFirst(new T(d));
    linkedList::insertTail(ptr);
}

template<typename T>
bool  LinkedListQueue<T>::full()                  //checks if the stack is full
{
    return !(qty-maxQty);
}

template<typename T>
bool  LinkedListQueue<T>::empty()                 //check if the stack is empty
{
    return !qty;
}

template<typename T>
void  LinkedListQueue<T>::clear()                //clears the stack
{
    nukem();
}

template<typename T>
size_t  LinkedListQueue<T>::size()                   //returns the current size of the stack
{
    return qty;
}
template<typename T>
size_t LinkedListQueue<T>::max_size()
{
    return maxQty;
}

template<typename T>
void  LinkedListQueue<T>::nukem()                //clears the stack
{
    baseNode *ptr = anchor, *bye;
    while(ptr->nextNode())
    {
        bye = ptr->nextNode();
        ptr = ptr->nextNode();
        delete bye;
    }
    anchor->nextNode() = NULL;
    qty = 0;
}

template<typename T>
void LinkedListQueue<T>::copy(const LinkedListQueue<T>& other)
{
    qty = other.qty;
    maxQty = other.maxQty;
    for(baseNode *ptr = other.anchor; ptr; ptr = ptr->nextNode())
        push(ptr->getFirst());
 }

//friends
template<typename Y>
ostream& operator<<(ostream &out, const LinkedListQueue<Y> &stack)
{
    baseNode *ptr = stack.anchor->nextNode();
    while(ptr)
    {
        out<<*(Y*)(ptr->getFirst())<<std::endl;
        ptr = ptr->nextNode();
    }
    return out;
}

template<typename Y>
istream& operator>>(istream &in, LinkedListQueue<Y> &stack)
{
//    node<Y> input;
//    while(in>>input)
//       stack.push(input.getData());

    baseNode ptr;
    while(in>>ptr)
        stack.push(ptr.getFirst());
    return in;
}
#endif // LinkedListQueue_H
