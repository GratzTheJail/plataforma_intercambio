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

AlunoComp* acessaAluno(char* nomeUsu);
bool loginAluno(char* nomeUsu, char* senha);
int criaAluno(AlunoComp novoAluno);
AlunoComp* modificaAluno(char* nomeUsu, AlunoComp novoAluno);
int deletaAluno(char* nomeUsu);

#endif
