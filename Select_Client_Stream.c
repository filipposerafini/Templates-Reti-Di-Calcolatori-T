// Filippo Serafini
// 0000723678
// Select_Client_Stream.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>  

#define DIM_BUFF 100

// dichiarazione eventuali funzioni
bool checkPortVal(char *a)  {
    int aux = 0;
    while( a[aux]!= '\0' )  {
        if((a[aux] < '0') || (a[aux] > '9'))  {
            return false;
        }
        aux++;
    }
    return true;
}

int main(int argc, char *argv[]) {
    int sd, nread, port;
    struct hostent *host;
    struct sockaddr_in servaddr;

    // controllo argomenti
    if (argc != 3) {
        printf("Usage: %s serverAddress serverPort\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // controllo della porta inserita
    if (!checkPortVal(argv[2])) {
        printf("Using: %s serverAddress serverPort\n", argv[0]);
        perror("Second value must be an integer\n");
        exit(EXIT_FAILURE);
    } else {
        port = atoi(argv[2]);
    }

    // inizializzazione indirizzo server
    memset((char *)&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    host = gethostbyname(argv[1]);
    if (host == NULL) {
        printf("%s non trovato in /etc/hosts\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    servaddr.sin_addr.s_addr = ((struct in_addr*) (host->h_addr))->s_addr;
    servaddr.sin_port = htons(atoi(argv[2]));

    printf("[%s]: Avvio", argv[0]);

    // creazione socket
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("apertura socket");
        exit(EXIT_FAILURE);
    }
    printf("[%s]: Creata la socket %d\n", argv[0], sd);

    // bind della socket
    if (connect(sd,(struct sockaddr *) &servaddr, sizeof(struct sockaddr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }
    printf("[%s]: Connect ok\n", argv[0]);

    // TODO LOGICA DEL PROGRAMMA

    close(sd);
    printf("[%s]: Termino\n", argv[0]);
    exit(EXIT_SUCCESS);
}
