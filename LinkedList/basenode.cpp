#include "basenode.h"
#include <cstdlib>

baseNode::baseNode()
{
    data = next = NULL;
}

baseNode::~baseNode()
{
    data = next = NULL;
}

baseNode*& baseNode::nextNode()
{
    return next;
}

void* baseNode::getData() const
{
    return data;
}

void baseNode::setData(void *ptr)
{
    data = ptr;
}

ostream &operator<<(ostream &out, const baseNode &y)
{
    out<<y.data<<" ";
    return out;
}

istream &operator>>(istream &in, baseNode &y)
{
    in>>y.data;
    return in;
}

baseNode& baseNode::operator=(const baseNode &other)
{
    data = other.data;
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
