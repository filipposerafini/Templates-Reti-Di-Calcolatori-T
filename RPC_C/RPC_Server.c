// Filippo Serafini
// 0000723678
// RPC_Server.c

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <rpc/rpc.h>
#include "RPC_xFile.h"

static int inizializzato = 0;

void inizializza() {
    if (inizializzato == 1)
        return;

    // TODO INIZIALIZZAZIONE STRUTTURA DATI

    inizializzato = 1;
    printf("Terminata inizializzazione struttura dati!\n");
}

int * funzione_uno_1_svc(int *input, struct svc_req *rqstp) {
    static int result;
    result = -1;
    inizializza();

    // TODO LOGICA DELLA FUNZIONE

    return (&result);
}
