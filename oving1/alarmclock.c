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


    
    
    int main(void) {
        char buff[100];
        time_t now = time(0);
        strftime(buff, 100, "%Y-%m-%d %H:%M:%S", localtime(&now));
        printf("Welcome to the alarm clock! It is currently %s\n", buff);
        return 0;

    

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

    return 0;
    
}





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
