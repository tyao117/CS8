#ifndef BASENODE_H
#define BASENODE_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

using std::ostream;
using std::istream;

class baseNode
{
public:
    baseNode();
    virtual ~baseNode();
    baseNode& operator = (const baseNode &other);

    //Functions
    baseNode*& nextNode();
    void *getData() const;
    void setData(void *ptr);

    //Friend Functions
    friend
    bool operator<(const baseNode &x, const baseNode &y);
    friend
    bool operator<=(const baseNode &x, const baseNode &y);
    friend
    bool operator>(const baseNode &x, const baseNode &y);
    friend
    bool operator>=(const baseNode &x, const baseNode &y);
    friend
    bool operator==(const baseNode &x, const baseNode &y);
    friend
    bool operator!=(const baseNode &x, const baseNode &y);
    friend
    ostream& operator<<(ostream &out, const baseNode &y);
    friend
    istream& operator>>(istream &in, baseNode &y);

protected:
    void *data;
    baseNode *next;

    private:
};

#endif // BASENODE_H
