#include "Builtin.h"

int builtin_cmd(Job *job) {

    if (strbrpk((char) job->args), "<>") { // check if 
        cmd_io(job);
    }
    
    if (!strcmp(job->args[0], "cd")) {
        return cmd_cd(job);
    }

    if (!strcmp(job->args[0], "jobs")) {
        // printe ut listen av jobs
    }
}


int cmd_cd(Job *job) { // 
    if (job->args[1] == NULL) {
            fprintf(stderr, "lsh: expected argument to \"cd\"\n");
        } else {
            if (chdir(job->args[1]) != 0) {
                perror("lsh");
        }
}

int cmd_io(Job *job) {
    // change
}