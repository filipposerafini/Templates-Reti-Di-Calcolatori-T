// Filippo Serafini
// 0000723678
// TCP_Server.c

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

#define BUFF_SIZE 1024

void gestore(int signo) {
    int stato;
    printf("Esecuzione gestore di SIGCHLD\n");
    wait(&stato);
}

int main(int argc, char **argv) {
    struct sockaddr_in cliaddr, servaddr;
    struct hostent *host;
    const int on = 1;
    int  listenfd, connfd;
    int port, len;

    // TODO VARIABILI PER LA LOGICA DEL PROGRAMMA
    char buffer[BUFF_SIZE];

    // controllo argomenti
    if(argc != 2)	{
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

    // creazione socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("creazione socket ");
        exit(EXIT_FAILURE);
    }
    printf("[%s]: Creata socket %d\n", argv[0], listenfd);

    memset ((char *)&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        perror("set opzioni socket");
        exit(EXIT_FAILURE);
    }
    printf("[%s]: Settaggio opzioni ok\n", argv[0]);

    if (bind(listenfd,(struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("bind socket d'ascolto");
        exit(EXIT_FAILURE);
    }
    printf("[%s]: Bind socket ok\n", argv[0]);

    if (listen(listenfd, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("[%s]: Listen ok\n", argv[0]);

    // handler
    signal(SIGCHLD, gestore);

    for(;;) {
        printf("[%s]: In attesa di richieste\n", argv[0]);
        len=sizeof(cliaddr);
        if((connfd=accept(listenfd,(struct sockaddr *)&cliaddr,&len)) < 0)  {
            if (errno == EINTR)
                continue;
            else {
                perror("accept");
                exit(EXIT_FAILURE);
            }
        }
        if (fork() == 0)  {
            close(listenfd);
            printf("[%s - CHILD]: pid = %i\n", argv[0], getpid());

            //TODO LOGICA SERVER

            printf("[%s - CHILD]: Chiudo connessione e termino\n", argv[0], getpid());
            close(connfd);
            exit(EXIT_SUCCESS);
        }
        close(connfd);
    }
    printf("[%s]: Termino\n", argv[0]);
    exit(EXIT_SUCCESS);
}
