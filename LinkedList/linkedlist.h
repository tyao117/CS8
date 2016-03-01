#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <cstdlib>
#include "basenode.h"

enum LINKEDLISTERRORS {NOT_FOUND};

class linkedList
{
public:
    linkedList();
    // ~linkedList();
    virtual ~linkedList();

    bool empty();
    bool full();
    size_t size();
    size_t max_size();

protected:
    baseNode* anchor;
    size_t qty, maxQty;

    void insertTail(baseNode *&whom);       //inserts at the end of the list
    void insertHead(baseNode *&whom);   //inserts at the top of the list

    void erase(baseNode *whom);
    void eraseHead();

private:
};

#endif
