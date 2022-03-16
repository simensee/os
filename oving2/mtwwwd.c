#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sem.h>


#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

#include <netinet/in.h>
/*
Server-siden av programmet. 

Mottar GET-requests fra klient, og sender tilbake ønsket fil. 

Programmet startes ved å kompilere, så kjøre "./mtwwwd.c *root-path* *port* "

Root-path er roten for der serveren skal lete etter filer. Denne legges altså sammen med pathen fra klienten, 
og gir hele absolutte pathen til filen. 

Port er den spesifiserte porten serveren hører etter requester på. 

*/



char * split_string(char str) {
    char * token = strtok(&str, " ");
    return token;
}




int main(int argc, char* argv[]) {
    
    
    int server_socket, client_socket, addr_len, portnumber;
    char *www_path, buffer[512];
    
    // setter argumentene inn i variabler
    www_path = argv[1];
    portnumber = atoi(argv[2]);
    printf("\n Port: %d\n", portnumber); // printer ut porten, kun for å sjekke at dette funker. Kan fjernes når vi skal levere
    printf("\nPrepairing to create socket\n"); // printer for å sjekke programflyt, kan slettes før levering 
    
    server_socket = socket(AF_INET, SOCK_STREAM, 0); // lager socketen som skal brukes 


    // spesifiserer addressen og portnummer socketen skal bruke
    struct sockaddr_in server_address;
    struct sockaddr_in port_in;
    memset(&server_address, 0, sizeof(server_address)); // initierer minnet til adressen (?) 
    server_address.sin_family = AF_INET; // spesifiseres at det er en internett-adresse 
    server_address.sin_port = htons(portnumber); //MERK: her brukes portnummeret som ble lagt ved som argument til serveren. 
    server_address.sin_addr.s_addr = INADDR_ANY; //hører etter alle adresser 
    printf("\nCreated socket!\n"); // print for å sjekke programflyt 

    // binder server-socketen sammen med adressene 
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    
    // hører etter requester, her må det nok implementeres en while-løkke for å kunne motta nye requester når de er ferdige
    listen(server_socket, 100);
    
    // aksepterer innkommende socketer 
    // [Kommentar fra Elizabeth] Spesifisert i oppgaven er ved bruk av accept(2) skjønte ikke helt dette :(
    
    client_socket = accept(server_socket, (struct sockaddr*) &port_in, (socklen_t*) &addr_len);
    printf("Accepting connection...\n\n");
    if(recv(client_socket, buffer, sizeof(buffer), 0) == -1) //trying to recive message from client
    {
        perror("Failed to recive request from client");
        exit(1);
    }
    


    printf("Client socket received! \nContent of request: [%s]", buffer); // programflyt 

    // splitter opp mottakende request i forskjellige ting 
    char * request_type = strtok(buffer, " "); // her blir GET lagt, evt andre typer hvis det skal brukes
    char * path = strtok(NULL, " "); // selve pathen i requesten blir lagt inn her 
    // Printe ut for å sjekke om det er riktig, dette kan nok fjernes før levering 
    printf( " %s\n", request_type); 
    printf( " %s\n", path);
    FILE *html_data; // initierer en fil 
    strcat(www_path, path); // setter sammen pathene, slik at vi får en absolutt path til filene vi leter etter 
    
    char http_header[2048];
    if ((html_data = fopen(www_path, "r"))==NULL) { // prøver å åpne file for å lese 
        strcpy(http_header, "HTTP/1.1 404 Not Found\r\n\r\n"); // dersom den ikke finnes 
    }
    else {
        strcpy(http_header, "HTTP/1.1 200 OK\r\n\n"); // dersom den finnes
    }
   

    char response_data[1024];
    fgets(response_data, 1024, html_data); // leser filens innhold inn i response_data 
    strcat(http_header, response_data); // setter response_data sammen med headeren til responsen tilbake til klienten 
    send(client_socket, http_header, sizeof(http_header), 0); // sender responsen 
    //close(client_socket); denne må nok brukes etterhvert, men fikk det ikke til å funke
    return 0;
    
    pthread_t thread1;

    pthread_create( &thread1, NULL, &functionCount1, NULL);
    pthread_join( thread1, NULL);

    exit(0);
}


    
}
// Shaky oppgave b)

/*static pthread_mutex_t func_mutex = PTHREAD_MUTEX_INITIALIZER;
int counter=0;

void *func() {

    pthread_mutex_lock(&func_mutex);
    counter++
    pthread_mutex_unlock(&func_mutex);
}*/

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
}