#include <iostream>
#include "rempest.h"

using namespace std;

int main()
{
    tempest one("one"), two("two");
    one.otherPrivate(&two);
    one.me();
    one.you();
    one.me2();
    return 0;
}

