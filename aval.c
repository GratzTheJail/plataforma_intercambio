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

static Node* lst = NULL;

// ----------
// AUXILIARES
// ----------

// escreve conteúdo de uma lista no arquivo
void lst2arq(Node* avals){
    FILE* arq = fopen(ARQUIVO, "w");
    if(arq == NULL)
        exit(1);
    for(; avals != NULL; avals = avals->next){
        Aval* aval = (Aval*)avals->obj;
        fprintf(arq, "%d;", aval->id);
        fprintf(arq, "%s;", aval->texto);
        fprintf(arq, "%s;", aval->autor);
        fprintf(arq, "%d;\n", aval->idInst);
    }
    fclose(arq);
}

// transforma arquivo em lista
Node* arq2lst(){
    FILE* arq = fopen(ARQUIVO, "r");
    if(arq == NULL)
        exit(1);

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

// transforma Aval* em AvalComp* (aloca espaço para a nova AvalComp)
AvalComp* aval2avcomp(Aval* av){
    AvalComp* aval = (AvalComp*)malloc(sizeof(AvalComp));
    aval->id     = av->id;
    aval->idInst = av->idInst;
    strcpy(aval->autor, av->autor);
    strcpy(aval->texto, av->texto);

    return aval;
}

// transforma AvalComp* em Aval* (aloca espaço para a nova AvalComp)
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

void init_aval(){
    lst = arq2lst();
}

void end_aval(){
    lst2arq(lst);
    deleteList(lst);
}

// id é calculado (independe do parâmetro)
// uma avaliação perderá caracteres ';' nos seus campos texto e autor 
int criaAvaliacao(AvalComp novaAval){    
    // retira caracter ';' das strings texto e autor
    for(char* c = strchr(novaAval.texto, ';'); c != NULL; c = strchr(novaAval.texto, ';')){
        strcpy(c, c + 1);
    }
    for(char* c = strchr(novaAval.autor, ';'); c != NULL; c = strchr(novaAval.autor, ';')){
        strcpy(c, c + 1);
    }
    
    // calcula ID
    int id;
    if(lst == NULL)
        id = 0;
    else
        id = lst->n + 1;

    // transforma avaliacao de entrada (AvalComp) em Aval
    novaAval.id = id;
    Aval* av = avcomp2aval(&novaAval);
    
    // insere na lista
    lst = preInsert(lst, id);
    lst->obj = (void*)av;

    return 1;
}

// acessa avaliação com id = idAval
// caso não encontre retorna NULL
// retorna ponteiro para a avaliação encontrada (com memória alocada) 
AvalComp* acessaAvaliacao(int idAval){    
    // busca no com id especificado
    Node* noAval = findNode(lst, idAval);
    if(noAval == NULL) 
        return NULL;
    
    // transforma Aval* achado em AvalComp*
    Aval* av = (Aval*)(noAval->obj);
    AvalComp* aval = aval2avcomp(av);

    return aval;
}

// apenas texto será modificado
// não lida com problemas de string 
// retorna 1 se modificou e 0 se não encontrou
int modificaAvaliacao(int idAval, AvalComp novaAval){    
    // busca no com id especificado
    Node* noAval = findNode(lst, idAval);
    if(noAval == NULL) 
        return 0;

    // muda texto da aval na lista
    Aval* av = (Aval*)(noAval->obj);
    strcpy(av->texto, novaAval.texto);

    return 1;
}

int deletaAvaliacao(int idAval){    
    // busca no com id especificado
    Node* noAval = findNode(lst, idAval);
    if(noAval == NULL) 
        return 0;
    
    // deleta o nó
    deleteNode(lst, idAval);

    return 1;
}

Node* acessaAvaliacoesInst(int idInst){
    // lista de avaliações q será retornada
    Node* avals = NULL;

    for(Node* p = lst; p != NULL; p = p->next){
        Aval* av = (Aval*)(p->obj);
        
        // se avaliação atual for da inst desejada, adiciona na lista
        if(av->idInst == idInst){
            AvalComp* aval = aval2avcomp(av);
            avals = preInsert(avals, countNodes(avals));

            avals->obj = (void*)aval;
        }
    }

    return avals;
}

Node* acessaAvaliacoesAluno(char* nomeUsu){
    // lista de avaliações q será retornada
    Node* avals = NULL;

    for(Node* p = lst; p != NULL; p = p->next){
        Aval* av = (Aval*)(p->obj);
        
        // se avaliação atual for do autor desejado, adiciona na lista
        if(!strcmp(av->autor, nomeUsu)){
            AvalComp* aval = aval2avcomp(av);
            avals = preInsert(avals, countNodes(avals));

            avals->obj = (void*)aval;
        }
    }

    return avals;   
}