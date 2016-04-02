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

#define leftChild(n) (2 * n + 1)
#define rightChild(n) (2 * n + 2)

enum BST_TRAVERSAL_TYPES {PRE_ORDER,IN_ORDER,POST_ORDER, LEVEL_ORDER};
enum BST_ERRORS {EMPTY, OFF_RANGE};
enum WHICH_CHILD {RIGHT,LEFT};

using std::istream;
using std::ostream;
using std::stringstream;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::size_t;
using std::string;
using std::max;


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
class bst
{
    public:
        typedef void (bst<T>::*fptr)(size_t index, ostream &out) const;
        bst(BST_TRAVERSAL_TYPES  t = IN_ORDER);
        bst(const T &d, size_t = 1, BST_TRAVERSAL_TYPES t = IN_ORDER);
        bst(const bst<T> &other);
        ~bst();
        bst<T>& operator=(const bst<T> &other);

        void insert(const T &d, size_t c = 1);
        bst<T>& operator<<(const T &d);
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
        void setTraversal(BST_TRAVERSAL_TYPES t);
        BST_TRAVERSAL_TYPES currentTraversal();
        ostream& print(ostream &out = cout) const;


        template<typename U>
        friend
        ostream& operator<<(ostream& out, const bst<U> &other);

        template<typename U>
        friend
        istream& operator>>(istream& in, bst<U> &other);

    private:
        BST_TRAVERSAL_TYPES traverse;
        fptr whatToDo[4];
        static WHICH_CHILD direction[2];
        vector<node<T>*> v;

        void copy(const bst &other);
        void copy(const bst &other, size_t index);
        void insert(const T &d, size_t c, size_t r);
        void reattachRightChildren(size_t to, size_t from);
        void shiftSubtree(size_t to, size_t from);
        void nukem(size_t index);
        void inOrder(size_t index, ostream &out) const;
        bst<T> inOrder(size_t index) const;
        void preOrder(size_t index, ostream &out) const;
        void postOrder(size_t index, ostream &out) const;
        void levelOrder(size_t index, ostream &out) const;
        size_t depth(size_t index);
        bool balanced(size_t index);
        void rebalance(node<T> *r);
        size_t theMost(size_t index, WHICH_CHILD child) const;
        node<T>* findParent(node<T> *r, T d);
        void initialize(node<T> *n, BST_TRAVERSAL_TYPES  t );
        size_t totalNodes(size_t index);
        size_t totalDataItems(size_t index);
        void setMid(bst<T> sorted, size_t pos, size_t start, size_t end);
        void balanceTree(bst<T> sorted, size_t count);
        size_t findIndex(const T &d, size_t index);
};

template<typename T>
WHICH_CHILD bst<T>::direction[2] = {RIGHT,LEFT};

template<typename T>
bst<T>::bst(BST_TRAVERSAL_TYPES  t )
{
    initialize(NULL,t);
}

template<typename T>
bst<T>::bst(const T &d, size_t c, BST_TRAVERSAL_TYPES t)
{
    initialize(new node<T>(d,c),t);
}

template<typename T>
bst<T>::bst(const bst<T> &other)
{
    copy(other);
}


template<typename T>
bst<T>::~bst()
{
    nukem(0);
    traverse = IN_ORDER;
    whatToDo[IN_ORDER] = 0;
    whatToDo[PRE_ORDER] = 0;
    whatToDo[POST_ORDER] = 0;
}

template<typename T>
bst<T>& bst<T>::operator=(const bst<T> &other)
{
    if(this != &other)
    {
        nukem(0);
        copy(other);
    }
    return *this;
}

template<typename T>
void bst<T>::insert(const T &d, size_t c)
{
    insert(d, c, 0);
}

template<typename T>
void bst<T>::insert(const T &d, size_t c, size_t r)
{
    if(!v.size())
    {
        v.resize(1);
    }
    if(!v[r])
    {
        v[r] = new node<T>(d,c);
        v.resize(pow(2, depth() + 1) - 1);
//        v.resize(2 * v.size() + 1);
    }
    else
    {
        size_t insertPos = r;
        while(1)
            if(d == v[insertPos]->data)
            {
                v[insertPos]->count += c;
                break;
            }
            else
            {
                WHICH_CHILD child = direction[d < v[insertPos]->data];
                if(!v[(insertPos = leftChild(insertPos) + !child)])
                {
                    v[insertPos] = new node<T>(d,c);
                    if(leftChild(insertPos) > v.size())
                    {
                        v.resize(pow(2, depth() + 1) - 1);
//                        v.resize(2 * v.size() + 1);
                    }
                    break;
                }
            }
    }
}

template<typename T>
bst<T>& bst<T>::operator<<(const T &d)
{
    insert(d);
    return *this;
}

template<typename T>
size_t bst<T>::find(const T& d)
{
    size_t pos = 0;
    while(v[pos] && v[pos]->data != d)
        pos = leftChild(pos) + !direction[ d < v[pos]->data];
    return v[pos] ? v[pos]->count : 0;
}

template<typename T>
void bst<T>::clear()
{
    nukem(0);
    v.resize(1);
}

template<typename T>
bool bst<T>::remove(const T &d, size_t c)
{
    size_t bye = findIndex(d, 0);
    if(bye == SIZE_MAX)
        return false;
    v[bye]->count -= c;
    if( v[bye]->count < 1)
    {
        delete v[bye];
        if(v[rightChild(bye)])
        {
            size_t promotedOne = theMost(rightChild(bye), LEFT);
            v[bye] = v[promotedOne];
            v[promotedOne] = 0;
            reattachRightChildren(bye, promotedOne);
        }
        else if(v[leftChild(bye)])
        {
            size_t promotedOne = 2 * bye + 1;
            v[bye] = 0;
            shiftSubtree(bye, promotedOne);
        }
        else
        {
            v[bye] = 0;
        }
        v.resize(pow(2, depth() + 1) - 1);
    }
    return true;
}

template<typename T>
bool bst<T>::removeAll(const T &d)
{
    return remove(d,UINT_MAX);
}

template<typename T>
void bst<T>::reattachRightChildren(size_t to, size_t from)
{
    size_t attachHere = theMost(rightChild(to), LEFT);
    from = rightChild(from);
    if(!v[attachHere])
    {
        shiftSubtree(attachHere, from);
    }
    else
    {
        attachHere = leftChild(attachHere);
        shiftSubtree(attachHere, from);
    }

}

template<typename T>
void bst<T>::shiftSubtree(size_t to, size_t from)
{
    if(!v[from])
    {
        return;
    }
    insert(v[from]->data, v[from]->count, to);
    v[from] = 0;
    shiftSubtree(leftChild(to), leftChild(from));
    shiftSubtree(rightChild(to), rightChild(from));
}

template<typename T>
size_t bst<T>::totalData()
{
    return totalDataItems(0);
}

template<typename T>
size_t bst<T>::totalNodes()
{
    return totalNodes(0);
}

template<typename T>
size_t bst<T>::depth()
{
    return v[0] ? 1 + std::max(depth(1), depth(2)) : 0;
}

template<typename T>
const T& bst<T>::leftMost() const
{
    size_t temp = theMost(0,LEFT);
    return v.size() - 1 >= temp ? v[temp] : 0 ;
}

template<typename T>
const T& bst<T>::rightMost() const
{
    size_t temp = theMost(0, RIGHT);
    return v.size() - 1 >= temp ? v[temp] : 0 ;
}

template<typename T>
bool bst<T>::empty() const
{
    return !v[0];
}

template<typename T>
bool bst<T>::balanced()
{
   return balanced(0);
}

template<typename T>
void bst<T>::rebalance()
{
    size_t count = totalNodes();
    bst<T> temp;
//    temp.resize(v.size());
    temp = inOrder(0);
    clear();
    balanceTree(temp, count);
}

template<typename T>
void bst<T>::setTraversal(BST_TRAVERSAL_TYPES t)
{
    traverse = t;
}

template<typename T>
BST_TRAVERSAL_TYPES bst<T>::currentTraversal()
{
    return traverse;
}


template<typename T>
void bst<T>::copy(const bst &other)
{
    traverse = other.traverse;
    whatToDo[IN_ORDER] = &bst<T>::inOrder;
    whatToDo[PRE_ORDER] = &bst<T>::preOrder;
    whatToDo[POST_ORDER] = &bst<T>::postOrder;
    whatToDo[LEVEL_ORDER] = &bst<T>::levelOrder;
    if(!other.v.size() || !other.v[0])
        return;
    v.resize(other.v.size());
    v[0] = new node<T>(other.v[0]->data, other.v[0]->count);
    copy(other, leftChild(0));
    copy(other, rightChild(0));
}

template<typename T>
void bst<T>::copy(const bst &other, size_t index)
{
    if(other.v.size() - 1 < index || !other.v[index])
        return;
    v[index] = new node<T>(other.v[index]->data, other.v[index]->count);
    copy(other, leftChild(index));
    copy(other, rightChild(index));
}

template<typename T>
void bst<T>::nukem(size_t index)
{
    if(!(v.size() - 1 < index) && v[index])
    {
        nukem(leftChild(index));
        nukem(rightChild(index));
        delete v[index];
        v[index] = 0;
    }
    return;
}

template<typename T>
void bst<T>::inOrder(size_t index, ostream &out) const
{
    if(v.size() - 1 < index || !v[index])
        return;
    inOrder(leftChild(index),out);
    out<<v[index]->data<<"["<<v[index]->count<<"] ";
    inOrder(rightChild(index),out);
}

template<typename T>
bst<T> bst<T>::inOrder(size_t index) const
{
    bst<T> result;
    result.v.pop_back();
    bst<T> temp;
    if(index < v.size() - 1 && v[index])
    {
        temp = inOrder(leftChild(index));
        for(size_t i = 0; i < temp.v.size() && temp.v[i]; ++i)
        {
            result.v.push_back(new node<T>(temp.v[i]->data, temp.v[i]->count));
        }
        result.v.push_back(new node<T>(v[index]->data, v[index]->count));
        temp = inOrder(rightChild(index));
        for(size_t i = 0; i < temp.v.size() && temp.v[i]; ++i)
        {
            result.v.push_back(new node<T>(temp.v[i]->data, temp.v[i]->count));
        }
    }
    return result;
}

template<typename T>
void bst<T>::preOrder(size_t index, ostream &out) const
{
    if(v.size() - 1 < index || !v[index])
        return;
    out<<v[index]->data<<"["<<v[index]->count<<"] ";
    preOrder(leftChild(index),out);
    preOrder(rightChild(index),out);
}

template<typename T>
void bst<T>::postOrder(size_t index, ostream &out) const
{
    if(v.size() - 1 < index || !v[index])
        return;
    postOrder(leftChild(index),out);
    postOrder(rightChild(index),out);
    out<<v[index]->data<<"["<<v[index]->count<<"] ";
}

template<typename T>
void bst<T>::levelOrder(size_t index, ostream &out) const
{
    if (v.size() < index)
        return;
    if (!v[index])
        out<<index<<"= "<<"None "<<endl;
    else
        out<<index<<"= "<<v[index]->data<<"["<<v[index]->count<<"] "<<endl;
    levelOrder(++index, out);
}

template<typename T>
size_t bst<T>::depth(size_t index)
{
    return v.size() - 1 < index || !v[index] ? 0 : 1 + max(depth(leftChild(index)), depth(rightChild(index)));
}

template<typename T>
bool bst<T>::balanced(size_t index)
{
    if(v.size() - 1 < index || !v[index])
    {
        return true;
    }
    return abs((double)depth(leftChild(index)) - depth(rightChild(index))) <= 1 && balanced(leftChild(index)) && balanced(rightChild(index));
}

template<typename T>
size_t bst<T>::theMost(size_t index, WHICH_CHILD child) const
{
    if(empty())
        throw EMPTY;
    for(; v[leftChild(index) + !child]; index = leftChild(index) + !child);
    return index;
}

template<typename T>
node<T>* bst<T>::findParent(node<T> *r, T d)
{
    return !r ? NULL :
               r->childPtr(LEFT) && r->childPtr(LEFT)->data == d || r->childPtr(RIGHT) && r->childPtr(RIGHT)->data == d ? r
             : findParent(r->childPtr(direction[d < r->data]),d);
}

template<typename T>
size_t bst<T>::totalNodes(size_t index)
{
    return v[index] ? 1 + totalNodes(leftChild(index)) + totalNodes(rightChild(index)) : 0;
}


template<typename T>
size_t bst<T>::totalDataItems(size_t index)
{
    return v.size() - 1 >= index && v[index] ? v[index]->count + totalDataItems(leftChild(index)) + totalDataItems(rightChild(index)) : 0;
}

template<typename T>
void bst<T>::initialize(node<T> *n, BST_TRAVERSAL_TYPES  t )
{
    v.resize(1);
    if(n)
    {
        v[0] = n;
        v.resize(2 * v.size() + 1);
    }
    traverse = t;
    whatToDo[IN_ORDER] = &bst<T>::inOrder;
    whatToDo[PRE_ORDER] = &bst<T>::preOrder;
    whatToDo[POST_ORDER] = &bst<T>::postOrder;
    whatToDo[LEVEL_ORDER] = &bst<T>::levelOrder;
    direction[0] = RIGHT;
    direction[1] = LEFT;
}

template<typename T>
void bst<T>::setMid(bst<T> sorted, size_t pos, size_t start, size_t end)
{
    size_t mid = ((start + end) + 1) / 2;
    insert(sorted.v[mid]->data, sorted.v[mid]->count, pos);
    if(mid > start)
    {
        setMid(sorted, leftChild(pos), start, mid - 1);
        if(mid != end)
        {
            setMid(sorted, rightChild(pos), mid + 1, end);
        }
    }
    return;
}

template<typename T>
void bst<T>::balanceTree(bst<T> sorted, size_t count)
{
    if(count)
    {
        size_t mid = count / 2;
        insert(sorted.v[mid]->data, sorted.v[mid]->count, 0);
        if(mid)
        {
            setMid(sorted, leftChild(0), 0, mid - 1);
            setMid(sorted, rightChild(0), mid + 1, count - 1);
        }
    }
    return;
}

template<typename T>
size_t bst<T>::findIndex(const T &d, size_t index)
{
    if(!v[index])
    {
        return (-1);
    }
    if(v[index]->data == d)
    {
        return index;
    }
    return findIndex(d, leftChild(index) + !direction[d < v[index]->data]);
}

template<typename T>
ostream& bst<T>::print(ostream &out) const
{
   (this->*whatToDo[traverse])(0, out);
    return out;
}

template<typename U>
ostream& operator<<(ostream& out, const bst<U> &other)
{
    return other.print(out);
}

template<typename U>
istream& operator>>(istream& in, bst<U> &other)
{
    U data;
    int count;
    char junk;
    string line;
    stringstream ss;
    bool moreData = true;
    if(&in == &cin)
        while(moreData)
        {
            cout<<"Data: ";
            getline(in,line);
            if(line.empty())
                moreData = false;
            else
            {
                ss<<line;
                ss>>data;
                ss.clear();
                cout<<"Count: ";
                cin>>count;
                if(count < 1)
                {
                    throw EMPTY;
                }
                other.insert(data,count);
            }
        }
    else
        while(in>>data>>junk>>count>>junk)
            other.insert(data,count);
    return in;
}


#endif // BSTVECTOR_H
