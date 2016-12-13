/* Filippo Serafini 0000723678 */

const DIM = 5;

struct Input {
    char a;
    int b;
};

struct Output {
    char a[DIM];
};

program PROGRAM {
    version PROGRAMVERS{
        int  FUNZIONE_UNO(Input) = 1;
        Output FUNZIONE_DUE(Input) = 2;
    } = 1;
} = 0x20000013;
