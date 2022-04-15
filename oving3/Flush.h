#ifndef Flush_h
#define Flush_h


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "Flush.h"

#define MAXARGS 128
#define MAXPATH 256
#define BUFSIZE 1024
#define DELIM " \t\r\n\a"

typedef struct Job {
    int jid;
    char **args;
    int size;
    int pid;
    int bg;
    int next;
    int prev;
} Job;


char *read_cmdline(void);

char **parse_cmdline(char *cmdline, Job *job);

int execute(char *cmdline);

void type_promt();

void execute_cmd();

#endif