#ifndef DRIVER_H
#define DRIVER_H

#include <cstdlib>
#include <iostream>
#include "arrayQueue.h"
#include <string>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

char menu(string title[]);
void perform(char ans, int &list, queue<char> &one, queue<char> &two);
void loadfile(queue<char> &one,char *filename);
void help();
void checkArgs(int hi, char *bye[], queue<char> &one, queue<char> &two, int &list);

#endif // DRIVER_H
