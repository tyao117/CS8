#ifndef VECTORHEAP_H
#define VECTORHEAP_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <iomanip>

using namespace std;
enum HEAP_ERRORS {HEAP_EMPTY};
enum HEAP_TYPE {LESSTHAN, GREATERTHAN};
enum HEAP_BRANCH {LEFT, RIGHT};

template<typename T>
struct node
{
    T data;

    node(T d = T())
    {
        data = d;
    }
    ~node()
    {
        data = T();
    }
    node &operator= (const node &other)
    {
        if (this != other)
        {
            data = other.data;
        }
    }

    void assign(T d)
    {
        data = d;
    }

    friend
    bool operator< (const node& one, const node& two)
    {
        return one.data < two.data;
    }

    friend
    bool operator> (const node& one, const node& two)
    {
        return one.data > two.data;
    }

    friend
    bool operator== (const node& one, const node& two)
    {
        return one.data == two.data;
    }

    friend
    bool operator!= (const node &one, const node &two)
    {
        return one.data != two.data;
    }
};

template<typename T>
class heap
{
    public:
        typedef bool (heap<T>::*fptr)(const T &x,const  T &y);
        heap(HEAP_TYPE t = LESSTHAN);
        ~heap();
        heap(const heap<T> &other);
        heap<T>& operator=(const heap<T> &other);
        heap<T>& operator<<(const T &data);
        heap<T>& operator>>(T &data);
        void clear();
        unsigned int size();
        bool empty();
        void testPrint();

    private:

        vector<T> vec;
        int depth;

        unsigned int lastChildEntered;
        HEAP_TYPE heapType;
        fptr heapSortingMethod[2];

        void copy(const heap<T> &otherHeap);
        void copy(int parent, vector<T> &other);
        bool lessThan(const T &x, const T &y);
        bool greaterThan(const T &x, const T &y);
        void nukem(int where);
        unsigned int findParent(unsigned int childNumber);
        void reheapifyDown();
        void reheapifyUp();
        void swap(T &x, T &y);
};

template<typename T>
heap<T>::heap(HEAP_TYPE t)
{
    lastChildEntered = 0;
    depth = 0;
    heapType = t;
    heapSortingMethod[LESSTHAN] = &heap<T>::lessThan;
    heapSortingMethod[GREATERTHAN] = &heap<T>::greaterThan;
}

template<typename T>
heap<T>::~heap()
{
    nukem(1);
}

template<typename T>
heap<T>::heap(const heap<T> &other)
{
    copy(other);
}

template<typename T>
heap<T>& heap<T>::operator=(const heap<T> &other)
{
    if(this != &other)
    {
        nukem(1);
        copy(other);
    }
    return *this;
}


template<typename T>
heap<T>& heap<T>::operator<<(const T &data)
{
    if(empty())
    {
        lastChildEntered = 1;
        vec.resize(2);
        vec[1] = data;
        return *this;
    }
    ++lastChildEntered;
    unsigned int parent = findParent(lastChildEntered);

    if(lastChildEntered >= vec.size())
    {
        ++depth;
        vec.resize(vec.size() + pow(2,depth));
    }
    vec[parent*2 + (lastChildEntered%2)] = data;
    reheapifyUp();
    return *this;
}

template<typename T>
heap<T>& heap<T>::operator>>(T &data)
{
    if(empty())
        throw(HEAP_EMPTY);
    data = vec[1]; // assign the parameter value

    if(lastChildEntered == 1)
    {
        vec[1] = T();
        vec.clear();
        return *this;
    }
    int parent = findParent(lastChildEntered);
    int whichSideIsTheChild = lastChildEntered%2;

    vec[1] = vec[2*parent+(whichSideIsTheChild)];
    vec[2*parent+(whichSideIsTheChild)] = T();

    --lastChildEntered;
    reheapifyDown();
    return *this;
}

template<typename T>
void heap<T>::clear()
{
    nukem(1);
}

template<typename T>
unsigned int heap<T>::size()
{
    return lastChildEntered;
}

template<typename T>
bool heap<T>::empty()
{
    return vec.empty();
}

template<typename T>
void heap<T>::copy(const heap<T> &otherHeap)
{
    int size = otherHeap.vec.size();
    vec.resize(size);
    copy(1,otherHeap.vec);
}


template<typename T>
void heap<T>::copy(int parent, vector<T> &other)
{
    if(parent < other.size())
    {
        vec[parent] = other[parent];
        copy(2*parent, other);
        copy(2*parent+1, other);
    }
}

template<typename T>
void heap<T>::nukem(int where)
{
    if((unsigned int)where < vec.size() && ((unsigned int)(2*where) < vec.size()))
        nukem(2*where);
    if((unsigned int)where < vec.size() && ((unsigned int)(2*where+1) < vec.size()))
        nukem(2*where+1);
    if((unsigned int)where < vec.size())
        ( vec[where] = T());
}

template<typename T>
unsigned int heap<T>::findParent(unsigned int childNumber)
{
   bitset<32> bits(childNumber);
   double j = (log10(childNumber*1.)/log10(2.));
   int i = int(j);
   unsigned int parent = 1; // root index
   --i;
   for(; i > 0; --i)
       parent = (2*parent)+bits[i]; // traverse to find parent
   return parent;
}

template<typename T>
void heap<T>::reheapifyDown()
{
    unsigned int childToSwitchWith, parent = 1;
    while(2*parent <= lastChildEntered)
    {
        if( (2*parent+1) > lastChildEntered ){
            childToSwitchWith = 2*parent;
        }
        else{
            childToSwitchWith = (this->*heapSortingMethod[heapType])(vec[2*parent],vec[2*parent+1])
                              ? 2*parent
                              : 2*parent+1;
        }
        if(!(this->*heapSortingMethod[heapType])(vec[parent], vec[childToSwitchWith]))
        {
            swap(vec[parent],vec[childToSwitchWith]);
            parent = childToSwitchWith;
        }
        else
            break;
    }
}

template<typename T>
void heap<T>::reheapifyUp()
{
    int parent = (lastChildEntered / 2),
        child = lastChildEntered;
    while ((0 < parent) && (!(this->*heapSortingMethod[heapType])(vec[parent], vec[child])))
    {
        swap(vec[parent],vec[child]);
        child = child>>1; //child = child/2
        parent = child>>1; //child = child/2
    }
}

template<typename T>
void heap<T>::swap(T &x, T &y)
{
    T temp = x;
    x = y;
    y = temp;
}

template<typename T>
bool heap<T>::lessThan(const T &x,const  T &y)
{
    return *x < *y;
}

template<typename T>
bool heap<T>::greaterThan(const T &x, const T &y)
{
    return *x > *y;
}

#endif // VECTORHEAP_H
