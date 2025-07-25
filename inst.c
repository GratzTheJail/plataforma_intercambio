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

static Inst* lst = NULL; 

// carrega dados persistidos no começo do programa
void inicializaInst() {
    FILE* arq = fopen(ARQUIVO, "r");
    if (!arq) return;

    int id;
    char nome[50], pais[25], senha[20];
    while (fscanf(arq, "%d;%49[^;];%24[^;];%19[^;];\n", &(id), nome, pais, senha) == 4) {
        Inst* novo = (Inst*)malloc(sizeof(Inst));
        novo->id = id;
        strcpy(novo->nome, nome);
        strcpy(novo->pais, pais);
        strcpy(novo->senha, senha);
        novo->prox = lst;
        lst = novo;
    }

    fclose(arq);
}

// persiste dados ao final do programa
void finalizaInst() {
    FILE* arq = fopen(ARQUIVO, "w");
    if (!arq) return;

    for (Inst* p = lst; p; p = p->prox)
        fprintf(arq, "%d;%s;%s;%s;\n", p->id, p->nome, p->pais, p->senha);

    // Libera memória
    Inst* temp;
    while (lst) {
        temp = lst;
        lst = lst->prox;
        free(temp);
    }

    fclose(arq);
}

// transforma do tipo compartilhado inst para instcomp 
static InstComp* inst2comp(Inst* i) {
    if (!i) return NULL;
    InstComp* ic = malloc(sizeof(InstComp));
    ic->id = i->id;
    strcpy(ic->nome, i->nome);
    strcpy(ic->pais, i->pais);
    strcpy(ic->senha, i->senha);
    return ic;
}

// transforma do tipo compartilhado instcomp para inst 
static Inst* comp2inst(InstComp* ic) {
    Inst* i = malloc(sizeof(Inst));
    i->id = ic->id;
    strcpy(i->nome, ic->nome);
    strcpy(i->pais, ic->pais);
    strcpy(i->senha, ic->senha);
    i->prox = NULL;
    return i;
}

// acessa uma instituição com o id passado
// retorna o tipo compartilhado InstComp da instituição buscada, NULL caso não encontre
InstComp* acessaInst(int id) {
    Inst* p;
    for (p = lst; p != NULL; p = p->prox) {
        if (p->id == id) {  
            InstComp* res = inst2comp(p);
            return res;
        }
    }
    return NULL;
}

// retorna true se o login foi bem sucedido (id e senha corretos), false caso contrario
bool loginInst(int id, char* senha) {
    InstComp* i = acessaInst(id);
    if (!i) return false;  

    bool ok = strcmp(i->senha, senha) == 0;  
    free(i);
    return ok;
}

// cria uma instituição com os dados especificados por novaInst
// calcula o proprio id (id novaInst ignorado)
// retorna 0 caso já tenha sido adicionado ou o id adicionado 
int criaInst(InstComp novaInst) {
    if (strlen(novaInst.nome) == 0 || strlen(novaInst.senha) == 0) return 0;

    int id = 1;
    for (Inst* p = lst; p; p = p->prox) {
        if (!strcmp(p->nome, novaInst.nome)) {  
            return 0;
        }
        ++id; //garante que o id sempre vai ser diferente dos que ja existem
    }
    novaInst.id = id;

    Inst* novo = comp2inst(&novaInst);
    novo->prox = lst;
    lst = novo;

    return id;         
}

// modifica instituição de id passado com os dados passados em novaInst
// retorna NULL caso não seja encontrado ou o tipo compartilhado de instituição modificado
InstComp* modificaInst(int id, InstComp novaInst) {
    for (Inst* p = lst; p; p = p->prox) {
        if (p->id != id && !strcmp(p->nome, novaInst.nome)) { //nome ja existe para outro id
            return NULL;
        }
    }
    for (Inst* p = lst; p; p = p->prox) {
        if (p->id == id) {
            strcpy(p->nome, novaInst.nome);
            strcpy(p->pais, novaInst.pais);
            strcpy(p->senha, novaInst.senha);
            InstComp* res = inst2comp(p);
            return res;
        }
    }
    return NULL;  
}

// deleta instituição de id passado
// retorna 1 se foi deletado, 0 caso não seja encontrado
int deletaInst(int id) {
    Inst* ant = NULL, * p = lst;

    while (p) {
        if (p->id == id) {
            if (ant == NULL) lst = p->prox;  
            else ant->prox = p->prox;        
            free(p);
            return 1; 
        }
        ant = p;
        p = p->prox;
    }

    return 0;  
}