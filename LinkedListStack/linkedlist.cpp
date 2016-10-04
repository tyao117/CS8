#include "linkedlist.h"

linkedList::linkedList()
{
    qty = 0;
    maxQty = 500;
}

linkedList::~linkedList()
{
//for loop to go through the list starting the last item qty
//call the destructor of the node
//delete the node
    baseNode *ptr = anchor->nextNode(), *bye = NULL;
    while(ptr)
    {
        bye = ptr;
        ptr = ptr->nextNode();
        delete bye;
    }
    qty = 0;
}

bool linkedList::empty()
{
    return !qty;
}

bool linkedList::full()
{
    return !(maxQty-qty);
}

size_t linkedList::size()
{
    return qty;
}

size_t linkedList::max_size()
{
    return maxQty;
}

void linkedList::insertTail(baseNode*& whom)
{
    baseNode *ptr = anchor;
    qty++;
    for(; ptr->nextNode() && ptr->nextNode()->getData() != whom->getData(); ptr = ptr->nextNode());
    if(!ptr)
    {
        ptr->nextNode() = whom;
        return;
    }
    whom->nextNode() = NULL;
    ptr->nextNode() = whom;
    return;
}

void linkedList::insertHead(baseNode *&whom)
{
    baseNode *ptr = anchor;
    qty++;
    whom->nextNode() = ptr->nextNode();
    ptr->nextNode() = whom;
}

void linkedList::erase(baseNode *whom)// whom = object
{
    //  working erase
    baseNode *ptr = anchor, *bye = anchor->nextNode();
    qty--;
    for(; bye && bye->getData() != whom->getData(); ptr = ptr->nextNode(), bye = bye->nextNode() );
    if(!bye || bye->getData() != whom->getData())
        throw NOT_FOUND;
    ptr->nextNode() = bye->nextNode();
    delete bye;
    return;
}

void linkedList::eraseHead()
{
    baseNode *ptr = anchor, *bye = anchor->nextNode();
    qty--;
    ptr->nextNode() = bye->nextNode();
    bye->nextNode() = NULL;
    delete bye;
    bye = NULL;
    return;
}

