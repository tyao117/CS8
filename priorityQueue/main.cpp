#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include "priorityQueue.h"

using namespace std;

void perform(char choice, priorityQueue<string, int> &theQueue);
char menu();

int main(int argc, char *argv[])
{
    int big;
    cout<<"How big of a queue do you want? ";
    cin>>big;
    priorityQueue<string, int> example(big);
    while(true)
        perform(menu(), example);
    return 0;
}

char menu()
{
    cout<<"Options are: "<<endl
        <<"  + Enqueue data"<<endl
        <<"  - Dequeue data"<<endl
        <<"  F is the queue full?"<<endl
        <<"  E is the queue empty?"<<endl
        <<"  C clear the queue"<<endl
        <<"  R resize the queue"<<endl
        <<"  P Peek at the front of the queue"<<endl
        <<"  D Display the queue"<<endl
        <<"  I Read in a queue from a file"<<endl
        <<"  W Write out a queue to a file"<<endl
        <<"  Q quit"
        <<"Your selection: ";
    char choice;
    cin>>choice;
    return choice;
}


void perform(char choice, priorityQueue<string, int> &theQueue)
{
    string isNot;
    string data;
    int priority;
    string fileName;
    ofstream out;
    ifstream in;

    switch(toupper(choice))
    {
        case '+' :
                   try
                   {
                       cout<<"Please enter data: ";
                       cin>>data;
                       cout<<"Please enter the data\'s priority: ";
                       cin>>priority;
                       theQueue.enqueue(data,priority);
                   }
                   catch(PQ_ERRORS e)
                   {
                       cout<<"queue was full."<<endl;
                   }
                   break;

        case '-' :
                   try
                   {
                       theQueue >> data;
                       cout<<data<<" was just dequeued"<<endl;
                   }
                   catch(PQ_ERRORS e)
                   {
                      cout<<"queue was empty."<<endl;
                   }
                   break;

        case 'F' :
                    isNot = theQueue.full()? " is ": " is not ";
                    cout<<"The queue "+isNot+"full"<<endl;
                    break;

        case 'E' :
                    isNot = theQueue.empty()? " is ": " is not ";
                    cout<<"The queue "+isNot+"empty"<<endl;
                    break;

        case 'C' :
                    theQueue.clear();
                    break;

        case 'R' :
                    cout<<"Please enter the new queue size: ";
                    int size;
                    cin>>size;
                    theQueue.resize(size);
                    break;

        case 'P' :
                    cout<<"The data item at the front of the queue is :"<<theQueue.peek()<<endl;
                    break;

        case 'D' :
                    cout<<theQueue<<endl<<endl;
                    break;

        case 'W' :
                    cout<<"Name of output file: ";
                    cin>>fileName;
                    out.open(fileName.c_str());
                    out<<theQueue<<endl;
                    out.close();
                    break;

        case 'I' :
                    cout<<"Name of output file: ";
                    cin>>fileName;
                    in.open(fileName.c_str());
                    in>>theQueue;
                    in.close();
                    break;

        case 'Q' :
                    exit(1);

          default: cout<<"Unknown option. Please re-enter"<<endl<<endl;
       }
    cout<<endl<<endl;
}
