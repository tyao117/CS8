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
    fptr whatToDo[300];
//    srand(time(NULL));
    for(int i = 0; i < 128; ++i)
        whatToDo[i] = null;
    initscr();//enable getchar functions
    whatToDo['W'] = whatToDo['w'] = up;
    whatToDo['S'] = whatToDo['s'] = down;
    whatToDo['A'] = whatToDo['a'] = left;
    whatToDo['D'] = whatToDo['d'] = right;
    whatToDo['Q'] = whatToDo['q'] = quit;
    while(1)
    {
        int w = getchar();
        //ungetch(w);
//        char w = getchar();
//        (whatToDo[getchar()])();
        (whatToDo[w])();
        refresh();
    }

    return 0;
}


void left()
{
    cout<<"Left"<<"";
}

void right()
{
    cout<<"Right"<<"";
}

void up()
{
    cout<<"Up"<<"";
}

void down()
{
    cout<<"Down"<<"";
}

void quit()
{
    exit(0);
}

void null()
{
    cout<<"";
}

