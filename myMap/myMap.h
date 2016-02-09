#ifndef MYMAP_H
#define MYMAP_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "linkedlist.h"
#include "node.h"
using std ::endl;
template<typename K, typename V>
class myMap : public linkedList
{
    public:
        myMap(unsigned int size = 500)
        {
            maxQty = size;
            anchor = new baseNode;
        }
        ~myMap();
        myMap(const myMap<K,V> &other);
        myMap<K,V>& operator=(const myMap<K,V> &other);
        const V operator[] (K index)const; //[]operator handle return
        V& operator[](const K& index);// [] operator handle assigning
        baseNode* insert(const K& key, const V& value);
        void erase(const K& key);
        void clear();

        template<typename k, typename v>
        friend
        ostream& operator<<(ostream &out, const myMap<k,v> &other);

        template<typename k, typename v>
        friend
        istream& operator>>(istream &in, myMap<k,v> &other);


    private:

        void copy(const myMap<K,V> &other);
        void nukem();
        baseNode * find(const K& index);
};

template<typename K, typename V>
myMap<K,V>::~myMap()
{
    delete anchor;
    nukem();
}

template<typename K, typename V>
myMap<K,V>::myMap(const myMap<K,V> &other)
{
    copy(other);
}

template<typename K, typename V>
myMap<K,V>& myMap<K,V>::operator=(const myMap<K,V> &other)
{
    nukem();
    copy(other);
    return *this;
}

template<typename K, typename V>
baseNode* myMap<K,V>::find(const K& index)
{
    baseNode *ptr = anchor->nextNode();
    for(;ptr && *(K*)(ptr->getFirst()) != index; ptr = ptr->nextNode());
    if(!ptr)
        return NULL;
    return ptr;
}

template<typename K, typename V>
const V myMap<K,V>::operator[] (K index) const
{
   cout<<"RHS"<<endl;
   baseNode* ptr = find(index);
   if(!ptr)
        return NOT_FOUND;
   return ((node<K,V>*)ptr)->theValue();
}
template<typename K, typename V>
V& myMap<K,V>::operator[](const K& index) // this is amazing (magic happens)
{
    cout<<"LHS"<<endl;
    baseNode *ptr  = find(index);
    if(!ptr)
    {
        V value = V();
        ptr = insert(index, value);
    }
    return ((node<K,V>*)ptr)->theValue();
 }

template<typename K, typename V>
baseNode* myMap<K,V>::insert(const K& key,const V& value)
{
    baseNode *ptr = new node<K,V>(key,value);
    linkedList::insert(ptr);
    return ptr;
}

template<typename K, typename V>
void myMap<K,V>::erase(const K& key)
{
    baseNode* ptr = find(key);
    try
    {
    linkedList::erase(ptr);
    }
    catch (LINKEDLISTERRORS err)
    {
        cout<<"an error occured"<<endl;
    }
}

template<typename K, typename V>
void myMap<K,V>::clear()
{
    nukem();
}

template<typename K, typename V>
void myMap<K,V>::copy(const myMap<K,V> &other)
{
    baseNode *ptr = other.anchor->nextNode();
    for(; ptr; ptr = ptr->nextNode())
        insert(((node<K,V>*)ptr)->theKey(),((node<K,V>*)ptr)->theValue());
}

template<typename K, typename V>
void myMap<K,V>::nukem()
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

template<typename k, typename v>
ostream& operator<<(ostream &out, const myMap<k,v> &other)
{
    baseNode *ptr = other.anchor->nextNode();

        for(; ptr; ptr=ptr->nextNode())
            out<<*(node<k,v>*)ptr<<" ";
        return out;
}

template<typename k, typename v>
istream& operator>>(istream &in, myMap<k,v> &other)
{
    string ans;
    k key = k(); v value = v();
     other.anchor->nextNode() = new node<k,v>(key,value);
     baseNode* ptr = other.anchor->nextNode();
   while(in >> *(node<k,v>*) ptr)
   {
       ptr = other.insert(((node<k,v>*)ptr)->theKey(),((node<k,v>*)ptr)->theValue());
       std::cout<<"Are you Done?"<<endl;
       std::cin>>ans;
       if(ans=="yes" || ans=="Yes" || ans=="Y" || ans=="y")
           break;
   }
   return in;
}

#endif // MYMAP_H
