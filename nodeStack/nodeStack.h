#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include "node.h"

using std::ostream;
using std::istream;

enum STACK_ERRORS {STACK_IS_EMPTY, STACK_IS_FULL};

template<typename T>
class myStack
{
    public:
       myStack( unsigned int s = 10); //Constructor
       ~myStack(); //Deconstructor
       myStack(const myStack<T>& other); //Copy constructor
       myStack<T>& operator=(const myStack<T>& other); //Assignment operator

       myStack<T>& operator<<(const T& d); //Push, chainable
       myStack<T>& operator>>(T &d); // Pop, chainable

       T pop();                      //pops out the first element
       T top();                      //looks at the top element
       void push(const T& d);        //push elements into the array
       bool full();                  //checks if the stack is full
       bool empty();                 //check if the stack is empty
       void clear();                 //clears the stack
       int size();                   //returns the current size of the stack
       int max_size();               //returns the max size of the stack

       template<typename Y>
       friend
       ostream& operator<<(ostream &out, const myStack<Y> &stack);


       template<typename Y>
       friend
       istream& operator>>(istream &in, myStack<Y> &stack);

    private:
       node<T> *tos;
       int qty, max_qty;

       void copy(const myStack<T>& other);
       void nukem();
};

template<typename T>
myStack<T>::myStack( unsigned int s )
{
    tos = NULL;
    qty = 0;
    max_qty = s;
}

template<typename T>
myStack<T>::~myStack()
{
    nukem();
}

template<typename T>
myStack<T>::myStack(const myStack<T>& other)
{
    copy(other);
}

template<typename T>
myStack<T>& myStack<T>::operator=(const myStack<T>& other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename T>
myStack<T>& myStack<T>::operator<<(const T& d) //Push, chainable
{
    push(d);
    return *this;
}

template<typename T>
myStack<T>& myStack<T>::operator>>(T &d) // Pop, chainable
{
    d = pop();
    return *this;
}


template<typename T>
T myStack<T>::pop()
{
    if(empty())
        throw STACK_IS_EMPTY;
    --qty;
    T data = tos->getData();
    node<T>* bye = tos;
    tos = tos->nextNode();
    delete bye;
    return data;
}

template<typename T>
T myStack<T>::top()
{
    if(empty())
        throw STACK_IS_EMPTY;
    return tos->getData();
}

template<typename T>
void myStack<T>::push(const T& data)
{
    if(full())
        throw STACK_IS_FULL;
    node<T> *newNode = new node<T>(data);
    newNode->nextNode() = tos;
    tos = newNode;
    ++qty;
}

template<typename T>
bool myStack<T>::full()
{
    return qty == max_qty;
}

template<typename T>
bool myStack<T>::empty()
{
    return !tos;
}

template<typename T>
void myStack<T>::clear()
{
    nukem();
}

template<typename T>
int myStack<T>::size()
{
    return qty;
}

template<typename T>
int myStack<T>::max_size()
{
    return max_qty;
}

template<typename T>
void myStack<T>::copy(const myStack<T>& other)
{
    node<T> * ptr = tos = new node<T>(*other.tos),
            *ptr2 = other.tos;
    while(ptr2->nextNode())
    {
        ptr->nextNode() = new node<T>(ptr2->nextNode());
        ptr = ptr->nextNode();
        ptr2 = ptr2->nextNode();
    }
   qty = other.qty;
   max_qty = other.max_qty;
}

template<typename T>
void myStack<T>::nukem()
{
    node<T>* ptr;
    while(tos)
    {
        ptr = tos;
        tos = tos->nextNode();
        delete ptr;
    }
    qty = 0;
}

template<typename Y>
ostream& operator<<(ostream &out, const myStack<Y> &stack)
{
    node<Y>* ptr = stack.tos;
    while(ptr)
    {
        out<<*ptr<<std::endl;
        ptr = ptr->nextNode();
    }
    return out;
}


template<typename Y>
istream& operator>>(istream &in, myStack<Y> &stack)
{
    node<Y> input;
    while(in>>input)
       stack.push(input.getData());
    return in;
}


#endif // MYSTACK_H
