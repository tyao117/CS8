#ifndef DRIVER_H
#define DRIVER_H

#include <cstdlib>
#include <iostream>
#include "LinkedListQueue.h"
#include <string>
#include <fstream>
#include <cstring>


using namespace std;

char menu(string title[]);

void perform(char ans, int &list, LinkedListQueue<string> &one, LinkedListQueue<string> &two);
void loadfile(LinkedListQueue<string> &one,char *filename); // insert data from file to a queue
void help();
void checkArgs(int argc, char *argv[],LinkedListQueue<string> &one,LinkedListQueue<string> &two, int &list);



#endif // DRIVER_H
