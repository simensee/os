#include "flushh.h"

// global variables for linked list, first and last job in list
job *first_job = NULL;
job *last_job = NULL;


// read cmdline from user
char *read_line(void) {
    
    int bsize = BUFSIZE;
    char *cmdline = malloc(bsize);

    fgets(cmdline, bsize, stdin); //read command line
    
    if (feof(stdin)) // check for end of stream
        exit(0);

    return cmdline;

}

// parsing cmdnline into arguments
void parse_cmdline(char *cmdline, char **args) {
    
    int bufsize = MAXARGS, pos = 0;
    
    char *token;

    
    token = strtok(cmdline, DELIM);
   
    while(token != NULL) { // run until there are no input left
        args[pos] = token;
        pos++;
        
        if (pos >= bufsize) {
            bufsize += BUFSIZE;
            args = realloc(args, bufsize * sizeof(char*));
            if (!args) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        
        token = strtok(NULL, DELIM);
       
    }


}


// printing out file directory + ':'
void type_prompt() {
    char cwd[MAXPATH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("\n%s:", cwd);
    } else {
        perror("getcwd() error");
        exit(1);
    }
}


void check_status(int status, char *cmdline)
{
    cmdline[strcspn(cmdline, "\r\n")] = 0; // removes newline from cmdline

    if (WIFEXITED(status))
    {
        int stat = WEXITSTATUS(status);
        printf("Exit status [%s] = %d\n", cmdline, stat);
    }
}

// add job to linked list

void add_job(int pid, char *cmdline)
{
    job *new_job = (job *)malloc(sizeof(job));

    
    new_job->pid = pid;
    strcpy(new_job->cmdline, cmdline);

    //update next
    new_job->next = NULL;
    if (first_job == NULL)
    {
        first_job = new_job;
    }
    
    // update prev
    new_job->prev = last_job;
    if (last_job != NULL)
    {
        last_job->next = new_job;
    }
    last_job = new_job;

    
}

// print all bg jobs in linked list

void print_all_jobs()
{
    job *j = first_job;
    while (j != NULL)
    {
        printf("[pid %d] %s\n", j->pid, j->cmdline);
        j = j->next;
    }
}

// remove job from linked list

void remove_job(job *j)
{
    /* checks if first node */
    if (j->prev != NULL)
    {
        j->prev->next = j->next;
    }
    else
    {
        first_job = j->next;
    }

    /* checks if last node */
    if (j->next != NULL)
    {
        j->next->prev = j->prev;
    }
    else
    {
        last_job = j->prev;
    }
    free(j);
}


// check for completed processes

void check_jobs()
{
    job *j = first_job;
    while (j != NULL)
    {
        int status;

        
        if (waitpid(j->pid, &status, WNOHANG))
        {
            check_status(status, j->cmdline);

            remove_job(j);
        }
        j = j->next;
    }
}




int check_bg(char cmdline[MAX_LIMIT])
{
    // removes newline from cmdline
    cmdline[strcspn(cmdline, "\r\n")] = 0;
    int size = strlen(cmdline) - 1;
    int bg;
    
    // check for bg via '&' and removes it
    
    if ((size> 0) && ((bg = cmdline[size]) == '&'))
    {
        cmdline[size] = '\0';
    }


    return bg;
}






int cmd_cd(char **args) { // change directory command
    
    if (args[1] == NULL) {
            fprintf(stderr, "Expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("lsh");
        }
         else {
            return 0;
        }
    }
        
}

int builtin_cmd(char **args) { // builtin commands
    
    if (!strcmp(args[0], "cd")) {
        return cmd_cd(args);
    }

    if (!strcmp(args[0], "jobs")) { // print all bg jobs
        print_all_jobs();
        return 0;
        
    }
    
    // check for io redirection
    for (int i = 0; i < MAX_LIMIT; i++)
    {
        if (!args[i])
            break;

        printf("%s\n", args[i]);
        if (strpbrk((char*) args[i], "<>")) {
            return 1;
        }
        
    }
}


// executing command line
void launch(char **args, char *cmdline) 
{
    int bg = check_bg(cmdline);
    int is_io = 0;

    // check if the command is builtin
    is_io = builtin_cmd(args);


    
   
    int status;
    pid_t cpid = fork();

    if (cpid == -1)
    {
        perror("Failed to fork");
    }
    if (cpid > 0) { // inside parent
        
        if (bg)
        {
            // adds job to list
            add_job(cpid, cmdline);
        }
        else
        {
            waitpid(cpid, &status, 0); // waits for child
            check_status(status, cmdline); 
        }
    
    }
    if (cpid == 0) // inside child
    {
        
        if (is_io) 
        {

            execl("/bin/sh", "/bin/sh", "-c", cmdline, (char *)0); // executes io redirection
        }
        else
        {
            execvp(args[0], args); // executes standard command
        }
        exit(EXIT_FAILURE);
    }
    
}



int main(void) 
{
    char *cmdline = malloc(BUFSIZE);
    char cmdline_copy[BUFSIZE];
    char **args = malloc(BUFSIZE);

    while (1)
    {
        // checks linked list of bg jobs
        check_jobs();

        // prints current directory
        type_prompt();

        // reads input cmdline from user
        cmdline = read_line();

        // makes copy of cmdline from user
        strcpy(cmdline_copy, cmdline); 

        // splits cmdline into arguments
        parse_cmdline(cmdline, args);
        
        
        // launches and executes command line
        launch(args, cmdline_copy);
    }
}