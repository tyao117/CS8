#ifndef BSTVECTOR_H
#define BSTVECTOR_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iomanip>
#include <limits>
#include <sstream>
#include <algorithm>


enum TRAVERSE_TYPE {PRE_ORDER,IN_ORDER,POST_ORDER};
enum BST_ERRORS {BST_EMPTY, BST_RANGE};

using std::istream;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::size_t;


template<typename T>
struct node
{
    T data;
    size_t count;

    node()
    {
        data = T();
        count = 0;
    }

    node(T d = T())
    {
        data = d;
        count = 1;
    }

    node(T d = T(), size_t c = 1)
    {
        data = d;
        count = c;
    }

    node(const node<T> &other)
    {
        data = other.data;
        count = other.count;
    }

    node<T> operator = (const node<T> &other)
    {
        if (this != other)
        {
            data = other.data;
            count = other.count;
        }
    }
    ~node()
    {
        data = T();
        count = 0;
    }
};

template<typename T>
class bstvector
{
    public:
        bstvector(TRAVERSE_TYPE  t = IN_ORDER);
        bstvector(const T &d, size_t = 1, TRAVERSE_TYPE t = IN_ORDER);
        bstvector(const bstvector<T> &other);
        ~bstvector();
        bstvector<T>& operator=(const bstvector<T> &other);

        void insert(const T &d, size_t c = 1);
        bstvector<T>& operator<<(const T &d);
        size_t find(const T &d);
        void clear();
        bool remove(const T &d, size_t c = 1);
        bool removeAll(const T &d);
        size_t totalData();
        size_t totalNodes();
        size_t depth();
        const T& leftMost() const;
        const T& rightMost() const;
        bool empty() const;
        bool balanced();
        void rebalance();
        void setTraversal(TRAVERSE_TYPE t);
        TRAVERSE_TYPE currentTraversal();
        ostream& print(ostream &out = cout) const;


        template<typename U>
        friend
        ostream& operator<<(ostream& out, const bstvector<U> &other);

        template<typename U>
        friend
        istream& operator>>(istream& in, bstvector<U> &other);


    private:
        vector<node<T>*> v;
        TRAVERSE_TYPE traverse;
        size_t total;

        void copy(const bstvector &other);
        void copy(size_t index);
        void nukem();

};

template <typename T>
bstvector<T>::bstvector(TRAVERSE_TYPE  t)
{
    traverse = t;
    total = 0;
}

template <typename T>
bstvector<T>::bstvector(const T &d, size_t count, TRAVERSE_TYPE t)
{
    traverse = t;
    node<T> *newNode = new node<T>(d,count);
    total = count;
    v.push_back(newNode);
    v.resize(3);
}

template <typename T>
bstvector<T>::bstvector(const bstvector<T> &other)
{
    copy(other);
}

template <typename T>
bstvector<T>::~bstvector()
{
    //nukem();
    traverse = IN_ORDER;
    total = 0;
}

template <typename T>
bstvector<T>& bstvector<T>::operator=(const bstvector<T> &other)
{
    if (this != &other)
    {
        copy(other);
    }
    traverse = other.traverse;
    total = other.total;
}

template <typename T>
void bstvector<T>::insert(const T &d, size_t c)
{
    if (NULL)
    return;
    node<T> *newNode = new node<T>(d,c);
    v[NULL] = newNode;
    total += newNode->count;
}

template <typename T>
bstvector<T>& bstvector<T>::operator<<(const T &d)
{

}

template <typename T>
size_t bstvector<T>::find(const T &d)
{

}

template <typename T>
void bstvector<T>::clear()
{
    nukem();
}

template <typename T>
bool bstvector<T>::remove(const T &d, size_t c)
{

}

template <typename T>
bool bstvector<T>::removeAll(const T &d)
{

}

template <typename T>
size_t bstvector<T>::totalData()
{

}

template <typename T>
size_t bstvector<T>::totalNodes()
{
    return total;
}

template <typename T>
size_t bstvector<T>::depth()
{
    return (double(log2( v.size() - 1)));
}

template <typename T>
const T& bstvector<T>::leftMost() const
{

}
template <typename T>
const T& bstvector<T>::rightMost() const
{

}
template <typename T>
bool bstvector<T>::empty() const
{

}
template <typename T>
bool bstvector<T>::balanced()
{

}

template <typename T>
void bstvector<T>::rebalance()
{

}

template <typename T>
void bstvector<T>::setTraversal(TRAVERSE_TYPE t)
{
    traverse = t;
}

template <typename T>
TRAVERSE_TYPE bstvector<T>::currentTraversal()
{
    return traverse;
}

template <typename T>
ostream& bstvector<T>::print(ostream &out) const
{

}

template <typename T>
void bstvector<T>::copy(const bstvector &other)
{
    v = other.v;
    traverse = other.traverse;
    total = other.total;
}

template <typename T>
void bstvector<T>::copy(size_t index)
{

}

template <typename T>
void bstvector<T>::nukem()
{
    v.clear();
    vector<T>().swap(v);
    traverse = IN_ORDER;
    total = 0;
}

template <typename U>
ostream& operator<<(ostream& out, const bstvector<U> &other)
{

}

template<typename U>
istream& operator>>(istream& in, bstvector<U> &other)
{

}


#endif // BSTVECTOR_H
