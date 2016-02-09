#include <iostream>
#include "node.h"
#include "linkedlist.h"
#include "myMap.h"

using namespace std;

int main()
{
  cout<<"Starting the demonstration program"<<endl;
  myMap<char,string> mymap;
  cout<<"Safely declared a myMap"<<endl;

  cout<<"start here"<<endl;
  mymap['a']="an element";
  mymap['b']="another element";
  mymap['c'] = mymap['b'];
  cout<<"Should have fired RHS"<<endl;

  cout<<"True"<<endl;
//  mymap.insert('a',"an element");
//  mymap.insert('b',"another element");
//  mymap.insert('c', mymap['b']);

  cout << "mymap['a'] is " << mymap['a'] << endl;
  cout << "mymap['b'] is " << mymap['b'] << endl;
  cout << "mymap['c'] is " << mymap['c'] << endl;
  cout << "mymap['d'] is " << mymap['d'] << endl;
  mymap.erase('b');

  cout<< mymap<<endl;

  cout << "mymap now contains " << mymap.size() << " elements.\n";

  myMap<string,int> mymap2;

  mymap2["one"] = 1;
  mymap2["two"] = 2;
  mymap2["three"] = mymap2["two"];

  cout<<"True"<<endl;

  cout << "mymap2[\"one\"] is " << mymap2["one"] << endl;
  cout << "mymap2[\"two\"] is " << mymap2["two"] << endl;
  cout << "mymap2[\"three\"] is " << mymap2["three"] << endl;
  cout << "mymap2[\"four\"] is " << mymap2["four"] << endl;
  //mymap2.erase("one");
  cout <<mymap2<< endl;

//  cout << "mymap2 now contains " << mymap2.size() << " elements.\n";

  return 0;
}

