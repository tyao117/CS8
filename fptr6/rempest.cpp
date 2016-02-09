#include "rempest.h"

tempest::tempest(const string &name)
{
    myName = name;
}

tempest::~tempest()
{

}

void tempest::whoAmI()
{
    cout<<"I am "<<myName<<endl;
}

void tempest::otherPrivate(tempest *o)
{
    other = o;
    otherP = &tempest::whoAmI;
}

void tempest::me()
{
   whoAmI();
}

void tempest::me2()
{
    (this->*otherP)();
   (other->*otherP)();
}
void tempest::you()
{
   other->whoAmI();
}
