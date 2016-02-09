#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//This program shows pointers to functions
//It goes on an infinite loop until 'Q' or 'q' is called

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
    whatToDo['U'] = whatToDo['u'] = up;
    whatToDo['D'] = whatToDo['d'] = down;
    whatToDo['R'] = whatToDo['r'] = right;
    whatToDo['L'] = whatToDo['l'] = left;
    whatToDo['Q'] = whatToDo['q'] = quit;
    while(1)
        (whatToDo[rand()%128])();
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
