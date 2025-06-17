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

#define ARQUIVO "arquivos/alunos.txt"  // Caminho para o arquivo onde os dados dos alunos são salvos

// Estrutura interna do Aluno (lista encadeada)
typedef struct aluno {
    char nomeUsu[30];       // Nome de usuário do aluno
    char senha[20];         // Senha do aluno
    struct aluno* prox;     // Ponteiro para o próximo aluno na lista
} Aluno;


// Lê o arquivo e converte os dados em uma lista encadeada de alunos
static Aluno* arq2lst() {
    FILE* arq = fopen(ARQUIVO, "r");
    if (!arq) return NULL;  // Se não conseguiu abrir o arquivo, retorna NULL

    Aluno* lst = NULL;

    char nome[30], senha[20];
    while (fscanf(arq, "%29[^;];%19[^;];\n", nome, senha) == 2) {
        Aluno* novo = (Aluno*)malloc(sizeof(Aluno));
        strcpy(novo->nomeUsu, nome);
        strcpy(novo->senha, senha);
        novo->prox = lst;   // Insere no início da lista
        lst = novo;
    }

    fclose(arq);
    return lst;
}

// Escreve os dados da lista encadeada de volta no arquivo
static void lst2arq(Aluno* lst) {
    FILE* arq = fopen(ARQUIVO, "w");
    if (!arq) return;  // Falha ao abrir o arquivo para escrita

    for (; lst != NULL; lst = lst->prox) {
        fprintf(arq, "%s;%s;\n", lst->nomeUsu, lst->senha);
    }

    fclose(arq);
}

// Libera a memória alocada para a lista encadeada
static void liberaLista(Aluno* lst) {
    while (lst) {
        Aluno* temp = lst;
        lst = lst->prox;
        free(temp);
    }
}

// Converte um Aluno interno em um AlunoComp (versão compartilhável)
static AlunoComp* aluno2comp(Aluno* a) {
    if (!a) return NULL;
    AlunoComp* ac = malloc(sizeof(AlunoComp));
    strcpy(ac->nomeUsu, a->nomeUsu);
    strcpy(ac->senha, a->senha);
    return ac;
}

// Converte um AlunoComp (vindo de fora) em um Aluno interno
static Aluno* comp2aluno(AlunoComp* ac) {
    Aluno* a = malloc(sizeof(Aluno));
    strcpy(a->nomeUsu, ac->nomeUsu);
    strcpy(a->senha, ac->senha);
    a->prox = NULL;
    return a;
}

// Busca um aluno pelo nome de usuário e retorna seus dados (AlunoComp) se encontrado
AlunoComp* acessaAluno(char* nomeUsu) {
    Aluno* lst = arq2lst();
    Aluno* p;
    for (p = lst; p != NULL; p = p->prox) {
        if (!strcmp(p->nomeUsu, nomeUsu)) {  // Se encontrou o usuário
            AlunoComp* res = aluno2comp(p);
            liberaLista(lst);
            return res;
        }
    }
    liberaLista(lst);
    return NULL;  // Aluno não encontrado
}

// Verifica se o login do aluno é válido (nome de usuário e senha corretos)
bool loginAluno(char* nomeUsu, char* senha) {
    AlunoComp* a = acessaAluno(nomeUsu);
    if (!a) return false;  // Usuário não encontrado

    bool ok = strcmp(a->senha, senha) == 0;  // Confere senha
    free(a);
    return ok;
}

// Cria um novo aluno, se o nome de usuário não estiver vazio nem já existir
int criaAluno(AlunoComp novoAluno) {
    if (strlen(novoAluno.nomeUsu) == 0) return 0;  // Nome de usuário inválido

    Aluno* lst = arq2lst();
    for (Aluno* p = lst; p != NULL; p = p->prox) {
        if (!strcmp(p->nomeUsu, novoAluno.nomeUsu)) {  // Usuário já existe
            liberaLista(lst);
            return 0;
        }
    }

    // Cria novo aluno e insere no início da lista
    Aluno* novo = comp2aluno(&novoAluno);
    novo->prox = lst;
    lst = novo;

    lst2arq(lst);      // Salva lista atualizada no arquivo
    liberaLista(lst);  // Libera memória
    return 1;          // Aluno criado com sucesso
}

// Modifica os dados (nome/senha) de um aluno existente
AlunoComp* modificaAluno(char* nomeUsu, AlunoComp novoAluno) {
    Aluno* lst = arq2lst();
    for (Aluno* p = lst; p != NULL; p = p->prox) {
        if (!strcmp(p->nomeUsu, nomeUsu)) {
            strcpy(p->nomeUsu, novoAluno.nomeUsu);  // Atualiza nome
            strcpy(p->senha, novoAluno.senha);      // Atualiza senha
            AlunoComp* res = aluno2comp(p);
            lst2arq(lst);
            liberaLista(lst);
            return res;
        }
    }
    liberaLista(lst);
    return NULL;  // Aluno não encontrado
}

// Remove um aluno do sistema, se ele existir
int deletaAluno(char* nomeUsu) {
    Aluno *lst = arq2lst(), *ant = NULL, *p = lst;

    while (p) {
        if (!strcmp(p->nomeUsu, nomeUsu)) {
            if (ant == NULL) lst = p->prox;  // Primeiro elemento da lista
            else ant->prox = p->prox;        // Remove do meio/fim
            free(p);
            lst2arq(lst);
            liberaLista(lst);
            return 1;  // Aluno deletado com sucesso
        }
        ant = p;
        p = p->prox;
    }

    liberaLista(lst);
    return 0;  // Aluno não encontrado
}
