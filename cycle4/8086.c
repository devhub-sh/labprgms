#include "ctype.h"
#include "stdio.h"
#include "string.h"

char vars[100][20];
int nv = 0;

void addvar(const char* v) {
    if (isdigit((unsigned char)v[0]) || v[0] == '-')
        return;
    for (int i = 0; i < nv; i++)
        if (!strcmp(vars[i], v))
            return;
    strcpy(vars[nv++], v);
}

int main(void) {
    FILE* f = fopen("tac.txt", "r");
    FILE* o = fopen("out.asm", "w");
    char op[8], a[12], b[12], r[12];
    char ops[100][8], A[100][12], B[100][12], R[100][12];
    int n = 0;
    if (!f) {
        printf("tac.txt not found\n");
        return 1;
    }

    while (fscanf(f, "%7s %11s %11s %11s", op, a, b, r) == 4) {
        strcpy(ops[n], op);
        strcpy(A[n], a);
        strcpy(B[n], b);
        strcpy(R[n], r);
        addvar(a);
        addvar(b);
        addvar(r);
        n++;
    }
    fclose(f);

    FILE* out[2] = {stdout, o};
    for (int k = 0; k < 2; k++) {
        FILE* w = out[k];
        fprintf(w, ".MODEL SMALL\n.STACK 100H\n.DATA\n");
        for (int i = 0; i < n; i++) {
            fprintf(w, ".CODE\nMAIN PROC\n      MOV AX, @DATA\n     MOV DS, AX\n");
        }
        for (int i = 0; i < n; i++) {
            switch (ops[i][0]) {
                case '=':
                    fprintf(w, "        MOV AX, %s\n    MOV %s, AX\n", A[i], R[i]);
                    break;
                case '+':
                    fprintf(w, "        MOV AX, %s\n        ADD AX, %s\n        MOV %s, AX\n", A[i], B[i], R[i]);
                    break;
                case '-':
                    fprintf(w, "        MOV AX, %s\n        SUB AX, %s\n        MOV %s, AX\n", A[i], B[i], R[i]);
                    break;
                case '*':
                    fprintf(w, "        MOV AX, %s\n        MOV BX, %s\n        MUL BX\n        MOV %s, AX\n", A[i], B[i], R[i]);
                    break;
                case '/':
                    fprintf(w, "        MOV AX, %s\n        MOV BX, %s\n        DIV BX\n        MOV %s, AX\n", A[i], B[i], R[i]);
                    break;
            }
        }
        fprintf(w, "\n      MOV AH, 4CH\n      INT 21H\nMAIN ENDP\nEND MAIN\n");
        if (k == 0)
            printf("\n--- saved to out.asm ---\n");
    }
    fclose(o);
    return 0;
}
