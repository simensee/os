#include "Flush.h"
/* Implement "flush", a unix shell with some functions. 
* 
*
* Main functions that needs to be included:
*/

// Void function to print out the file path 
char **parse_line(char *buffer, int *n_arg, char **argv) {
    
    int bufsize = BUFSIZE, position = 0;
    char **argv = malloc(bufsize * sizeof(char*));
    char *token;
    
    token = strtok(buffer, DELIM);
    while(token != NULL) { // run until there are no input left
        //argv[pos]
    }
    

    
    // check if last element is '&' -> set background to 1 (true) 
    if ((bg = (*argv[argc-1] == '&')) != 0)
        argv[--argc] = NULL;
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
void evaluate(char *cmdline) {
    int argc;
    char *argv[MAXARGS];
    int background; // determine if process should run fg or bg
    static unsigned job_id = 0;

    
    
    background = parse_line(cmdline, &argc, argv);




    
    



    // fork new process to execute command

}


int main(int argc, char **argv) {
    
    char cmdline[MAXARGS];


    while (1) {

        type_prompt(); //print file path with ':' 

        fgets(cmdline, MAXARGS, stdin); // get input from user

        if (feof(stdin)) {
            exit(0);
        }
        
        evaluate(cmdline); 

    }
    return 0;
}