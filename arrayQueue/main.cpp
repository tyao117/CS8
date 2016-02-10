#include <iostream>
#include <string>
#include "driver.h"
#include "arrayQueue.h"

using namespace std;

int main(int argc, char *argv[])
{
  queue<char> one, two;
  char ans1;
  int list = 1;
  string title[13] = {
      " Please make a selection: ",
      "  S : Select a queue",
      "  R : Read from a file",
      "  W : Write to a file",
      "  P : Print the list",
      "  + : Enqueue an item",
      "  - : Dequeue an item",
      "  M : Merge List 2 into List 1",
      "  Q : Quit",
      "Your selection: "};
  system("cls");
/*  try
  {
    checkArgs(argc, argv, one, two, list);
  }
  catch(int e)
  {
     cout<<"Error "<<e<<". Program terminating"<<endl;
     exit(e);
  }*/

    while(toupper(ans1 = menu(title)) != 'Q')
       perform(ans1, list,  one, two);
  return 0;
}
