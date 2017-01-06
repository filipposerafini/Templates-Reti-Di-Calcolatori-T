// Filippo Serafini
// 0000723678
// Select_Server.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define max(a,b) ((a) > (b) ? (a) : (b))

// TODO DEFINIZIONE STRUTTURA DATI

void gestore(int signo) {
    int stato;
    printf("launching SIGCHLD handler\n");
    wait(&stato);
}

int main(int argc, char **argv) {
    struct sockaddr_in cliaddr, servaddr;
    int  port, listenfd, connfd, udpfd, nready, maxfdp1, len;
    const int on = 1;
    fd_set rset;
    char zero=0;

    // controllo argomenti
    if (argc != 2) {
        printf("Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        port = atoi(argv[1]);
        if (port < 1024 || port > 65535)  {
            printf("Usage: %s port>1024\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    printf("[Select_Server]: Avvio\n");

    // inizializzazione indirizzo server e bind
    memset ((char *)&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    // creazione socket TCP
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("crazione socket TCP");
        exit(EXIT_FAILURE);
    }
    printf("[Select_Server_TCP]: Creata socket %d\n", listenfd);

    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        perror("set opzioni socket TCP");
        exit(EXIT_FAILURE);
    }
    printf("[Select_Server_TCP]: Settaggio opzioni ok\n");

    if (bind(listenfd,(struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("bind socket TCP");
        exit(EXIT_FAILURE);
    }
    printf("[Select_Server_TCP]: Bind socket ok\n");

    if (listen(listenfd, 5) < 0)  {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("[Select_Server_TCP]: Listen ok\n");

    // creazione socket UDP
    udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpfd < 0) {
        perror("creazione socket UDP");
        exit(EXIT_FAILURE);
    }
    printf("[Select_Server_UDP]: Creata socket %d\n", udpfd);

    if (setsockopt(udpfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        perror("set opzioni socket UDP");
        exit(EXIT_FAILURE);
    }
    printf("[Select_Server_UDP]: Settaggio opzioni ok\n");

    if (bind(udpfd,(struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("bind socket UDP");
        exit(EXIT_FAILURE);
    }
    printf("[Select_Server_UDP]: Bind socket ok\n");

    // handler
    signal(SIGCHLD, gestore);

    // pulizia e settaggio maschera
    FD_ZERO(&rset);
    maxfdp1 = max(listenfd, udpfd) + 1;
    printf("[Select_Server]: settaggio maschera\n");

    // inizializzazione struttura dati
    // TODO

    for (;;) {
        FD_SET(listenfd, &rset);
        FD_SET(udpfd, &rset);

        if ((nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0) {
            if (errno == EINTR)
                continue;
            else {
                perror("select");
                exit(EXIT_FAILURE);
            }
        }

        // richieste TCP
        if (FD_ISSET(listenfd, &rset)) {
            printf("[Select_Server]: Ricevuta richiesta TCP\n");

            len = sizeof(struct sockaddr_in);
            if((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&len)) < 0) {
                if (errno == EINTR)
                    continue;
                else {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
            }

            if (fork() == 0) { 
                close(listenfd);
                printf("[Select_Server_CHILD]: Pid=%i\n", getpid());

                // TODO LOGICA GESTIONE RICHIESTE TCP

                printf("[Select_Server_CHILD]: Chiudo connessione e termino\n", getpid());
                close(connfd);
                exit(EXIT_SUCCESS);
            }
            close(connfd);
        }

        // richieste UDP
        if (FD_ISSET(udpfd, &rset)) {
            printf("[Select_Server]: Ricevuta richiesta UDP\n");

            // TODO LOGICA GESTIONE RICHISTE UDP

        }
    }
    printf("[Select_Server]: Termino\n");
    exit(EXIT_FAILURE);
}
