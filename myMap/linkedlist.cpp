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

bool linkedList::empty()
{
  return !qty;
}

bool linkedList::full()
{
  return !(maxQty - qty);
}

unsigned int linkedList::size()
{
    return qty;
}

unsigned int linkedList::max_size()
{
    return maxQty;
}

void linkedList::insert(baseNode*& whom)
{
    baseNode *ptr = anchor;
    qty++;
    for(; ptr->nextNode() && ptr->nextNode()->getFirst() != whom->getFirst(); ptr = ptr->nextNode());
    if(!ptr)
    {
        ptr->nextNode() = whom;
        return;
    }
    whom->nextNode() = ptr->nextNode();
    ptr->nextNode() = whom;
    return;
}

void linkedList::erase(baseNode *whom)// whom = object
{
    //working erase
    baseNode *ptr = anchor, *bye = anchor->nextNode();
    qty--;
    for(; bye && bye->getFirst() != whom->getFirst(); ptr = ptr->nextNode(), bye = bye->nextNode() );
    if(!bye || bye->getFirst() != whom->getFirst())
        throw NOT_FOUND;
    ptr->nextNode() = bye->nextNode();
    delete bye;
    return;
}

