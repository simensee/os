#include "Flush.h"
/* Implement "flush", a unix shell with some functions. 
* 
*
* Main functions that needs to be included:
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
int launch(Job *job) {
    int bg; // Process should run in background
    int cpid;

    if (*job->args[job->size-1] == '&') {
        bg = 1;
    }
    
    // loope gjennom builtin 

    if (cpid = fork() == 0) {
        job->pid = getpid();
        if (execvp(job->args[0], job->args) == -1) {
            perror("lsh");
        }
    exit(EXIT_FAILURE);
    }

    if (!bg) { // if process is running in foreground, parent should wait until finished
        int status;
        if (waitpid(job->pid, &status, WUNTRACED > 0)) {
            if (WIFSTOPPED(status)) {
                job->finished = 1;
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


int main(int argc, char **argv) {
    
    char *cmdline = malloc(BUFSIZE);
    char **args;
    int status;
    
    while (1) {
        Job *job = malloc(sizeof(Job));
       

        add_to_list()

        while ()
        type_prompt(); //print file path with ':' 
        cmdline = read_line();    
        printf("%s", cmdline);    
        parse_cmdline(cmdline, job); 
        printf("\nLast token: %s\n",(char *) job->args[job->size]);
        
        launch(job);


    }
    return 0;
}