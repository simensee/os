#include <stdio.h>

#include <stdlib.h>
#include <time.h>

int main() {
    char c;
    time_t t = time(NULL);
    struct tm current_time = *localtime(&t);
    int c_time = mktime(&current_time);

    struct alarm {
        struct tm time;
        int pid;
    }
    
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

}
