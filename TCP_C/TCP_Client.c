// Filippo Serafini
// 0000723678
// TCP_Client.c

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

int main(int argc, char *argv[]) {
    struct hostent *host;
    struct sockaddr_in servaddr;
    int port, sd, nread;

    // controllo argomenti
    if (argc != 3) {
        printf("Usage: %s serverAddress serverPort\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        port = atoi(argv[2]);
        if (port < 1024 || port > 65535) {
            printf("Usage: %s serverAddress serverPort>1024\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    // inizializzazione indirizzo server
    memset((char *)&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    host = gethostbyname(argv[1]);
    if (host == NULL) {
        printf("%s non trovato in /etc/hosts\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    servaddr.sin_addr.s_addr=((struct in_addr*) (host->h_addr))->s_addr;
    servaddr.sin_port = htons(atoi(argv[2]));

    char richiesta[32];

    printf("\n----------------------------------------\nRICHIESTA, EOF per terminare: ");
    while (gets(richiesta)) {

        // creazione socket stream
        sd = socket(AF_INET, SOCK_STREAM, 0);
        if (sd < 0) {
            perror("apertura socket");
            exit(EXIT_FAILURE);
        }
        printf("[TCP_Client]: Creata la socket %d\n", sd);

        if (connect(sd,(struct sockaddr *) &servaddr, sizeof(struct sockaddr)) < 0) {
            perror("connect");
            exit(EXIT_FAILURE);
        }
        printf("[TCP_Client]: Connect ok\n");

        // TODO LOGICA DEL CLIENT

    printf("\n----------------------------------------\nRICHIESTA, EOF per terminare: ");
    }

    printf("[TCP_Client]: Termino\n");
    exit(EXIT_SUCCESS);
}
