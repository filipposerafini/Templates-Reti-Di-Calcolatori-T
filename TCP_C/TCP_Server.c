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

    // controllo argomenti
    if (argc != 2)	{
        printf("Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        port = atoi(argv[1]);
        if (port < 1024 || port > 65535)  {
            printf("Usage: %s port>1024\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    printf("[TCP_Server]: Avvio\n");

    // creazione socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("creazione socket");
        exit(EXIT_FAILURE);
    }
    printf("[TCP_Server]: Creata socket %d\n", listenfd);

    memset ((char *)&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        perror("set opzioni socket");
        exit(EXIT_FAILURE);
    }
    printf("[TCP_Server]: Settaggio opzioni ok\n");

    if (bind(listenfd,(struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("bind socket");
        exit(EXIT_FAILURE);
    }
    printf("[TCP_Server]: Bind socket ok\n");

    if (listen(listenfd, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("[TCP_Server]: Listen ok\n");

    // handler
    signal(SIGCHLD, gestore);

    for(;;) {
        printf("[TCP_Server]: In attesa di richieste\n");
        len=sizeof(cliaddr);
        if ((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&len)) < 0)  {
            if (errno == EINTR)
                continue;
            else {
                perror("accept");
                exit(EXIT_FAILURE);
            }
        }
        if (fork() == 0)  {
            close(listenfd);
            printf("[TCP_Server_CHILD]: Pid = %i\n", getpid());

            //TODO LOGICA SERVER

            printf("[TCP_Server_CHILD]: Chiudo connessione e termino\n", getpid());
            close(connfd);
            exit(EXIT_SUCCESS);
        }
        close(connfd);
    }
    printf("[TCP_Server]: Termino\n");
    exit(EXIT_SUCCESS);
}
