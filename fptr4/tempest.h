#ifndef TEMPEST_H
#define TEMPEST_H
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <string>

using namespace std;

class tempest;

typedef void (tempest::*fptr)();

class tempest
{
    public:
        tempest(const string &who);
        ~tempest();
        void otherPrivate(tempest *o);
        void me();
        void me2();
        void you();

    private:
        string myName;
        tempest *other;
        fptr otherP;

        void whoAmI();
};

#endif // TEMPEST_H
