#ifndef ALUNOCOMP_H
#define ALUNOCOMP_H

// Estrutura com dados do aluno que podem ser usados externamente 

typedef struct alunoCompartilhado AlunoComp;

struct alunoCompartilhado {
    char nomeUsu[30];
    char senha[20];
};

#endif
