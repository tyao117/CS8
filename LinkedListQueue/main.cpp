#include <iostream>
//#include "LinkedListQueue.h"
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


