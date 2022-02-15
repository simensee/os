#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

//int main(void) {
    /*char c;
    time_t t = time(NULL);
    struct tm current_time = *localtime(&t);
    int c_time = mktime(&current_time);

    struct alarm {
        struct tm time;
        int pid;
    }*/

typedef struct alarm {
        time_t alarm_time;
        int pid;
}Alarm;

struct alarm alarms[10];

void empty_stdin() 
{
    int c = getchar();

    while (c!= '\n' &&  c != EOF) 
        c = getchar();
}

/*const char * variable_to_string(time_t time) {
    char buff[100];
    strftime(buff, 100, "%Y-%m-%d %H:%M:%S", localtime(&time));
    return buff;
}*/
void printSystemTime(time_t t){
    const struct tm *tm = localtime(&t);
    printf("%04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
}

void add_alarm_array(time_t alarm_time, pid_t pid) { // [TODO] legge til alarm i array 'alarms'

}

void list_alarms() { // list all active alarms 
    int i;
    for(i = 0; i < sizeof(alarms) / sizeof(struct alarm); i++)
    {
        printf("Alarm %d at ", i);
        printSystemTime(alarms[i].alarm_time);
    }
    
}

void cancel_alarms(int i) { // cancel all alarms

    pid_t pid = alarms[i].pid;


    for(i = 0; i < sizeof(alarms) / sizeof(struct alarm); i++)
    {
        if (alarms[i].pid == i)
        {
            // cancel alarm with pid=i TODO
            
        }
        
    }
}

int new_alarm() { 
    struct tm result = {0};
    time_t t, now;
    int diff;
    char buff[19];
    printf("Enter the alarm in format \"YYYY-MM-dd hh:mm:ss\" :");
    scanf(" %[^\n]19s", buff); 
    empty_stdin();
    //puts(buff);
    strptime(buff, "%Y-%m-%d %H:%M:%S", &result);
    t = mktime(&result); 
    time(&now);
    diff = (int) difftime(t, now);

    //[NY KODE START]: klone prosessen og få den til å ringe etter x sekunder
    pid_t pid = fork();
    
    if (pid == 0) {
        sleep(diff);
        printf("RIIIIING\n");
        kill(getpid(), SIGTERM);
    }

    struct alarm new_alarm;
    new_alarm.alarm_time = t;
    new_alarm.pid = getpid();
    //TODO legge struct alarm inn i array

    //[NY KODE SLUTT]
    printf("Scheduling alarm in: %d seconds\n", diff); // Endret her for å printe ut differansen mellon ringetidspunkt og nå
    strftime(buff,sizeof(buff), "%Y-%m-%d %H:%M:%S", &result);
    
    return 0;
    
}


    
    
int main(void) {
    time_t now;
    char input;
    time(&now);
    printf("Welcome to the alarm clock! It is currently ");
    printSystemTime(now);
    printf("Please enter \"s\" (schedule), \"l\" (list), \"c\" (cancel), \"x\" (exit): ");
    scanf("%c", &input);
    empty_stdin();
    //getchar();

    do {
        if (input == 'l') {
            printf("Enter the alarm in format \"dd-MM-YY hh:mm:ss\" :");
            list_alarms();
        }

        if (input == 's') {
            new_alarm();
        }

        if (input == 'c') {

        }
        
        
    } 
    while(input != 'x');
    printf("\nGoodbye!\n");
    sleep(2);
    return 0;

}




