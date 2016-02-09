#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::ostream;
using std::istream;

template<typename D, typename P>
class node
{
    public:
        node(const D& d = D(), const P& p = P());
        ~node();
        node(const node<D,P> &other);
        node<D,P>& operator=(const node<D,P> &other);
        node<D,P>*& nextNode();
        node<D,P>*& prevNode();
        void setData(const D& d);
        const D& getData() const;
        void setPriorty(const P& p);
        const P& getPriority() const;

        template<typename T, typename U>
        friend
        bool operator>(const node<T,U> &one, const node<T,U> &two);

        template<typename T, typename U>
        friend
        bool operator<(const node<T,U> &one, const node<T,U> &two);


        template<typename T, typename U>
        friend
        istream& operator>>(istream &in, node<T,U> &input);


        template<typename T, typename U>
        friend
        ostream& operator<<(ostream &out,const  node<T,U> &output);

    private:
        D data;
        P priority;
        node<D,P> *next, *prev;

        void nukem();
        void copy(const node<D,P> &other);
};


template<typename D, typename P>
node<D,P>::node(const D& d, const P& p)
{
    data = d;
    priority  = p;
    next = prev = NULL;
}

template<typename D, typename P>
node<D,P>::~node()
{
    nukem();
}

template<typename D, typename P>
node<D,P>::node(const node<D,P> &other)
{
    copy(other);
}

template<typename D, typename P>
node<D,P>& node<D,P>::operator=(const node<D,P> &other)
{
    if(this != &other)
        copy(other);
    return *this;
}

template<typename D, typename P>
node<D,P>*& node<D,P>::nextNode()
{
    return next;
}

template<typename D, typename P>
node<D,P>*& node<D,P>::prevNode()
{
    return prev;
}

template<typename D, typename P>
void node<D,P>::setData(const D& d)
{
    data = d;
}

template<typename D, typename P>
const D& node<D,P>::getData() const
{
    return data;
}

template<typename D, typename P>
void node<D,P>::setPriorty(const P& p)
{
    priority = p;
}

template<typename D, typename P>
const P& node<D,P>::getPriority() const
{
    return priority;
}


template<typename D, typename P>
void node<D,P>::nukem()
{
    data = D();
    priority  = P();
    next = prev = NULL;
}

template<typename D, typename P>
void node<D,P>::copy(const node<D,P> &other)
{
    data = other.data;
    priority  = other.priority;
    next = prev = NULL;
}

template<typename T, typename U>
bool operator>(const node<T,U> &one, const node<T,U> &two)
{
    return one.priority > two.priority;
}

template<typename T, typename U>
bool operator<(const node<T,U> &one, const node<T,U> &two)
{
    return one.priority < two.priority;
}


template<typename T, typename U>
istream& operator>>(istream &in, node<T,U> &input)
{
    if(&in == &cin)
    {
        cout<<"Data: ";
        cin>>input.data;
        cout<<"Priority: ";
        cin>>input.priority;
    }
    else
    {
        string line;
        stringstream ss;
        getline(in,line);
        line = line.substr(5);
        ss<<line.substr(0, line.find("Priority: "));
        ss>>input.data;
        ss.clear();
        line = line.substr(0, line.find("Priority: "));
        line.erase(0,10);
        ss<<line;
        ss>>input.priority;
    }
    return in;
}


template<typename T, typename U>
ostream& operator<<(ostream &out,const  node<T,U> &output)
{
    string eol;
    eol = &out == &cout ? " " : "/n";
    out<<"Data: "<<output.data<<" Priority: "<<output.priority<<eol;
    return out;
}


#endif // NODE_H
