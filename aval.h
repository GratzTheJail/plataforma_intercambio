// Modulo avaliacoes
#ifndef LIST
#define LIST
#include "list/list.h"
#endif
#ifndef AVALCOMP
#define AVALCOMP
#include "avalcomp.h"
#endif

AvalComp* acessaAvaliacao(int idAval);
// id é calculado (independe do parâmetro)
int criaAvaliacao(AvalComp novaAval);
// apenas texto será modificado
int modificaAvaliacao(int idAval, AvalComp novaAval);
int deletaAvaliacao(int idAval);

Node* acessaAvaliacoesInst(int idInst, int* tam);
Node* acessaAvaliacoesAluno(char* nomeUsu, int* tam);