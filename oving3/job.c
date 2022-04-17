#include "Job.h"


Job *first_job = NULL;


void add_to_list(Job *job) {
    
    if (!first_job) {
        first_job = job;
    }


    Job *j = first_job;

    while(j->next) {
        j = j->next;
    }
    j->next = job;
    job->prev = j;

}




Job *remove_from_list(Job *job) {
    Job* j;
    for (j = first_job; j; j = j->next) {
        if(j->pid == job->pid) {
            if (!j->prev && !j->next) {
                first_job = NULL;
            }
            else {
                
            }
        }
    }
}