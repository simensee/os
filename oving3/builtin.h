#ifndef BUILTIN_H
#define BUILTIN_H

#include <string.h>
#include <unistd.h>
#include "job.h"


int builtin_cmd(Job *job);
int cmd_cd;
#endif