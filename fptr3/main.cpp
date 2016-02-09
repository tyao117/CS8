#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>

using namespace std;

typedef void (*fptr)();

void left();
void right();
void up();
void down();
void quit();
void null();

int main()
{
    fptr whatToDo[128];
    srand(time(NULL));
    for(int i = 0; i < 128; ++i)
        whatToDo[i] = null;
    whatToDo['W'] = whatToDo['w'] = up;
    whatToDo['S'] = whatToDo['s'] = down;
    whatToDo['A'] = whatToDo['a'] = right;
    whatToDo['D'] = whatToDo['d'] = left;
    whatToDo['Q'] = whatToDo['q'] = quit;
    while(getch() == '\033')
        (whatToDo[getch()])();

    return 0;
}


void left()
{
    cout<<"Left"<<endl;
}

void right()
{
    cout<<"Right"<<endl;
}

void up()
{
    cout<<"Up"<<endl;
}

void down()
{
    cout<<"Down"<<endl;
}

void quit()
{
    exit(0);
}

void null()
{
    cout<<" "<<endl;
}

