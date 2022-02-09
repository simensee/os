#include <stdio.h>
#include <time.h>
int main() {
    char c;
    time_t current_time;
    struct alarm {
        time_t time;
        int pid;
    }
    
    printf("Welcome to the alarm clock! It is currently %d. \n", current_time);
    printf("Please enter \"c\" (schedule), \"l\" (list), \"c\" (cancel), \"x\" (exit)");
    c = scanf("");
    do {
        if (c == 'l') {
            list_alarms();
        }
        if (c == 's') {

        }
        {
            
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
