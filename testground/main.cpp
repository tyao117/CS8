#include <iostream>
#include <string>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    int array[5];
    for (int i = 0; i < 8; ++i)
    {
        if (i>5)
        array[i%5] = i;
        else
        array[i] = i;
        cout<<"array"<<i<<" "<<array[i]<<endl;
    }
    array [4] = NULL;
    for (int i = 0; i < 5; ++i)
    {
    cout<<*array+i<<endl;
    }

}
