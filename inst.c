// Modulo Instituições

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inst.h"

#define ARQUIVO "arquivos/instituicoes.txt"

typedef struct instituicoes Inst;
struct instituicoes {
    int id;
    char nome[50];
    char pais[25];
    char senha[20];
    Inst* prox;
};

static Inst* arq2lst() {
    FILE* arq = fopen(ARQUIVO, "r");
    if (!arq) return NULL;  

    Inst* lst = NULL;

    int id;
    char nome[50], pais[25], senha[20];
    while (fscanf(arq, "%d;%49[^;];%24[^;];%19[^;];\n", id, nome, pais, senha) == 2) {
        Inst* novo = (Inst*)malloc(sizeof(Inst));
        novo->id = id;
        strcpy(novo->nome, nome);
        strcpy(novo->pais, pais);
        strcpy(novo->senha, senha);
        novo->prox = lst; 
        lst = novo;
    }

    fclose(arq);
    return lst;
}

static void lst2arq(Inst* lst) {
    FILE* arq = fopen(ARQUIVO, "w");
    if (!arq) return;

    for (; lst != NULL; lst = lst->prox) {
        fprintf(arq, "%d;%s;%s;%s;\n", lst->id, lst->nome, lst->pais, lst->senha);
    }

    fclose(arq);
}

static void liberaLista(Inst* lst) {
    while (lst) {
        Inst* temp = lst;
        lst = lst->prox;
        free(temp);
    }
}

static InstComp* inst2comp(Inst* i) {
    if (!i) return NULL;
    InstComp* ic = malloc(sizeof(InstComp));
    ic->id = i->id;
    strcpy(ic->nome, i->nome);
    strcpy(ic->pais, i->pais);
    strcpy(ic->senha, i->senha);
    return ic;
}

static Inst* comp2inst(InstComp* ic) {
    Inst* i = malloc(sizeof(Inst));
    i->id = ic->id;
    strcpy(i->nome, ic->nome);
    strcpy(i->pais, ic->pais);
    strcpy(i->senha, ic->senha);
    i->prox = NULL;
    return i;
}

InstComp* acessaInst(int id) {
    Inst* lst = arq2lst();
    Inst* p;
    for (p = lst; p != NULL; p = p->prox) {
        if (p->id == id) {  
            InstComp* res = inst2comp(p);
            liberaLista(lst);
            return res;
        }
    }
    liberaLista(lst);
    return NULL;
}

bool loginInst(int id, char* senha) {
    InstComp* i = acessaInst(id);
    if (!i) return false;  

    bool ok = strcmp(i->senha, senha) == 0;  
    free(a);
    return ok;
}

int criaInst(InstComp novaInst) {
    if (strlen(novaInst.nome) == 0) return 0;  

    Inst* lst = arq2lst();
    for (Inst* p = lst; p != NULL; p = p->prox) {
        if (!strcmp(p->nome, novaInst.nome) || (p->id == novaInst.id)) {  //verifica tambem se ja existe uma instituicao com esse id
            liberaLista(lst);
            return 0;
        }
    }

    Inst* novo = comp2inst(&novaInst);
    novo->prox = lst;
    lst = novo;

    lst2arq(lst);     
    liberaLista(lst);  
    return 1;         
}

InstComp* modificaInst(int id, InstComp novaInst) {
    Inst* lst = arq2lst();
    for (Inst* p = lst; p != NULL; p = p->prox) {
        if (p->id == id) {
            strcpy(p->nome, novaInst.nome);  
            strcpy(p->pais, novaInst.pais);
            strcpy(p->senha, novaInst.senha);   
            InstComp* res = inst2comp(p);
            lst2arq(lst);
            liberaLista(lst);
            return res;
        }
    }
    liberaLista(lst);
    return NULL;  
}

int deletaInst(int id) {
    Inst* lst = arq2lst(), * ant = NULL, * p = lst;

    while (p) {
        if (p->id = id) {
            if (ant == NULL) lst = p->prox;  
            else ant->prox = p->prox;        
            free(p);
            lst2arq(lst);
            liberaLista(lst);
            return 1; 
        }
        ant = p;
        p = p->prox;
    }

    liberaLista(lst);
    return 0;  
}