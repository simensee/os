#ifndef Flush_h
#define Flush_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Flush.h"

#define MAXARGS 128
#define MAXPATH 256
#define BUFSIZE 64
#define DELIM " \t\r\n\a"



void parse_arguments(char *str) ;

void type_promt();


#endif