#ifndef BST_H
#define BST_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <limits>
#include <cmath>
#include "node.h"

using namespace std;

enum BST_TRAVERSAL_TYPES {IN_ORDER, PRE_ORDER, POST_ORDER};
enum BST_ERROR_TYPES {EMPTY};


template<typename T>
class bst
{
    public:
        typedef void (bst<T>::*fptr)(node<T>*,ostream &) const;
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


        template<typename U>
        friend
        ostream& operator<<(ostream& out, const bst<U> &other);

        template<typename U>
        friend
        istream& operator>>(istream& in, bst<U> &other);

    private:
        node<T> *root;
        BST_TRAVERSAL_TYPES  traverse;
        fptr whatToDo[3];
        static WHICH_CHILD direction[2];

        void copy(node<T> *r);
        void nukem(node<T>* &r);
        void inOrder(node<T>* r, ostream &out) const;
        void preOrder(node<T>* r, ostream &out) const;
        void postOrder(node<T>* r, ostream &out) const;
        size_t depth(node<T> *r);
        bool balanced(node<T> *r);
        void rebalance(node<T> *r);
        node<T>* theMost(node<T>*r, WHICH_CHILD child) const;
        node<T>* findParent(node<T> *r, T d);
        void initialize(node<T> *n, BST_TRAVERSAL_TYPES  t );
        size_t totalNodes(node<T> *r);
        size_t totalDataItems(node<T> *r);
        node<T>* leftRotate(node<T>* n);
        node<T>* rightRotate(node<T>* n);
        node<T>* createRightVine(node<T>* r);
        node<T>* balanceVine(node<T>* r, size_t nodeCount);
        ostream& print(ostream &out = cout) const;

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
    copy(other.root);
}


template<typename T>
bst<T>::~bst()
{
    nukem(root);
}

template<typename T>
bst<T>& bst<T>::operator=(const bst<T> &other)
{
    if(this != &other)
    {
        nukem(root);
        copy(other.root);
    }
    return *this;
}


template<typename T>
void bst<T>::insert(const T &d, size_t c)
{
    bool notDone = true;
    if(!root)
        root = new node<T>(d,c);
    else
    {
        node<T> *temp = root;
        while(notDone)
            if(d == *temp)
            {
                (*temp) += c;
                notDone = false;
            }
            else
            {
                WHICH_CHILD child = direction[d < temp->getData()];
                if(!temp->childPtr(child))
                {
                    temp->childPtr(child) = new node<T>(d,c);
                    notDone = false;
                }
                else
                    temp = temp->childPtr(child);
            }
    }
    if (balanced())
        rebalance();
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
    node<T> *ptr = root;
    while(ptr && *ptr != d)
        ptr = ptr->childPtr(direction[ d < *ptr]);
    return ptr ? ptr->getCount() : 0;
}

template<typename T>
void bst<T>::clear()
{
    nukem(root);
}

template<typename T>
bool bst<T>::remove(const T &d, size_t c)
{
    static node<T> temp;
    temp.childPtr(LEFT) = temp.childPtr(RIGHT) = root;
    node<T> *parent = findParent(&temp, d),
            *bye,
            *leftMost, *rightMost;
    if(!parent)
        return false;
    WHICH_CHILD child = direction[d < parent->getData()];
    bye = parent->childPtr(child);
    *bye -= c;
    if( bye->getCount() < 1)
    {
           if(bye->childPtr(RIGHT))
           {
                parent->childPtr(child) = bye->childPtr(RIGHT);
                leftMost = theMost(bye->childPtr(RIGHT), LEFT);
                leftMost->childPtr(LEFT) = bye->childPtr(LEFT);
           }
           else
                parent->childPtr(child) = bye->childPtr(LEFT);
           delete bye;
           root = temp.childPtr(child);
    }
    return true;
}

template<typename T>
bool bst<T>::removeAll(const T &d)
{
    return remove(d,UINT_MAX);
}

template<typename T>
size_t bst<T>::totalData()
{
    return totalDataItems(root);
}

template<typename T>
size_t bst<T>::totalNodes()
{
    return totalNodes(root);
}

template<typename T>
size_t bst<T>::depth()
{
    return root ? 1 + max(depth(root->rightChild()), depth(root->leftChild())) : 0;
}

template<typename T>
const T& bst<T>::leftMost() const
{
    node<T>* temp = theMost(root,LEFT);
    return temp ? temp->getData() : 0 ;
}

template<typename T>
const T& bst<T>::rightMost() const
{
    node<T>* temp = theMost(root, RIGHT);
    return temp ? temp->getData() : 0 ;
}

template<typename T>
bool bst<T>::empty() const
{
    return !root;
}

template<typename T>
bool bst<T>::balanced()
{
   return balanced(root);
}

template<typename T>
void bst<T>::rebalance()
{
    /*
      Rebalancing is done via the DSW algorithm.
      This is not in your textbook, nor will you
      find it in many textbooks used in the USA.

      Here is a link to an academic paper about
      the DSW algorithm:

      http://penguin.ewu.edu/~trolfe/DSWpaper/index.html

      This paper was published in Inroads, the  journal
      of the ACM's Special Interest Group on Computer
      Science Education. This algorithm runs in
      O(n) time, and as such, is extremely fast.

      Note: This algorithm is designed to work on linked-lists.
      There is a version that will work with array-based trees.
    */
    cout<<endl<<"rebalance checked"<<endl;
    size_t count = totalNodes();
    root = createRightVine(root);
    root = balanceVine(root,count);
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
void bst<T>::copy(node<T> *r)
{
    if(!r)
        return;
    insert(r->getData(), r->getCount());
    copy(r->getChildPtr(LEFT));
    copy(r->getChildPtr(RIGHT));
}

template<typename T>
void bst<T>::nukem(node<T> *&r)
{
    if(!r)
        return;
    nukem(r->childPtr(LEFT));
    nukem(r->childPtr(RIGHT));
    delete r;
    r = NULL;
}


template<typename T>
void bst<T>::inOrder(node<T>* r, ostream &out) const
{
    if(!r)
        return;
    inOrder(r->childPtr(LEFT),out);
    out<<r->getData()<<"["<<r->getCount()<<"] ";
    inOrder(r->childPtr(RIGHT),out);
}

template<typename T>
void bst<T>::preOrder(node<T>* r, ostream &out) const
{
    if(!r)
        return;
    out<<r->getData()<<"["<<r->getCount()<<"] ";
    preOrder(r->childPtr(LEFT),out);
    preOrder(r->childPtr(RIGHT),out);
}

template<typename T>
void bst<T>::postOrder(node<T>* r, ostream &out) const
{
    if(!r)
        return;
    postOrder(r->childPtr(LEFT),out);
    postOrder(r->childPtr(RIGHT),out);
    out<<r->getData()<<"["<<r->getCount()<<"] ";
}

template<typename T>
size_t bst<T>::depth(node<T> *r)
{
    return !r ? 0 : 1 + max(depth(r->childPtr(LEFT)), depth(r->childPtr(RIGHT)));
}

template<typename T>
bool bst<T>::balanced(node<T> *r)
{
    return abs((double)(depth(r->childPtr(LEFT)) - (double)depth(r->childPtr(RIGHT)))) <= 1;
}


template<typename T>
node<T>* bst<T>::theMost(node<T>*r, WHICH_CHILD child) const
{
    if(empty())
        throw EMPTY;
    node<T> *temp = r;
    for(; temp->childPtr(child); temp = temp->childPtr(child));
    return temp;
}

template<typename T>
node<T>* bst<T>::findParent(node<T> *r, T d)
{
    return !r ? NULL : (r->childPtr(LEFT) != 0 )&& (r->childPtr(LEFT)->getData() == d) ||(r->childPtr(RIGHT) != 0 )&& (r->childPtr(RIGHT)->getData() == d) ? r : findParent(r->childPtr(direction[d < r->getData()]),d);
}

template<typename T>
size_t bst<T>::totalNodes(node<T> *r)
{
    return !r ? 0 : 1 + totalNodes(r->childPtr(LEFT)) + totalNodes(r->childPtr(RIGHT));
}


template<typename T>
size_t bst<T>::totalDataItems(node<T> *r)
{
    return r ? r->getCount() + totalDataItems(r->childPtr(LEFT)) + totalDataItems(r->childPtr(RIGHT)) : 0;
}

template<typename T>
void bst<T>::initialize(node<T> *n, BST_TRAVERSAL_TYPES  t )
{
    root  = n;
    traverse = t;
    whatToDo[IN_ORDER] = &bst<T>::inOrder;
    whatToDo[PRE_ORDER] = &bst<T>::preOrder;
    whatToDo[POST_ORDER] = &bst<T>::postOrder;
    direction[0] = RIGHT;
    direction[1] = LEFT;
}

template<typename T>
node<T>* bst<T>::leftRotate(node<T>* n)
{

    if(n->childPtr(RIGHT))
    {
        node<T>* rightChild = n->childPtr(RIGHT);
        n->childPtr(RIGHT) = rightChild->childPtr(RIGHT);
        rightChild->childPtr(RIGHT) = rightChild->childPtr(LEFT);
        rightChild->childPtr(LEFT) = n->childPtr(LEFT);
        n->childPtr(LEFT) = rightChild;
        size_t count = n->getCount();
        T data = n->getData();
        n->setNodeValue(rightChild->getData(), rightChild->getCount());
        rightChild->setNodeValue(data,count);
     }
    return n;
}


template<typename T>
node<T>* bst<T>::rightRotate(node<T>* n)
{
    if(n->childPtr(LEFT))
    {
        node<T>* leftChild = n->childPtr(LEFT);
        n->childPtr(LEFT) = leftChild->childPtr(LEFT);
        leftChild->childPtr(LEFT) = leftChild->childPtr(RIGHT);
        leftChild->childPtr(RIGHT) = n->childPtr(RIGHT);
        n->childPtr(RIGHT) = leftChild;

        size_t count = n->getCount();
        T data = n->getData();
        n->setNodeValue(leftChild->getData(), leftChild->getCount());
        leftChild->setNodeValue(data,count);
     }
    return n;
}


template<typename T>
node<T>* bst<T>::createRightVine(node<T>* r)
{
    while(r->childPtr(LEFT))
        r = rightRotate(r);
    if(r->getChildPtr(RIGHT))
        r->childPtr(RIGHT) = createRightVine(r->childPtr(RIGHT));
    return r;
}

template<typename T>
node<T>* bst<T>::balanceVine(node<T>* r, size_t nodeCount)
{
    node<T>* newRoot = r;
    size_t FullTreeCount = 1;
    for(int i = 1; nodeCount > pow(2., i) - 1; FullTreeCount = pow(2., i++) - 1);
     size_t times = log2(FullTreeCount);

    newRoot = leftRotate(newRoot);
    r = newRoot->childPtr(RIGHT);
    for(size_t j = 1; j < nodeCount - FullTreeCount; ++j)
    {
        r = leftRotate(r);
        r = r->childPtr(RIGHT);
    }
    for(size_t i = 0; i < times; ++i)
    {
        newRoot = leftRotate(newRoot);
        r = newRoot->childPtr(RIGHT);
        for(size_t j = 0; FullTreeCount/2 && j < FullTreeCount/2-1; ++j)
        {
            r = leftRotate(r);
            r = r->childPtr(RIGHT);
        }
        FullTreeCount >>= 1;
    }
    return newRoot;
}

template<typename T>
ostream& bst<T>::print(ostream &out) const
{
    (this->*whatToDo[traverse])(root, out);
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
                other.insert(data,count);
            }
        }
    else
        while(in>>data>>junk>>count>>junk)
            other.insert(data,count);
    return in;
}


#endif // BST_H
