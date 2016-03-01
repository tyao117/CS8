#include <iostream>
#include "linkedliststack.h"
#include <string>

using namespace std;

string getLine();
void perform(string line);
string trimAndNormalize(string line);

int main()
{
   string line;
   while((line = getLine()) != "")
       perform(line);
   return 0;
}

string getLine()
{
    string line;
    cout<<"Input: ";
    getline(cin, line);
    return line;
}

void perform(string line)
{
    LinkedListStack<char> stack(line.size());
    string normalized, reversed;
    normalized = trimAndNormalize(line);
    for(unsigned int i = 0; i < normalized.size(); i++)
        stack<<normalized[i];
    cout<<stack;
    cout<<"stack size="<<stack.size()<<endl;
    LinkedListStack<char> stack2(stack);

    cout<<stack2;
    while(!stack.empty())
        reversed += stack.pop();
    cout<<reversed<<endl;
    string isNot = reversed == normalized ? " is " : " is not ";
    cout<<line<<isNot<<"a palindrome"<<endl;

}


string trimAndNormalize(string line)
{
//    unsigned int pos;
    size_t pos;

    for(unsigned int i = 0; i < line.size(); i++)
        line[i] = toupper(line[i]);
    while((pos = line.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890")) < string::npos)
    {
        line.erase(pos,1);
    }
    cout<<line<<endl;
    return line;
}
