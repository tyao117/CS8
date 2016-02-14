#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::stringstream;

int main(int argc, char *argv[])
{
    stringstream ss;
    string test= "I'm going to using be string stream";
    ss<<test;
    while (!ss.eof())
    {
        string test;
        if (isalpha(ss.peek()))
        ss>>test;
        cout<<test<<endl;
    }
    cout<<endl;
}
