#include "flush.h"
/* Implement "flush", a unix shell with some functions. 
* 
*
* Main functions that needs to be included:
*/

/**
 * @brief Practical Excercise 3
 * 
 * Unix Shell
 * 
 * @return char* 
 */

Job *first_job = NULL;


void add_to_list(Job *job) {
    if (!first_job) {
        first_job = job;
    }
    Job *j = first_job;
    while(j->next) {
        j = j->next;
    }
    j->next = job;
    job->prev = j;

}




Job *remove_from_list(Job *job) { // [TODO: Skrive ferdig denne, bare vanlig remove fra en lenkeliste]
    Job* j;
    for (j = first_job; j; j = j->next) {
        if(j->pid == job->pid) {
            if (!j->prev && !j->next) {
                first_job = NULL;
            }
            else {

            }
        }
    }
}

void print_job(Job *job) {
    printf("[%d]: ", job->pid);
    for (int i = 0; i; i < job->size) {
        printf("%s", job->args[i]);
    }
}


void print_all_jobs() {
    Job *j;
    for (j = first_job; j; j = j->next) {
        print_job(j);
    }
}

int cmd_cd(Job *job) { // 
    
    if (job->args[1] == NULL) {
            fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    } else {
        if (chdir(job->args[1]) != 0) {
            perror("lsh");
        }
         else {
            return 1;
        }
    }
        
}

int cmd_io(Job *job) { // [TODO: skrive denne, vet ikke hvem som skrev det som er inni her, men skal hvertfall være io-redirection]
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
    print_job(job);
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

// Function for reading command line and returning to main [WOORKING]
char *read_line(void) {
    
    int bsize = BUFSIZE;
    char *cmdline = malloc(bsize);

    fgets(cmdline, bsize, stdin); //read command line
    
    if (feof(stdin)) // check for end of stream
        exit(0);

    
    return cmdline;
}

// Void function to print out the file path [WORKING]
Job *parse_cmdline(char *cmdline, Job *job) {
    
    int bufsize = MAXARGS, pos = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;
    int bg;

    
    token = strtok(cmdline, DELIM);
   
    while(token != NULL) { // run until there are no input left
        tokens[pos] = token;
        pos++;
        //printf("Position %d: %s", pos, token);
        if (pos >= bufsize) {
            bufsize += BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        
        token = strtok(NULL, DELIM);
        //printf("%d", pos);
    }
    job->size=pos-1;
    job->args=tokens;
    return job;
    
    // check if last element is '&' -> set background to 1 (true) 
    //if ((bg = (*argv[argc-1] == '&')) != 0)
      //  argv[--argc] = NULL;

    
}

// [TODO: Make a linked list with jobs, use "next" and "prev" in job struct]
/*struct node 
{
    int pid;
    struct node *prev;
    struct node *next;
}*/

int launch(Job *job) {
    int bg = 0; // Process should run in background
    int cpid;

    if (*job->args[job->size-1] == '&') {
        bg = 1;
    }
    
    // loope gjennom builtin 

    if (cpid = fork() == 0) {
        job->pid = getpid();
        if (builtin_cmd(job)) {
            job->finished = 1;
        } 
        else {
            if (execvp(job->args[0], job->args) == -1) {
                perror("lsh");
            }
        exit(EXIT_FAILURE);
        }
       
    }
    else {
        if (!bg) { // if process is running in foreground, parent should wait until finished
            int status;
            printf("YOOO");
            if (waitpid(job->pid, &status, WUNTRACED > 0)) {
                if (WIFSTOPPED(status)) {
                    job->finished = 1;
                } else {
                    remove_from_list(job);

                }
            }
        }
    }

    


}

// Function to print out current file directory + ':'
void type_prompt() {
    char cwd[MAXPATH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("\n%s:", cwd);
    } else {
        perror("getcwd() error");
        exit(1);
    }
}
 // Function to evaluate input coming from user
/*void evaluate(char *cmdline) {
    int argc;
    char *argv[MAXARGS];
    int background; // determine if process should run fg or bg
    static unsigned job_id = 0;


    
    background = parse_line(cmdline, &argc, argv);


    return background;


*/

    // fork new process to execute command

//}


/*int redirection() {
    // open path trengs vel ikke?
    int fd = open(path);
    if(fork() == 0) {
        //Child
        close(STDIN_FILENO);
        dup(fd);
        close(fd);
        // Execute process
    } else {
        //Parent
        close(fd);
    }
}*/

// Har allerede en termination i launch-metoden
int termination(int pid) {
    int status = 0;
    
    if (waitpid(pid, &status, 0))
    {
        if ( WIFEXITED(status) )
        {
            int exit_status = WEXITSTATUS(status);       
            printf("Exit status of the child was %d\n", exit_status);
            return exit_status;
        }
    }
    return -1;
    
}



int main(int argc, char **argv) {
    
    char *cmdline = malloc(BUFSIZE);
    char **args;
    int status;
    
    while (1) {
        Job *job = malloc(sizeof(Job));

        printf("\n\nHEi\n\n");
        type_prompt(); //print file path with ':' 
        cmdline = read_line();    
        printf("%s", cmdline);    
        print_job(job);
        job = parse_cmdline(cmdline, job);
        add_to_list(job);
        printf("%d",job->size);
        
        launch(job);


    }
    return 0;
}