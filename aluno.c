/*
 * Guilherme Melo Gratz 			2211068
 * João Miguel Rodrigues Montenegro da Franca	2411289
 * Lorena Silveira dos Santos 			2312667
*/
// Modulo Aluno

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

// objetivo: Grava a lista no arquivo e libera a memória
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

// objetivo: Conversão de aluno para aluno compartilhado
static AlunoComp* aluno2comp(Aluno* a) {
    if (!a) return NULL;
    AlunoComp* ac = malloc(sizeof(AlunoComp));
    strcpy(ac->nomeUsu, a->nomeUsu);
    strcpy(ac->senha, a->senha);
    return ac;
}
//Conversão de aluno compartilhado para aluno
static Aluno* comp2aluno(AlunoComp* ac) {
    Aluno* a = malloc(sizeof(Aluno));
    strcpy(a->nomeUsu, ac->nomeUsu);
    strcpy(a->senha, ac->senha);
    a->prox = NULL;
    return a;
}

// Funções de acesso 
// objetivo: Acessa um aluno pelo nome de usuário
// Retorna um ponteiro para AlunoComp ou NULL se não encontrar
AlunoComp* acessaAluno(char* nomeUsu) {
    for (Aluno* p = listaAlunos; p; p = p->prox)
        if (!strcmp(p->nomeUsu, nomeUsu))
            return aluno2comp(p);
    return NULL;
}
// objetivo: Verifica se o login do aluno é válido
bool loginAluno(char* nomeUsu, char* senha) {
    AlunoComp* a = acessaAluno(nomeUsu);
    if (!a) return false;
    bool ok = strcmp(a->senha, senha) == 0;
    free(a);
    return ok;
}
// objetivo: Cria um novo aluno na lista
// Retorna 1 se conseguiu criar, 0 se o nome de usuário já existe ou se o nome de usuário for vazio
// Se o nome de usuário já existir, não altera a lista
// Se o nome de usuário for vazio, não cria o aluno
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
// objetivo: Modifica os dados de um aluno na lista
// Retorna um ponteiro para AlunoComp com os dados atualizados ou NULL se não encontrar o aluno
// Se não encontrar o aluno, não altera a lista
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
// objetivo: Deleta um aluno da lista
// Retorna 1 se conseguiu deletar, 0 se não encontrar o aluno
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
