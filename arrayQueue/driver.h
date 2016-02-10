#ifndef DRIVER_H
#define DRIVER_H

#include <cstdlib>
#include <iostream>
#include "arrayQueue.h"
#include <string>
#include <fstream>
#include <cstring>


using namespace std;

char menu(string title[]);

void perform(char ans, int &list, queue<string> &one, queue<string> &two);
void loadfile(queue<string> &one,char *filename); // insert data from file to a queue
void help();
void checkArgs(int argc, char *argv[],queue<string> &one,queue<string> &two, int &list);



#endif // DRIVER_H
