#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

using std::ostream;
using std::istream;

template<typename T>
class node
{
  public:
     node(const T &d = T()) : data(d), ptr(NULL)
     {}

     ~node()
     {
         data = T();
         ptr = NULL;
     }

     node(const node<T> &n)
     {
         data = n.data;
         ptr = NULL;
     }

     node<T>& operator=(const node<T>& n)
     {
         if(this != &n)
         {
             data = n.data;
             ptr = NULL;
         }
         return *this;
     }

     void setData(const T& x)
     {
         data = x;
     }

     T getData()
     {
         return data;
     }

     node<T>*& nextNode()
     {
         return ptr;
     }

     template<typename Y>
     friend
     ostream& operator<<(ostream &out, const node<Y>& n);


     template<typename Y>
     friend
     istream& operator>>(istream &in,  node<Y>& n);

  private:
    T data;
    node<T> *ptr;

};


template<typename Y>
ostream& operator<<(ostream &out, const node<Y>& n)
{
    out<<n.data<<" ";
    return out;
}


template<typename Y>
istream& operator>>(istream &in,  node<Y>& n)
{
     in>>n.data;
     return in;
}


#endif // NODE_H
