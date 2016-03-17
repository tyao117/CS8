#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <bitset>

using namespace std;
void add(int);


int main(int argc, char *argv[])
{
    cout<<"BitWise Practice"<<endl;
    cout<<"SL0 (1<<0)="<<(1<<0)<<endl;
    cout<<bitset<8>(1<<0)<<endl;
    cout<<"SL1 (1<<1)="<<(1<<1)<<endl;
    cout<<bitset<8>(1<<1)<<endl;
    cout<<"SL2 (1<<2)="<<(1<<2)<<endl;
    cout<<bitset<8>(1<<2)<<endl;
    cout<<"22="<<bitset<8>(22)<<endl;
    cout<<"19="<<bitset<8>(19)<<endl;
    cout<<"AND (22&19)="<<(22&19)<<endl;
    cout<<bitset<8>(22&19)<<endl;
    cout<<"OR  (22|19)="<<(22|19)<<endl;
    cout<<bitset<8>(22|19)<<endl;
    cout<<"XOR (22^19)="<<(22^19)<<endl;
    cout<<bitset<8>(22^19)<<endl;

    return 0;
}

