// Filippo Serafini
// 0000723678
// RPC_Client.c

#include <stdio.h>
#include <rpc/rpc.h>
#include "RPC_xFile.h"

void main (int argc, char *argv[]) {
    char *host;
    CLIENT *cl;

    // TODO VARIABILI PER LA LOGICA DEL PROGRAMMA
    char command[32];

    // controllo argomenti
    if (argc != 2)	{
        printf("Usage: %s serverAddress\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    host = argv[1];

    // TODO cl = clnt_create(host, PROGRAM, PROGRAMVERS, "udp");
    if (cl == NULL)	{
        clnt_pcreateerror(host);
        exit(EXIT_FAILURE);
    }

    printf("\t----------\t----------\nCMD - FUNZIONE, EOF per terminare: ");
    while (gets(command)) {

        if (strcmp(command, "CMD1") == 0) {

            // TODO LOGICA CLIENT

            // Invocazione remota
            // ris = funzione_uno(&input, cl);

            if (ris == NULL)	{
                clnt_perror(cl, host);
                exit(EXIT_FAILURE);

            } else if (*ris < 0) {
                // Gestione Problemi

            } else {
                // Gestione Successo
            }
        } else {
            printf("Errore!\n");
        }

        printf("\t----------\t----------\nCMD - FUNZIONE, EOF per terminare: ");
    }

    clnt_destroy(cl);
    exit(EXIT_SUCCESS);
}
