// aluno.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

#define ARQUIVO "arquivos/alunos.txt"



static Aluno* listaAlunos = NULL;  // lista viva durante a execução

// Inicializa a lista a partir do arquivo
void inicializaAlunos() {
    FILE* arq = fopen(ARQUIVO, "r");
    if (!arq) return;

    char nome[30], senha[20];
    while (fscanf(arq, "%29[^;];%19[^;];\n", nome, senha) == 2) {
        Aluno* novo = malloc(sizeof(Aluno));
        strcpy(novo->nomeUsu, nome);
        strcpy(novo->senha, senha);
        novo->prox = listaAlunos;
        listaAlunos = novo;
    }

    fclose(arq);
}

// Grava a lista no arquivo e libera a memória
void finalizaAlunos() {
    FILE* arq = fopen(ARQUIVO, "w");
    if (!arq) return;

    for (Aluno* p = listaAlunos; p; p = p->prox)
        fprintf(arq, "%s;%s;\n", p->nomeUsu, p->senha);

    // Libera memória
    Aluno* temp;
    while (listaAlunos) {
        temp = listaAlunos;
        listaAlunos = listaAlunos->prox;
        free(temp);
    }

    fclose(arq);
}

// Conversões
static AlunoComp* aluno2comp(Aluno* a) {
    if (!a) return NULL;
    AlunoComp* ac = malloc(sizeof(AlunoComp));
    strcpy(ac->nomeUsu, a->nomeUsu);
    strcpy(ac->senha, a->senha);
    return ac;
}

static Aluno* comp2aluno(AlunoComp* ac) {
    Aluno* a = malloc(sizeof(Aluno));
    strcpy(a->nomeUsu, ac->nomeUsu);
    strcpy(a->senha, ac->senha);
    a->prox = NULL;
    return a;
}

// Funções de acesso
AlunoComp* acessaAluno(char* nomeUsu) {
    for (Aluno* p = listaAlunos; p; p = p->prox)
        if (!strcmp(p->nomeUsu, nomeUsu))
            return aluno2comp(p);
    return NULL;
}

bool loginAluno(char* nomeUsu, char* senha) {
    AlunoComp* a = acessaAluno(nomeUsu);
    if (!a) return false;
    bool ok = strcmp(a->senha, senha) == 0;
    free(a);
    return ok;
}

int criaAluno(AlunoComp novoAluno) {
    if (strlen(novoAluno.nomeUsu) == 0) return 0;

    for (Aluno* p = listaAlunos; p; p = p->prox)
        if (!strcmp(p->nomeUsu, novoAluno.nomeUsu))
            return 0;

    Aluno* novo = comp2aluno(&novoAluno);
    novo->prox = listaAlunos;
    listaAlunos = novo;
    return 1;
}

AlunoComp* modificaAluno(char* nomeUsu, AlunoComp novoAluno) {
    for (Aluno* p = listaAlunos; p; p = p->prox) {
        if (!strcmp(p->nomeUsu, nomeUsu)) {
            strcpy(p->nomeUsu, novoAluno.nomeUsu);
            strcpy(p->senha, novoAluno.senha);
            return aluno2comp(p);
        }
    }
    return NULL;
}

int deletaAluno(char* nomeUsu) {
    Aluno *p = listaAlunos, *ant = NULL;
    while (p) {
        if (!strcmp(p->nomeUsu, nomeUsu)) {
            if (ant) ant->prox = p->prox;
            else listaAlunos = p->prox;
            free(p);
            return 1;
        }
        ant = p;
        p = p->prox;
    }
    return 0;
}
