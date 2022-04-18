#ifndef JOB_H
#define JOB_H

//#include "Flush.h"
//#include "Builtin.h"
#include <stddef.h>
#include <stdio.h>

//#include "builtin.h"

//void add_to_list(Job *job);


typedef struct Job {
    
    char **args;
    int size;
    int pid;
    int bg;
    struct Job *next;
    struct Job *prev;
    int finished;
} Job;

void print_all_jobs();
Job *remove_from_list(Job *job);
void add_to_list(Job *job);
extern Job *first_job;
#endif