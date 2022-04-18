#include "builtin.h"
//#include "job.h"

int cmd_cd(Job *job) { // 
    if (job->args[1] == NULL) {
            fprintf(stderr, "lsh: expected argument to \"cd\"\n");
        } else {
            if (chdir(job->args[1]) != 0) {
                perror("lsh");
            }
        }
        return 1;
}

int cmd_io(Job *job) {
    /*int fd = open(path);
    if(fork() == 0) {
        //Child
        close(STDIN_FILENO);
        dup(fd);
        close(fd);
        // Execute process
    } else {
        //Parent
        close(fd);
    }*/
    return 1;
}

int builtin_cmd(Job *job) {

    if (strpbrk((char*) job->args, "<>")) { // check if 
        return cmd_io(job);
        
    }
    
    if (!strcmp(job->args[0], "cd")) {
        return cmd_cd(job);
    ;
    }

    if (!strcmp(job->args[0], "jobs")) {
        print_all_jobs();
        return 1;
        
    }
}


