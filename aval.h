// Modulo avaliacoes
#ifndef LIST
#define LIST
#include "list/list.h"
#endif

typedef struct avaliacoes Aval;
struct avaliacoes{
    int id;
    char texto[400];
    char autor[25];
    int idInst;
};

Aval* acessaAvaliacao(int idAval);
// id é calculado (independe do parâmetro)
Aval* criaAvaliacao(Aval novaAval);
// apenas texto será modificado
Aval* modificaAvaliacao(int idAval, Aval novaAval);
int deletaAvaliacao(int idAval);

Aval** acessaAvaliacoesInst(int idInst, int* tam);
Aval** acessaAvaliacoesAluno(char* nomeUsu, int* tam);

void lst2arq(Node* avals);
Node* arq2lst();