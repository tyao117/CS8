#include <iostream>

using namespace std;

typedef int (*fptr)(int x, int y);

int add(int x, int y);
int sub(int x, int y);
int mult(int x, int y);
int div(int x, int y);
void perform(char *title, int x, int y, fptr whatToDo);

int main()
{
    perform(" addition",3,4,add);
    perform(" subtraction ",3,4,sub);
    perform(" multiply ",3,4,mult);
    perform(" remainder ",3,4,div);

    return 0;
}

int add(int x, int y)
{
    return x + y;
}

int sub(int x, int y)
{
    return x - y;
}

int mult(int x, int y)
{
    return x * y;
}

int div(int x, int y)
{
    return x / y;
}

void perform(char *title, int x, int y, fptr whatToDo)
{
    cout<<"The "<<title<<" of "<<x<<" and "<<y<<" is "
        <<whatToDo(x,y)<<endl;
}

