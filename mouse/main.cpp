#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>

#define COLOR1  1
#define COLOR2  2
void initialize();
bool kbinput();
void endProgram();
bool moveMouse(int &x, int &y, bool &attOnOff);

using namespace std;


int main ()
{
    initscr();
    int x = 20, y =12;
    bool attOnOff = true;
    initialize();
    attron(COLOR_PAIR(COLOR1) | A_BOLD);
    mvaddstr(y, x, " ");
    refresh();
    while(moveMouse(x, y, attOnOff));
    system("pause");
    endProgram();

}


bool moveMouse(int &x, int &y, bool &attOnOff)
{
     int c;
     static int count = 0;
     if(kbinput())
     {
        switch( c = getch())
        {
           case KEY_F(10) : return false;

           case KEY_UP  : y--;
                          if(y <= 0)
                            y = 23;
                          break;

           case KEY_DOWN : y++;
                           if(y >= 23)
                             y = 1;
                           break;

           case KEY_RIGHT : x++;
                           if(x >= 79)
                               x = 1;
                             break;

           case KEY_LEFT : x--;
                            if(x <= 1)
                                x = 79;
                           break;

           case KEY_F(9) : char string[80];
                           mvinstr(1,1,string);
                           attron(COLOR_PAIR(COLOR2));
                           mvaddstr(23,1,string);
                           refresh();
                           break;

                 case 32 : if(attOnOff)
                           {
                              attOnOff = false;
                              attron(COLOR_PAIR(COLOR2));
                           }
                           else
                           {
                              attOnOff = true;
                              attron(COLOR_PAIR(COLOR1));
                           }

        }
       int data = mvinch(y,x);
       data &= A_COLOR;
       if(data == COLOR_PAIR(COLOR1))
          count++;

       mvaddstr(y,x, " ");
       move(1,1);
       clrtoeol();
       attron(COLOR_PAIR(COLOR2));
       mvprintw(1,1, "The pen is at y = %3d x= %3d collision count: %3d",y,x, count);
       if(attOnOff)
         attron(COLOR_PAIR(COLOR1));
       refresh();
       return true;
     }
}

void initialize()
{
    initscr ();                 //Turn on curses
    cbreak ();                  //Turn off carriage return to enter data
    raw();
    nodelay(stdscr,true);       //getch does not wait
    noecho ();                  //Turn off echoing of input
    start_color ();             //Turn on coloring of output
    keypad (stdscr, TRUE);      //Turn on F key entry and arrowkeys
    curs_set(0);                //Set screen to default WHITE on BLACK

    if (!has_colors ())         //If colors not available, kill program
    {
        endwin ();
        fputs ("No colors!", stderr);
        exit (1);
    }
    //Initialize color pairs
    init_pair (COLOR1, COLOR_WHITE, COLOR_YELLOW);
    init_pair (COLOR2, COLOR_WHITE, COLOR_BLACK);

    refresh();
}

bool kbinput()
{
     int ch = getch();
     if(ch == ERR)
        return false;
     ungetch(ch);
     return true;
}

void endProgram()
{
    erase ();
    refresh ();
    endwin ();
    exit(0);
}
