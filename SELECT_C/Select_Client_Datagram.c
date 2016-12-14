// Filippo Serafini
// 0000723678
// Select_Client_Datagram.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    struct hostent *host;
    struct sockaddr_in clientaddr, servaddr;
    int  sd, len, port;
    
    // controllo argomenti
    if (argc != 3) {
        printf("Usage: %s serverAddress serverPort\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        port = atoi(argv[2]);
        if (port < 1024 || port > 65535)  {
            printf("Usage: %s serverAddress serverPort>1024\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    printf("[Datagram_Client]: Avvio\n");

    // inizializzazione indirizzo client
    memset((char *)&clientaddr, 0, sizeof(struct sockaddr_in));
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_addr.s_addr = INADDR_ANY;
    clientaddr.sin_port = 0;

    // inizializzazione indirizzo server
    memset((char *)&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    host = gethostbyname(argv[1]);
    if (host == NULL) {
        printf("%s non trovato in /etc/hosts\n", argv[1]);
        exit(EXIT_FAILURE);
    } else {
        servaddr.sin_addr.s_addr = ((struct in_addr *) (host->h_addr))->s_addr;
        servaddr.sin_port = htons(port);
    }

    // creazione socket
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0) {
        perror("creazione socket");
        exit(EXIT_FAILURE);
    }
    printf("[Datagram_Client]: Creata socket %d\n", sd);
    
    // bind della socket
        if (bind(sd,(struct sockaddr *) &clientaddr, sizeof(clientaddr)) < 0)  {
        perror("bind socket");
        exit(EXIT_FAILURE);
    }
    printf("[Datagram_Client]: Bind effettuato\n");

    // TODO LOGICA DEL PROGRAMMA

    close(sd);
    printf("[Datagram_Client]: Termino\n");
    exit(EXIT_SUCCESS);
}
