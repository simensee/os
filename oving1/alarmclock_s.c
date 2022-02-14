#include <stdio.h>

#include <stdlib.h>
#include <time.h>

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
} Alarm;

struct alarm alarms[10];

/*const char * variable_to_string(time_t time) {
    char buff[100];
    strftime(buff, 100, "%Y-%m-%d %H:%M:%S", localtime(&time));
    return buff;
}*/
void printSystemTime(time_t t){
    const struct tm *tm = localtime(&t);
    printf("%04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
}

void list_alarms() { // list all active alarms 
    int i;
    for(i = 0; i < sizeof(alarms) / sizeof(struct alarm); i++)
    {
        printf("Alarm %d at ", alarms[i].pid);
        printSystemTime(alarms[i].alarm_time);
    }
    
}

void cancel_alarms(int i) { // cancel all alarms
    for(i = 0; i < sizeof(alarms) / sizeof(struct alarm); i++)
    {
        if (alarms[i].pid == i)
        {
            // cancel alarm with pid=i TODO
        }
        
    }
}

int new_alarm() { // initialize new alarm TODO
    char time_str;
    struct tm a_time;
    scanf("%s", &time_str);
    a_time = strptime(&time_str);
    
}
    
    
int main(void) {

    char buff[100];
    char letter;

    

    time_t now = time(0);
    strftime(buff, 100, "%Y-%m-%d %H:%M:%S", localtime(&now));
    printf("Welcome to the alarm clock! It is currently %s\n", buff);

    printf("Please enter \"s\" (schedule), \"l\" (list), \"c\" (cancel), \"x\" (exit)");
    scanf("%c", &letter);

    do {
        if (letter == 'l') {
            list_alarms();
        }

        if (letter == 's') {

        }

        if (letter == 'c') {
            
        }
        
        
    } while(letter != 'x');
    printf("Goodbye!");

return 0;

}



//DETTE ER KODE LISE HAR LOKET MED, FUNKER, MEN FEIL FORMAT
/*time_t currentTime;
// * betyr ...
char *currentTimeInString;

currentTime = time(NULL);

char buff[20];
strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));


if (currentTime == ((time_t)-1))
{
    printf("Failed to get the current time.\n");
}
else
{
    currentTimeInString = ctime(&currentTime);

    if (currentTimeInString == NULL)
    {
        printf("Failed to convert to the current time.\n");
    }
    else 
    {
        printf("\nThe current time is : %s", currentTimeInString);
    }
}*/







    /*
    printf("Welcome to the alarm clock! bla bla It is currently %s", ctime(&t)); 
    printf("Please enter \"c\" (schedule), \"l\" (list), \"c\" (cancel), \"x\" (exit)");
    c = scanf("");

    do {
        if (c == 'l') {
            list_alarms();
        }

        if (c == 's') {

        }

        if (c == 'c') {

        }
        
        
    } while(c != 'x');
    printf("Goodbye!");
    return 0; 
}


int list_alarms() { // list all active alarms 

}

void cancel_alarms( ) { // cancel all alarms

}

int new_alarm() { // initialize new alarm 

}*/
