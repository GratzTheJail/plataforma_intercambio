/*
 * Guilherme Melo Gratz 			2211068
 * João Miguel Rodrigues Montenegro da Franca	2411289
 * Lorena Silveira dos Santos 			2312667
*/
// Modulo Aluno
#ifndef ALUNO_H
#define ALUNO_H

#include <stdbool.h>
#include "alunoComp.h"

typedef struct aluno {
    char nomeUsu[30];
    char senha[20];
    struct aluno* prox;
} Aluno;

void inicializaAlunos();     // Lê dados do arquivo no início
void finalizaAlunos();       // Salva dados no arquivo no fim

AlunoComp* acessaAluno(char* nomeUsu);
bool loginAluno(char* nomeUsu, char* senha);
int criaAluno(AlunoComp novoAluno);
AlunoComp* modificaAluno(char* nomeUsu, AlunoComp novoAluno);
int deletaAluno(char* nomeUsu);

#endif
