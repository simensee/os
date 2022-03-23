#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "bbuffer.c"


#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

#include <netinet/in.h>

#define MAXMEM (4096*1024)


char buffer[MAXMEM], body[MAXMEM], message[MAXMEM];
char* www_path;
int portnumber;
int n_threads;
int bbuffer;
int server_socket;

struct BNDBUF *bb;
/*
Server-siden av programmet. 

Mottar GET-requests fra klient, og sender tilbake ønsket fil. 

Programmet startes ved å kompilere, så kjøre "./mtwwwd.c *root-path* *port* "

Root-path er roten for der serveren skal lete etter filer. Denne legges altså sammen med pathen fra klienten, 
og gir hele absolutte pathen til filen. 

Port er den spesifiserte porten serveren hører etter requester på. 

*/

void err_n_exit(const char * message) {
    perror(message);
    exit(1);
}

char * split_string(char str) {
    char * token = strtok(&str, " ");
    return token;
}


void *handle_request(void *bbuff) {
    int client_socket;
    char *string, addr_buff[256], http_header[2048], html_buffer[256];
    FILE *html_data;
    
    while (1) {
        printf("Getting from bbuffer \n");
        printf("Thread %li\n", (long) pthread_self());
        
        
        client_socket = bb_get(bb);
        printf("got fd: %d \n", client_socket);
        if (client_socket < 0) {
            err_n_exit("Failed to connect to client socket");
        }
        
        bzero(buffer, sizeof(buffer));
        // read data from client_socket
        if(recv(client_socket, buffer, sizeof(buffer), 0) == -1) //trying to recive message from client
        {
            err_n_exit("Failed to recive request from client");
        }
        char * request_type = strtok(buffer, " "); // her blir GET lagt, evt andre typer hvis det skal brukes
        printf("Request type: %s\n", request_type);
        char * path = strtok(NULL, " "); // selve pathen i requesten blir lagt inn her 
        printf("Request path: %s\n", path);
        bzero(addr_buff, sizeof(addr_buff));
        strcat(www_path, path); // setter sammen pathene, slik at vi får en absolutt path til filene vi leter etter 

        printf("\nFull path: %s\n", path);
        if ((html_data = fopen(www_path, "rb"))==NULL) {
            strcpy(html_buffer, "<html><body><h1>404 Page Not Found</h1></body></html>\n");
            strcpy(http_header, "HTTP/1.1 404 Not Found\r\n\r\n"); // 404 Not Found
        } 
        else {
            fseek(html_data, 0, SEEK_END);
            long fsize = ftell(html_data);
            fseek(html_data, 0, SEEK_SET);

            string = malloc(fsize + 1);
            fread(string, fsize, 1, html_data);
            fclose(html_data);
            
            string[fsize] = 0;
            strcpy(http_header, "HTTP/1.1 200 OK\r\n\n"); // dersom den finnes
            printf("%s\r\n", string);   
        }


        strcat(http_header, string); // setter response_data sammen med headeren til responsen tilbake til klienten 

        // sender responsen
        if (send(client_socket, http_header, sizeof(http_header), 0) < 0) {
            err_n_exit("Failed to send to socket!");
        } 
        close(client_socket);
        
    }
}

/*int init_server_socket(int port) {
    //int server_socket, addr_len;
    server_socket = socket(AF_INET, SOCK_STREAM, 0); // lager socketen som skal brukes 
    if (server_socket < 0) {
        err_n_exit("Failed to connect to client socket!");
    }

    // spesifiserer addressen og portnummer socketen skal bruke
    struct sockaddr_in server_address;
    struct sockaddr_in port_in;
    //memset(&server_address, 0, sizeof(server_address)); // initierer minnet til adressen (?) 
    //bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET; // spesifiseres at det er en internett-adresse 
    server_address.sin_port = htons(port); //MERK: her brukes portnummeret som ble lagt ved som argument til serveren. 
    server_address.sin_addr.s_addr = INADDR_ANY; //hører etter alle adresser 
    printf("heii");

    printf("\nCreated socket!\n"); // print for å s jekke programflyt  
    printf("heii");

    // binder server-socketen sammen med adressene 
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)  {
        err_n_exit("Binding error");
    }
    printf("heii");


}*/


int main(int argc, char* argv[]) {
    
    int server_socket, addr_len, client_socket;
    //char buffer[512];
    
    
    if (argc < 4) {
        perror("\n[Please provide 4 arguments]: mtwwwd www-path port #threads #bufferslots\n");
        exit(0);
    }
    // setter argumentene inn i variabler
    www_path = argv[1];
    portnumber = atoi(argv[2]);
    n_threads = atoi(argv[3]);
    bbuffer = atoi(argv[4]);

    // Initialize the semaphore
    pthread_t threads_arr[n_threads];
    bb = bb_init(bbuffer);
    int temp[n_threads];
    printf("Port: %d\n", portnumber);

    printf("Threads: %d\n", n_threads);

    printf("Buffer size: %d\n", bbuffer);

    
    
    //server_socket = init_server_socket(portnumber);

    //start
    server_socket = socket(PF_INET, SOCK_STREAM, 0); // lager socketen som skal brukes 
    if (server_socket < 0) {
        err_n_exit("Failed to connect to client socket!");
    }
    struct sockaddr_in server_address;
    bzero((char *) &server_address, sizeof(server_address));
    // spesifiserer addressen og portnummer socketen skal bruke
    
    //struct sockaddr_in port_in;
    memset((char *)&server_address, 0, sizeof(server_address)); // initierer minnet til adressen (?) 
    
    server_address.sin_family = AF_INET; // spesifiseres at det er en internett-adresse 
    server_address.sin_port = htons(portnumber); //MERK: her brukes portnummeret som ble lagt ved som argument til serveren. 
    server_address.sin_addr.s_addr = INADDR_ANY; //hører etter alle adresser 
    

    printf("\nCreated socket!\n"); // print for å sjekke programflyt  

    // binder server-socketen sammen med adressene 
    int n = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    printf("%d", n);
    /*if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)  {
        err_n_exit("Binding error");
    }*/
    listen(server_socket, 5);
    // slutt
    
    // hører etter requester, her må det nok implementeres en while-løkke for å kunne motta nye requester når de er ferdige
    
    printf("Creating threads\n");
    for(int i = 0; i<n_threads;i++) {
        temp[i] = i;
        printf("Creating thread %d \n", i);
        int result = pthread_create(&threads_arr[i], NULL, &handle_request, &temp[i]);
        printf("Finished creating thread %d \n", i);
    }
    
    socklen_t cli_len;
    struct sockaddr client_address;
    int cccc = 0;
    while (1) {
        printf("Ready to take requests on port: %d\n", portnumber);
        // aksepterer innkommende socketer 
        // [Kommentar fra Elizabeth] Spesifisert i oppgaven er ved bruk av accept(2) skjønte ikke helt dette :(
        cli_len = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr*) &client_address, &cli_len);
        
        printf("Adding socketfd to bbuffer %d\n", client_socket);
        bb_add(bb, client_socket);
        //bzero(buffer,sizeof(buffer));
        cccc+=1;
        printf("%d\n",cccc);
        printf("Added socketfd to bbuffer \n");

        
        //printf("Client socket received! \nContent of request: [%s]", buffer); // programflyt 

        // splitter opp mottakende request i forskjellige ting 
        
        // Printe ut for å sjekke om det er riktig, dette kan nok fjernes før levering 
        
       // initierer en fil 

        //strcat(www_path, path); // setter sammen pathene, slik at vi får en absolutt path til filene vi leter etter 
        
        
        
    

        //char response_data[1024];
        //fgets(response_data, 1024, html_data); // leser filens innhold inn i response_data 
        
        //close(client_socket);
    }
    //close(client_socket); denne må nok brukes etterhvert, men fikk det ikke til å funke
    return 0;
    
    /*pthread_t thread1;

    pthread_create( &thread1, NULL, &functionCount1, NULL);
    pthread_join( thread1, NULL);*/

    //exit(0);
}


    




//}
// Shaky oppgave b)

/*static pthread_mutex_t func_mutex = PTHREAD_MUTEX_INITIALIZER;
int counter=0;

void *func() {

    pthread_mutex_lock(&func_mutex);
    counter++
    pthread_mutex_unlock(&func_mutex);
}*/
/*
pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER;

void *functionCount1();
int  count = 0;
#define COUNT_DONE  10 // hva gjør dette? 
#define COUNT_HALT1  3
#define COUNT_HALT2  6



void *functionCount1()
{
   for(;;)
   {
      pthread_mutex_lock( &condition_mutex );
      while( count >= COUNT_HALT1 && count <= COUNT_HALT2 )
      {
         pthread_cond_wait( &condition_cond, &condition_mutex );
      }
      pthread_mutex_unlock( &condition_mutex );

      pthread_mutex_lock( &count_mutex );
      count++;
      printf("Counter value functionCount1: %d\n",count);
      pthread_mutex_unlock( &count_mutex );

      if(count >= COUNT_DONE) return(NULL);
    }
}*/