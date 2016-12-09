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

#define DIM_BUFF 100
#define MAX_LEN 32
#define max(a,b) ((a) > (b) ? (a) : (b))

int conta_file (char *name) {

    DIR *dir;
    struct dirent * dd;
    int count = 0;
    dir = opendir (name);

    while ((dd = readdir(dir)) != NULL) {
        printf("File: %s\n", dd->d_name);
        count++;
    }

    printf("Total count calculated: %d\n", count);
    closedir (dir);
    return count;
}

void gestore(int signo) {
    int stato;
    printf("launching SIGCHLD handler\n");
    wait(&stato);
}

int main(int argc, char **argv) {
    struct sockaddr_in cliaddr, servaddr;
    int  port, listenfd, connfd, udpfd, nready, maxfdp1, len, result;
    const int on = 1;
    fd_set rset;
    char zero=0, buff[DIM_BUFF], request[MAX_LEN];

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
    printf("[%s]: Avvio\n", argv[0]);

    // creazione socket TCP
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)  {
        perror("crazione socket TCP");
        exit(EXIT_FAILURE);
    }
    printf("[%s - TCP]: Creata socket %d\n", argv[0], listenfd);

    memset ((char *)&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        perror("set opzioni socket TCP");
        exit(EXIT_FAILURE);
    }
    printf("[%s - TCP]: Settaggio opzioni ok\n", argv[0]);

    if (bind(listenfd,(struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("bind socket TCP");
        exit(EXIT_FAILURE);
    }
    printf("[%s - TCP]: Bind socket ok\n", argv[0]);

    if (listen(listenfd, 5) < 0)  {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("[%s - TCP]: Listen ok\n", argv[0]);

    // creazione socket UDP
    udpfd=socket(AF_INET, SOCK_DGRAM, 0);
    if (udpfd < 0)  {
        perror("creazione socket UDP");
        exit(EXIT_FAILURE);
    }
    printf("[%s - UDP]: Creata socket %d\n", argv[0], udpfd);

    memset ((char *)&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    if (setsockopt(udpfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)  {
        perror("set opzioni socket UDP");
        exit(EXIT_FAILURE);
    }
    printf("[%s - UDP]: Opzioni settate\n", argv[0]);

    if (bind(udpfd,(struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("bind socket UDP");
        exit(EXIT_FAILURE);
    }
    printf("[%s - UDP]: bind effettuata\n", argv[0]);

    // handler
    signal(SIGCHLD, gestore);

    // pulizia e settaggio maschera
    FD_ZERO(&rset);
    maxfdp1=max(listenfd, udpfd)+1;
    printf("[%s]: settaggio maschera\n", argv[0]);

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
            printf("[%s]: Ricevuta richiesta TCP\n", argv[0]);

            len = sizeof(struct sockaddr_in);
            if((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&len)) < 0)  {
                if (errno == EINTR)
                    continue;
                else {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
            }

            if (fork() == 0)  { 
                close(listenfd);
                printf("[%s - CHILD]: Pid=%i\n", argv[0], getpid());

                // TODO LOGICA GESTIONE RICHIESTE TCP

                printf("[%s - CHILD]: Chiudo connessione e termino\n", argv[0], getpid());
                close(connfd);
                exit(EXIT_SUCCESS);
            }
            close(connfd);
        }

        // richieste UDP
        if (FD_ISSET(udpfd, &rset)) {
            printf("[%s]: Ricevuta richiesta UDP\n");

            // TODO LOGICA GESTIONE RICHISTE UDP

        }
    }
    printf("[%s]: Termino", argv[0]);
    exit(EXIT_FAILURE);
}
