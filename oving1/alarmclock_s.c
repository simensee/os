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
}Alarm;

static struct alarm alarms[10];

void empty_stdin() 
{
    int c = getchar();

    while (c!= '\n' &&  c != EOF) 
        c = getchar();
}

int alarms_size() {
    int size=0;
    for (int i=0; i < sizeof(alarms); i++) {
        if (alarms[i].pid != 0) {
            size++;
        }
    }
    return size;
}

void printSystemTime(time_t t){
    const struct tm *tm = localtime(&t);
    printf("%04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
}

void add_alarm_array(time_t alarm_time, pid_t pid) { // [TODO] legge til alarm i array 'alarms'

}

void list_alarms() { // list all active alarms 
    //for(int i = 0; i <= alarms_size() / sizeof(struct alarm); i++)
    for(int i = 0; i < alarms_size(); i++)
    {
        if (alarms[i].pid != 0) {
            
            printf("\nAlarm %d at ", i+1);
            printSystemTime(alarms[i].alarm_time);
            printf(" with ID: %d\n\n", alarms[i].pid);
        }
        
    }
    
}

void InsertAlarmInArray(struct alarm alarm ) {
    int i, pos; 
    
    for(i=0;i<=alarms_size();i++)
    {
   	    if(alarm.alarm_time<alarms[i].alarm_time || alarms[i].alarm_time == 0)
        {
            pos = i;
            //printf("%d",i);
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
    //printf("\nOld alarm array size: %d\n", alarms_size());
    int pos;
    for (int i=0; i<=alarms_size(); i++) { // find position of alarm with correct pid
        //printf("\nPid for process: %d", alarms[i].pid);
        //printSystemTime(alarms[i].alarm_time);
            if (pid == alarms[i].pid) {
                pos = i;
                //printf("\nPosition of deleted process: %d\n", pos);
            }
            
    }
     for(int i=pos; i<alarms_size(); i++) // copy next element to current
        {
            alarms[i] = alarms[i + 1];
        }
    

}

void cancel_alarms() { // cancel all alarms
    int input;
    int i;
    pid_t pid;
    printf("Cancel which alarm?\n");
    scanf("%d", &input);
    //empty_stdin();

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


        /* Print array after deletion */
        printf("\nElements of array after delete are : ");
        list_alarms();
        
    }

    printf("\nCancel alarm with id: [%d]\n", pid);

    
    kill(pid, SIGTERM);
    /*
    for(i = 0; i < sizeof(alarms) / sizeof(alarms); i++)
    {
        if (alarms[i].pid == i)
        {
            // cancel alarm with pid=i TODO
            
        }
        
    }*/
}

int new_alarm() { 
    struct tm result = {0};
    time_t t, now;
    int diff, st, pid;
    char buff[19];
    printf("Enter the alarm in format \"YYYY-MM-dd hh:mm:ss\" :");
    scanf(" %[^\n]19s", buff); 
    empty_stdin();
    //puts(buff);ss

    
    strptime(buff, "%Y-%m-%d %H:%M:%S", &result);
    t = mktime(&result); 
    time(&now);
    diff = (int) difftime(t, now);

    //[NY KODE START]: klone prosessen og få den til å ringe etter x sekunder
    pid = fork();
    
    if (pid == 0) {
        sleep(diff);
        printf("\nRIIIIING\n");
        /*printf("\nID of child process: %d\n", getpid());
        printf("Array in child proces [%d]:", getpid());
        list_alarms();*/
        //ancel_alarm(getpid());
        exit(0);
        //kill(getpid(), SIGTERM);
    }

    else {
        struct alarm new_alarm;
        new_alarm.alarm_time = t;
        new_alarm.pid = pid;
        InsertAlarmInArray(new_alarm);



        //TODO legge struct alarm inn i array

        //[NY KODE SLUTT]
        printf("\nScheduling alarm in: %d seconds\n", diff); // Endret her for å printe ut differansen mellon ringetidspunkt og nå
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
    printSystemTime(now);
    //getchar();

    do {
        printf("Please enter \"s\" (schedule), \"l\" (list), \"c\" (cancel), \"x\" (exit): ");
        scanf("%c", &input);
        empty_stdin();
        
        if (input == 'l') {
            list_alarms();
            input = 'r';
        }

        if (input == 's') {
            new_alarm();
            input = 'r';
        }

        if (input == 'c') {
            cancel_alarms();
            input = 'r';
        }
        
        while ((pid = waitpid(-1, &st, WNOHANG)) > 0) {
            //printf("Child pid [%d] exited\n", pid);
            cancel_alarm(pid);
        } 
    } 
    while(input != 'x');
    printf("\nGoodbye!\n");
    sleep(2);
    return 0;

}




