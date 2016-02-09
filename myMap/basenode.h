#ifndef BASENODE_H
#define BASENODE_H

class baseNode
{
    public:
        baseNode();
        virtual ~baseNode();
        baseNode& operator = (const baseNode &other);

        virtual bool operator<(const baseNode &x) const ;
        virtual bool operator<=(const baseNode &x) const ;
        virtual bool operator>(const baseNode &x) const ;
        virtual bool operator>=(const baseNode &x)const ;
        virtual bool operator==(const baseNode &x) const ;
        virtual bool operator!=(const baseNode &x) const ;

        baseNode*& nextNode();
        void * getFirst() const;
        void setFirst(void *ptr);

    protected:
        void *first;
        baseNode *next;

    private:
};

#endif // BASENODE_H
