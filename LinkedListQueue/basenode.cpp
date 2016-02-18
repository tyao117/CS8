#include "basenode.h"
#include <cstdlib>

baseNode::baseNode()
{
    first = next = NULL;
}

baseNode::~baseNode()
{
    first = next = NULL;
}

baseNode*& baseNode::nextNode()
{
    return next;
}

void* baseNode::getFirst() const
{
    return first;
}

void baseNode::setFirst(void *ptr)
{
    first = ptr;
}

ostream &operator<<(ostream &out, const baseNode &y)
{
    out<<y.first<<" ";
    return out;
}

istream &operator>>(istream &in, baseNode &y)
{
    in>>y.first;
    return in;
}

baseNode& baseNode::operator=(const baseNode &other)
{
    first = other.first;
    next = other.next;
    return *this;
}

bool operator < (const baseNode &x, const baseNode &y)
{
    return x < y;
}

bool operator <=(const baseNode &x, const baseNode &y)
{
    return x <= y;
}
bool operator>(const baseNode &x, const baseNode &y)
{
    return x > y;
}
bool operator>=(const baseNode &x, const baseNode &y)
{
    return x >= y;
}
bool operator==(const baseNode &x, const baseNode &y)
{
    return x == y;
}
bool operator!=(const baseNode &x, const baseNode &y)
{
    return x != y;
}
