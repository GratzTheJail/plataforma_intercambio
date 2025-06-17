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

Node* avaliacoes = NULL;

// ----------
// AUXILIARES
// ----------

Node *deletaLista(Node *top) {
    Node *current = top;
    while (current != NULL) {
        Node *next = current->next;
        if (current->obj != NULL) {
            free(current->obj);  // Libera o objeto
        }
        free(current);           // Libera o nó
        current = next;
    }
    return NULL;
}

void lst2arq(Node* lst){
    FILE* arq = fopen(ARQUIVO, "w");
    Node* avals = lst;
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

// nao pode passar ponteiro nulo 
Aval* avcmp2av(AvalComp* aval){
    Aval* av = (Aval*)malloc(sizeof(Aval));
    if(av == NULL) exit(1);

    av->id = aval->id;
    av->idInst = aval->idInst;
    strcpy(av->autor, aval->autor);
    strcpy(av->texto, aval->texto);

    return av;
}

// nao pode passar ponteiro nulo 
AvalComp* av2avcmp(Aval* av){
    AvalComp* aval = (AvalComp*)malloc(sizeof(Aval));
    if(aval == NULL) exit(1);

    aval->id = av->id;
    aval->idInst = av->idInst;
    strcpy(aval->autor, av->autor);
    strcpy(aval->texto, av->texto);

    return aval;
}

// funcao auxiliar de busca de avaliação do tipo estruturado Aval para outras buscas
Aval* buscaAval(Node* lst, int id){
    Node* noAval = findNode(lst, id);
    if(noAval == NULL) 
        return NULL;

    Aval* av = (Aval*)(noAval->obj);

    return av;
}


// ----------------------
// PRINCIPAIS / INTERFACE
// ----------------------


// id é calculado (independe do parâmetro)
// uma avaliação NÃO PODE ter no seu campo texto nem autor nenhum caractere ';'
// TODO: perguntar se podemos mudar algo do q botamos originalmente pq foi uma ideia ruim
int criaAvaliacao(AvalComp novaAval){
    Node* lst = arq2lst();
    
    // retira caracteres ';' 
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
    
    // insere com ID calculado
    lst = preInsert(lst, id);
    
    // converte de AvalComp (tipo compartilhado) para Aval (tipo especifico)
    Aval* av = avcmp2av(&novaAval);

    lst->obj = (void*)av;
    fprintf(stderr, "Cria %s\n", novaAval.autor);

    // escreve arquivo e deleta lista
    lst2arq(lst);
    deletaLista(lst);

    return 1;
}

AvalComp* acessaAvaliacao(int idAval){
    Node* lst = arq2lst();

    Aval* av = buscaAval(lst, idAval);
    if(av == NULL)
        return NULL;
    
    AvalComp* aval = av2avcmp(av);

    deletaLista(lst);

    return aval;
}

// apenas texto será modificado
int modificaAvaliacao(int idAval, AvalComp novaAval){
    Node* lst = arq2lst();

    Aval* av = buscaAval(lst, idAval);
    if(av == NULL)
        return 0;

    Aval* novaAv = avcmp2av(&novaAval);
    strcpy(av->texto, novaAv->texto);

    lst2arq(lst);
    free(novaAv);

    return 1;
}

// TODO: terminar essa merda
int deletaAvaliacao(int idAval){
    Node* lst = arq2lst();

    Aval* av = buscaAval(lst, idAval);
    if(av == NULL)
        return 0;

    // ...

    return 0;
}

Node* acessaAvaliacoesInst(int idInst, int* tam);
Node* acessaAvaliacoesAluno(char* nomeUsu, int* tam);