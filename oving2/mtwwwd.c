#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "bbuffer.h"
#include "sem.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <unistd.h> 

#include <netinet/in.h>

#define MAXMEM (4096*1024)

char buffer[MAXMEM], body[MAXMEM], msg[MAXMEM], total_path[512];

char* www_path;
int portnumber;
int n_threads;
int bbuffer;
int server_socket;

struct BNDBUF *bb;

// Function to print and exit after errors
void err_n_exit(const char * message) {
    perror(message);
    exit(1);
}



// Function for handling request, executed by threads 
void *handle_request() {
    int client_socket;
    
    char *string, http_header[2048], html_buffer[256], path[256];
    FILE *html_data;
    

    while (1) {
        
        // Printing thread
        printf("Thread %li\n", (long) pthread_self());
        
        // Getting socket from bbuffer
        client_socket = bb_get(bb);
        printf("got fd: %d \n", client_socket);

        // Check sockets 
        if (client_socket < 0) {
            err_n_exit("Failed to connect to client socket");
        }
        
        // Erasing data from buffer
        bzero(buffer, sizeof(buffer));
       
        // Reading from socket
        if(read(client_socket, buffer, sizeof(buffer)-1) < 0) 
        {
            err_n_exit("Failed to read request from client socket");
        }

        // Fetching request type and path from buffer
        char * request_type;
        char * path;
        request_type = strtok(buffer, " "); 
        printf("Request type: %s\n", request_type);
        path = strtok(NULL, " "); 
        printf("Request path: %s\n", path);
        
        // Erasing memory from total path
        bzero(total_path, sizeof(total_path));

        // Concatenate total path and root path, as well as request-path
        strcat(total_path, www_path); 
        strcat(total_path, path); 



        printf("\nFull path: %s\n", total_path);

        // check if requested file is found, adds 404 not found if not
        if ((html_data = fopen(total_path, "rb"))==NULL) {
            strcpy(body, "<html><body><h1>404 Page Not Found</h1></body></html>\n");
            if(snprintf(msg, sizeof(msg),"HTTP/1.1 404 Not Found\r\n\n %s", body) < 0) {
                err_n_exit("Error");
            }
            
            
        } 
        // gets content from requested file and adds into variable msg
        else {
            fseek(html_data, 0, SEEK_END);
            long fsize = ftell(html_data);
            fseek(html_data, 0, SEEK_SET);

            string = malloc(fsize + 1);
            fread(string, fsize, 1, html_data);
            fclose(html_data);
            
            string[fsize] = 0;
            strcpy(body, string);
            if(snprintf(msg, sizeof(msg),"HTTP/1.1 200 OK\r\n\n %s", body) < 0) {
                err_n_exit("Error");
            }
            
        }


        

        // writes response back to socket 
        if (write(client_socket, msg, sizeof(msg)) < 0)
        {
            err_n_exit("Failed to send to socket!");
        } 

        // closes socket 
        close(client_socket);
        
    }
}


int main(int argc, char* argv[]) {
    
    int server_socket, addr_len, client_socket;
    
    // chec
    if (argc < 4) {
        err_n_exit("[Please provide 4 arguments]: mtwwwd www-path port #threads #bufferslots");
        
    }
    
    // fills out global variables
    www_path = argv[1];
    portnumber = atoi(argv[2]);
    n_threads = atoi(argv[3]);
    bbuffer = atoi(argv[4]);

    // Initialize the threads and bbuffer
    pthread_t threads_arr[n_threads];
    bb = bb_init(bbuffer);
    int temp[n_threads];


    printf("Port: %d\n", portnumber);

    printf("Threads: %d\n", n_threads);

    printf("Buffer size: %d\n", bbuffer);

    
    
    
    
    // creates server socket
    server_socket = socket(PF_INET, SOCK_STREAM, 0); // lager socketen som skal brukes 
    if (server_socket < 0) {
        err_n_exit("Failed to connect to client socket!");
    }

    // initializes server address
    struct sockaddr_in server_address;

    memset((char *)&server_address, 0, sizeof(server_address)); 
    
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(portnumber); 
    server_address.sin_addr.s_addr = INADDR_ANY; 
    

    
    
    // binds server socket with address
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0 ){
        err_n_exit("Failed to bind socket");
    }
    
    // listens after requests from client sockets
    listen(server_socket, 5);
   
    
    
    
    // creates threads
    for(int i = 0; i<n_threads;i++) {
        temp[i] = i;
        printf("Creating thread %d \n", i);
        // creates threads which executes function handle_request()
        int result = pthread_create(&threads_arr[i], NULL, &handle_request, &temp[i]);
        printf("Finished creating thread %d \n", i);
    }
    
    // address and length of client socket
    socklen_t cli_len;
    struct sockaddr client_address;
    
    while (1) {
        printf("Ready to take requests on port: %d\n", portnumber);
        
    
        cli_len = sizeof(client_address);
        // accepts client sockets
        client_socket = accept(server_socket, (struct sockaddr*) &client_address, &cli_len);
        if (client_socket < 0) {
            err_n_exit("Error with accepting");
        }
        
        printf("Adding socketfd to bbuffer %d\n", client_socket);

        // adds socket to buffer
        bb_add(bb, client_socket);
        printf("Added socketfd to bbuffer \n");
    }   
    
    return 0;
}


    



