#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

template<typename T>
union mask
{
    T* ptrVal;
    size_t varVal;
};

void newswap(size_t &x, size_t &y);

int main(int argc, char *argv[])
{
    string test2("Hello");
    string test1("Bye");

    mask<string> xptr, yptr;
    xptr.ptrVal = &test1;
    yptr.ptrVal = &test2;
    cout<<"xptr.ptrVal = "<<xptr.ptrVal<<" yptr.ptrVal = "<<yptr.ptrVal<<endl;
    swap(xptr.varVal, yptr.varVal);
    cout<<"xptr.ptrVal = "<<xptr.ptrVal<<" yptr.ptrVal = "<<yptr.ptrVal<<endl;


    double start;
    double duration;

    vector<mask<string>> arr;
    for(int i = 0; i < 1000000; ++i)
        arr.push_back(xptr);
    vector<mask<string>> arr2;
    for(int i = 0; i < 1000000; ++i)
        arr2.push_back(yptr);
    start = clock();
    for(int i(0); i < 1000000; ++i)
        newswap(arr[i].varVal, arr2[i].varVal);
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"printf: "<< duration <<'\n';

    start = clock();
    for(int i(0); i < 1000000; ++i)
        swap(arr[i], arr2[i]);
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"printf: "<< duration <<'\n';
    cout<<*(arr[0].ptrVal)<<endl;
    cout<<*(arr2[0].ptrVal)<<endl;

    return 0;
}


void newswap(size_t &x, size_t &y)
{
    x^=y^=x^=y;
    /*
     * x^=y;
     * y^=x;
     * x^=y;
     */
}
