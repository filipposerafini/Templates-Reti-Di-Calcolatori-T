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

int main(int argc, char **argv) {
    struct hostent *host;
    struct sockaddr_in clientaddr, servaddr;
    int  sd, len, port;
    
    // controllo del numero di argomenti
    if (argc != 3) {
        printf("Using: %s serverAddress serverPort\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // controllo della porta inserita
    if(!checkPortVal(argv[2]))  {
        printf("Using: %s serverAddress serverPort\n", argv[0]);
        perror("Second value must be an integer\n");
        exit(EXIT_FAILURE);
    } else  {
        port = atoi(argv[2]);
    }

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
    } else  {
        servaddr.sin_addr.s_addr = ((struct in_addr *) (host->h_addr))->s_addr;
        servaddr.sin_port = htons(port);
    }

    printf("[%s]: Avvio", argv[0]);

    // creazione socket
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0)  {
        perror("creazione socket");
        exit(EXIT_FAILURE);
    }
    printf("[%s]: Creata socket %d\n", argv[0], sd);
    
    // bind della socket
        if (bind(sd,(struct sockaddr *) &clientaddr, sizeof(clientaddr)) < 0)  {
        perror("bind socket");
        exit(EXIT_FAILURE);
    }
    printf("[%s]: Bind effettuato alla porta %i\n", argv[0], clientaddr.sin_port);

    // TODO LOGICA DEL PROGRAMMA

    close(sd);
    printf("[%s]: Termino\n", argv[0]);
    exit(EXIT_SUCCESS);
}
