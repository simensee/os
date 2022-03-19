#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <arpa/inet.h>

#include <netinet/in.h>

/*
Klient for å requeste en fil fra serveren. 

Startes med path fra root-folder spesifisert hos serveren som argument ved kjøring. 

Request på formen: 

GET *path* HTTP 1/1 \r\n\r\n

*/



int main(int argc, char* argv[]) {

    char *path, *buff[4096*1024];
    if (argc < 1) { // Sjekker om man har spesifisert et argument 
        printf("Too few arguments\n");
        exit(1); 
    }
    path = argv[1]; // Setter argumentet (pathen) inn i variabelen. 
    
    int client_socket; 
    client_socket = socket(AF_INET, SOCK_STREAM, 0); // Lager klient-socketen 

    // Setter addresse til localhost og port til 8001, samt spesifiserer at det er en internett-adresse. 
    struct sockaddr_in remote_address;
    remote_address.sin_family = AF_INET;
    remote_address.sin_port = htons(8002);
    remote_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    //inet_aton(address, (struct in_addr *)&remote_address.sin_addr.s_addr);

    //Kobler sammen socketen med adress-structen spesifisert over 
    connect(client_socket, (struct sockaddr *) &remote_address, sizeof(remote_address));


        
    // Initierer HTTP-requesten inn i buff, med path integrert i stringen 
    snprintf((char*)buff, sizeof(buff), "GET %s HTTP/1.1 \r\n\r\n", path);
    char response[4096*1024];

    // Sender requesten til socketen 
    send(client_socket, buff, sizeof(buff), 0);
    //Mottar svarer fra serveren gjennom socketen og printer ut 
    recv(client_socket, &response, sizeof(response), 0);
    printf("Response from server: %s\n", response);
    // Kommenterte ut close, da denne skapte problemer med kjøring i chrome. 
    //close(client_socket); 

    return 0;
}