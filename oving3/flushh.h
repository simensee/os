
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_LIMIT 200
#define BUFSIZE 1024
#define MAXPATH 256
#define MAXARGS 128
#define DELIM " \t\r\n\a"


typedef struct job
{
    int pid;
    char cmdline[MAX_LIMIT];
    struct job *prev;
    struct job *next;
} job ;