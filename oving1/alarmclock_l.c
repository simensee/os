#include <stdio.h>

#include <stdlib.h>
#include <time.h>

void empty_stdin() 
{
    int c = getchar();

    while (c!= '\n' &&  c != EOF) 
        c = getchar();
}

int list_alarms() { // list all active alarms 
    return 0;
}

void cancel_alarms( ) { // cancel all alarms
}

int new_alarm() { // initialize new alarm 
    struct tm result = {0};
    time_t t, now;
    int diff;
    char buff[19];
    printf("Enter the alarm in format \"YYYY-MM-dd hh:mm:ss\" :");
    scanf(" %[^\n]19s", &buff);
    empty_stdin();
    //puts(buff);
    
    
    strptime(buff, "%Y-%m-%d %H:%M:%S", &result);
    t = mktime(&result);
    time(&now);
    diff = (int) difftime(t, now);
    printf("Alarm is set to: %ld\n", t);
    strftime(buff,sizeof(buff), "%Y-%m-%d %H:%M:%S", &result);
    //printf("Alarm is set to: %d-%d-%d %d:%d:%d\n", result.tm_year,result.tm_mon, result.tm_mday, result.tm_hour, result.tm_min, result.tm_sec);
    return 0;

/*    int validation = 0, day = 0, month = 0, year = 0, hour = 0, min = 0, sec = 0;
vet ikke helt hvorfor jeg gjorde det slik.
    char stringValues[100] = {0};
fgets - blir brukt til å lese strengen eller tid.
string er en karakter array for å lagre input verdier. 
100 er meksimalt antall karakterer å lese
stdin er en peker til en file stream

    printf("Enter the alarm in format \"dd-MM-YY hh:mm:ss\" :")
    fgets(stringValues,100,stdin);
    sscanf(stringValues, "%d-%d-%d %d:%d:%d", &day,&month,&year,&hour,&min,&sec);

    validation = validate_time(day,month,year,hour,min,sec);

    if (validation==0) {
        printf("\nInvalid. Try another time");
    }
    else
    {
        printf("\nThe time is : %d-%d-%d &d:%d:%d", day,month,year,hour,min,sec);
    }
    return 0;*/
}

//int validate_time(int day, int month, int year, int hour, int min, int sec) {
    

/*
int validation = 0;
    if (month>12) validation = 1;

    if (month == 01 || month == 03 || month == 05 || month == 07 || month == 08 || month == 10 || month == 12) {
        if (day>31) validation = 1;
    }
    if (month == 02) {
        if (day > 28) validation = 1;
    }
    if (month == 04 || month == 06 || month == 09 || month == 11)  {
        if (day > 30) validation = 1;
    }

}*/

// Formatering av current date
int main(void)
{
    /*char buff[100];
    time_t now = time(0);
    strftime(buff, 100, "%Y-%m-%d %H:%M:%S", localtime(&now));
    printf("Welcome to the alarm clock! It is currently %s\n", buff);
    return 0;*/

    /*struct alarm {
            struct tm time;
            int pid;
    }*/
    // DETTE ER KODEN VI SKREV FØR SIMEN DRO
    char input;
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
    printf("Goodbye!");
    return 0; 
}