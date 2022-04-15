#include "Flush.h"
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
char **parse_cmdline(char *cmdline, Job *job) {
    
    int bufsize = MAXARGS, pos = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;
    int bg;

    
    token = strtok(cmdline, DELIM);
    printf("%s", token);
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
        job->size=pos-1;
        token = strtok(NULL, DELIM);
        //printf("%d", pos);
    }
    job->args=tokens;
    
    
    // check if last element is '&' -> set background to 1 (true) 
    //if ((bg = (*argv[argc-1] == '&')) != 0)
      //  argv[--argc] = NULL;

    
}

// [TODO: Make a linked list with jobs, use "next" and "prev" in job struct]
struct node 
{
    int pid;
    struct node *prev;
    struct node *next;
}
int launch(Job *job) {
    int bg; // Process should run in background
    int cpid;
    if (*job->args[job->size-1] == '&') {
        bg = 1;
    }
    


    if (cpid = fork() == 0) {
        job->pid = getpid();
        if (execvp(args[0], args) == -1) {
            perror("lsh");
        }
    exit(EXIT_FAILURE);
    }
    if (!bg) { // if process is running in foreground, parent should wait until finished
        waitpid(job->pid);
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


int redirection() {
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
}


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
        type_prompt(); //print file path with ':' 
        cmdline = read_line();    
        printf("%s", cmdline);    
        parse_cmdline(cmdline, job); 
        printf("\nLast token: %s\n",(char *) job->args[job->size]);
        
        launch(job);


    }
    return 0;
}