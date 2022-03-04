#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


typedef struct alarm {
        time_t alarm_time;
        int pid;
        char sound;
}Alarm;

static struct alarm alarms[10];

void empty_stdin() 
{
    int c = getchar();

    while (c!= '\n' &&  c != EOF) 
        c = getchar();
}

int alarms_size() { // find size of alarms array
    int size=0;
    for (int i=0; i < sizeof(alarms); i++) {
        if (alarms[i].pid != 0) {
            size++;
        }
    }
    return size;
}

void print_system_time(time_t t){
    const struct tm *tm = localtime(&t);
    printf("%04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
}



void list_alarms() { // list all active alarms 
    for(int i = 0; i < alarms_size(); i++)
    {
        if (alarms[i].pid != 0) {
            
            printf("\nAlarm %d at ", i+1);
            print_system_time(alarms[i].alarm_time);
            printf(" with ID: %d\n\n", alarms[i].pid);
        }
        
    }
    
}

void insert_alarm_in_array(struct alarm alarm ) {
    int i, pos; 
    
    for(i=0;i<=alarms_size();i++) // find correct position for alarm 
    {
   	    if(alarm.alarm_time<alarms[i].alarm_time || alarms[i].alarm_time == 0) 
        {
            pos = i;
            break;
        }
        else
        {
     	    pos=i+1;
        }
	}
    for(i=alarms_size();i>=pos;i--) {
        alarms[i]= alarms[i-1];
        
    }
    
    alarms[pos]=alarm;

}

void cancel_alarm(int pid) { // delete alarm from array 
    
    int pos;
    for (int i=0; i<=alarms_size(); i++) { // find position of alarm with correct pid
        
            if (pid == alarms[i].pid) {
                pos = i;
            }
            
    }
     for(int i=pos; i<alarms_size(); i++) // copy next element to current
        {
            alarms[i] = alarms[i + 1];
        }
    

}

void cancel_alarms() { 
    int input;
    int i;
    pid_t pid;
    printf("Cancel which alarm?\n");
    scanf("%d", &input);
    
    
    pid = alarms[input-1].pid;
    
    
    if(input-1 < 0 || input > alarms_size()) 
    {
        printf("\nInvalid position! Please enter position between 1 to %d\n", alarms_size());
    }
    else
    {
        /* Copy next element value to current element */
        for(i=input-1; i<alarms_size(); i++)
        {
            alarms[i] = alarms[i + 1];
        }

    }

    printf("\nCancel alarm with id: [%d]\n", pid);

    
    kill(pid, SIGTERM); // kills cancelled c
    
}

int new_alarm() { 
    struct tm result = {0};
    time_t t, now;
    int diff, st, pid;
    char buff[19];
    do {
        printf("\nEnter the alarm in format \"YYYY-MM-dd hh:mm:ss\" :");
        scanf(" %[^\n]19s", buff); 
        empty_stdin();
        strptime(buff, "%Y-%m-%d %H:%M:%S", &result);
        t = mktime(&result); 
        time(&now);
        diff = (int) difftime(t, now);
        if (diff < 0 ) {
            printf("\nEnter a valid alarm time!\n");
            
        }
    } while (diff <= 0);
    pid = fork();
    
    if (pid == 0) { 
        sleep(diff);
        
        printf("\nRIIIIING\n");
        execlp("afplay", "afplay", "alarm-clock-01.wav", NULL);
        exit(0);
        
    }

    else {
        struct alarm new_alarm;
        new_alarm.alarm_time = t;
        new_alarm.pid = pid;
        insert_alarm_in_array(new_alarm);

        printf("\nScheduling alarm in: %d seconds\n", diff); 
        strftime(buff,sizeof(buff), "%Y-%m-%d %H:%M:%S", &result);

        return 0;

    }

    
    
}


    
    
int main(void) {
    time_t now;
    char input;
    int pid, st;

    time(&now);
    printf("Welcome to the alarm clock! It is currently ");
    print_system_time(now);

    do {

        printf("Please enter \"s\" (schedule), \"l\" (list), \"c\" (cancel), \"x\" (exit): ");
        scanf("%c", &input);

        
        if (input == 'l') {
            list_alarms();
            empty_stdin();

            input = 'r';
        }

        if (input == 's') {
            new_alarm();
            input = 'r';
        }

        if (input == 'c') {
            cancel_alarms();
            empty_stdin();

            input = 'r';
        }

        
        while ((pid = waitpid(-1, &st, WNOHANG)) > 0) { // Deletes already rung child process from array and kills zombie
            cancel_alarm(pid);
        } 
    } 
    while(input != 'x');
    printf("\nGoodbye!\n");
    sleep(2);
    return 0;

}




