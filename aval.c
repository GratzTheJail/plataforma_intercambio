// Modulo avaliacoes
#include "aval.h"
#ifndef LIST
#define LIST
#include "list/list.h"
#endif
#include <stdio.h>
#include <stdlib.h>

#define ARQUIVO "arquivos/avaliacoes.txt"

Node* avaliacoes = NULL;

void lst2arq(Node* avals){
    FILE* arq = fopen(ARQUIVO, "w");
    for(; avals != NULL; avals = avals->next){
        Aval* aval = (Aval*)avals->obj;
        fprintf(arq, "%d;", aval->id);
        fprintf(arq, "%s;", aval->texto);
        fprintf(arq, "%s;", aval->autor);
        fprintf(arq, "%d;\n", aval->idInst);
    }
    fclose(arq);
}

Node* arq2lst(){
    FILE* arq = fopen(ARQUIVO, "r");
    Node* lst = NULL;
    
    for(Aval a; !feof(arq) && 
        fscanf(arq, " %d;%399[^;];%25[^;];%d;", &(a.id), a.texto, a.autor, &(a.idInst)) == 4;){
        lst = postInsert(lst, a.id);
        Node* novoNode = findNode(lst, a.id);
        if(novoNode != NULL){
            Aval* novaAval = (Aval*)malloc(sizeof(Aval));
            *novaAval = a;
            novoNode->obj = (void*)novaAval;
        }
    }

    fclose(arq);
    return lst;
}

// id é calculado (independe do parâmetro)
// uma avaliação NÃO PODE ter no seu campo texto nenhum caractere ';'
// TODO: perguntar se podemos mudar algo do q botamos originalmente pq foi uma ideia ruim
Aval* criaAvaliacao(Aval novaAval){
// TODO: criar check se há caractere ';' no campo de texto
    Node* lst = arq2lst();
    int id;
    
    if(lst == NULL)
        id = 0;
    else
        id = lst->n + 1;

    lst = preInsert(lst, id);
    
    Aval* av = (Aval*)malloc(sizeof(Aval));
    *av = novaAval;
    av->id = id;

    lst->obj = (void*)av;

    lst2arq(lst);

    lst = deleteList(lst);

    return av; // TODO: mudar caso o prof deixe mudar a ideia original, retornar se foi possivel ou n inserir por int
}

Aval* acessaAvaliacao(int idAval);
// apenas texto será modificado
Aval* modificaAvaliacao(int idAval, Aval novaAval);
int deletaAvaliacao(int idAval);

Aval** acessaAvaliacoesInst(int idInst, int* tam);
Aval** acessaAvaliacoesAluno(char* nomeUsu, int* tam);