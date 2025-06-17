// Modulo avaliacoes
#include "aval.h"
#ifndef LIST
#define LIST
#include "list/list.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "arquivos/avaliacoes.txt"

typedef struct avaliacoes Aval;
struct avaliacoes{
    int id;
    char texto[400];
    char autor[25];
    int idInst;
};

// ----------
// AUXILIARES
// ----------

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

AvalComp* aval2avcomp(Aval* av){
    AvalComp* aval = (AvalComp*)malloc(sizeof(AvalComp));
    aval->id     = av->id;
    aval->idInst = av->idInst;
    strcpy(aval->autor, av->autor);
    strcpy(aval->texto, av->texto);

    return aval;
}

Aval* avcomp2aval(AvalComp* aval){
    Aval* av = (Aval*)malloc(sizeof(Aval));
    strcpy(av->autor, aval->autor);
    strcpy(av->texto, aval->texto);
    av->idInst = aval->idInst;
    av->id = aval->id;

    return av;
}

// ---------
// INTERFACE
// ---------


// id é calculado (independe do parâmetro)
// uma avaliação NÃO PODE ter no seu campo texto nem autor nenhum caractere ';'
// TODO: perguntar se podemos mudar algo do q botamos originalmente pq foi uma ideia ruim
int criaAvaliacao(AvalComp novaAval){
    Node* lst = arq2lst();
    
    for(char* c = strchr(novaAval.texto, ';'); c != NULL; c = strchr(novaAval.texto, ';')){
        strcpy(c, c + 1);
    }
    for(char* c = strchr(novaAval.autor, ';'); c != NULL; c = strchr(novaAval.autor, ';')){
        strcpy(c, c + 1);
    }
    int id;
    
    if(lst == NULL)
        id = 0;
    else
        id = lst->n + 1;

    lst = preInsert(lst, id);
    
    novaAval.id = id;
    Aval* av = avcomp2aval(&novaAval);

    lst->obj = (void*)av;

    lst2arq(lst);

    lst = deleteList(lst);

    return 1;
}

AvalComp* acessaAvaliacao(int idAval){
    Node* lst = arq2lst();
    
    Node* noAval = findNode(lst, idAval);
    if(noAval == NULL) 
        return NULL;
    
    Aval* av = (Aval*)(noAval->obj);
    
    AvalComp* aval = aval2avcomp(av);

    return aval;
}

// apenas texto será modificado
AvalComp* modificaAvaliacao(int idAval, AvalComp novaAval);
int deletaAvaliacao(int idAval);

AvalComp** acessaAvaliacoesInst(int idInst, int* tam);
AvalComp** acessaAvaliacoesAluno(char* nomeUsu, int* tam);