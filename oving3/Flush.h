#ifndef Flush_h
#define Flush_h


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "Flush.h"
#include "job.c"

#define MAXARGS 128
#define MAXPATH 256
#define BUFSIZE 1024
#define DELIM " \t\r\n\a"

typedef struct Job {
    
    char **args;
    int size;
    int pid;
    int bg;
    int next;
    int prev;
    int finished;
} Job;


char *read_cmdline(void);

char **parse_cmdline(char *cmdline, Job *job);

int execute(char *cmdline);

void type_promt();

void execute_cmd();

#endif