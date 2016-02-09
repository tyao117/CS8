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
    baseNode *ptr = anchor, *bye = NULL;
    while(ptr->nextNode())
    {
        bye = ptr->nextNode();
        ptr = ptr->nextNode();
        delete bye;
    }
    anchor->nextNode() = NULL;
    delete anchor;
    anchor->NULL;
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
//    //Original Version
//    baseNode *ptr = anchor, *bye;
//    qty--;
//    for(; ptr->nextNode() && ptr->nextNode()->getFirst() != ((baseNode*)whom)->getFirst(); ptr = ptr->nextNode());
//    if(!ptr->nextNode() || ptr->nextNode()->getFirst() != whom)
//        //throw NOT_FOUND;
//    bye = ptr->nextNode();
//    ptr->nextNode() = bye->nextNode();
//    delete bye;
//    return;

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

