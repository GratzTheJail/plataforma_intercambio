// MODULO TEMPORARIO
// TESTES MODULO ALUNO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

// Função auxiliar para imprimir o resultado dos testes
void imprimeResultado(char* descricao, int esperado, int obtido) {
    printf("%s\nEsperado: %d | Obtido: %d\n\n", descricao, esperado, obtido);
}

int main() {
    printf(" ****** TESTES MODULO ALUNO ******\n\n");

    // teste criaAluno

    // Caso 3: Aluno criado com sucesso
    AlunoComp a1;
    strcpy(a1.nomeUsu, "joao");
    strcpy(a1.senha, "1234");
    int criacao1 = criaAluno(a1);
    imprimeResultado("criaAluno - Caso 3: Aluno 'joao' criado com sucesso", 1, criacao1);

    // Caso 1: Aluno não criado (já existe)
    AlunoComp repetido;
    strcpy(repetido.nomeUsu, "joao");
    strcpy(repetido.senha, "outrasenha");
    int criacao2 = criaAluno(repetido);
    imprimeResultado("criaAluno - Caso 1: Nome de usuario 'joao' já existe", 0, criacao2);

    // Caso 2: Nome de usuário vazio
    AlunoComp vazio;
    strcpy(vazio.nomeUsu, "");
    strcpy(vazio.senha, "1234");
    int criacao3 = criaAluno(vazio);
    imprimeResultado("criaAluno - Caso 2: Nome de usuário vazio", 0, criacao3);

    // Outro aluno válido para testes seguintes
    AlunoComp a2;
    strcpy(a2.nomeUsu, "maria");
    strcpy(a2.senha, "5678");
    criaAluno(a2);

    // testes loginAluno

    // Caso 3: Login OK
    imprimeResultado("loginAluno - Caso 3: Login válido para 'joao'", 1, loginAluno("joao", "1234"));

    // Caso 2: Senha errada
    imprimeResultado("loginAluno - Caso 2: Senha errada para 'maria'", 0, loginAluno("maria", "errada"));

    // Caso 1: Usuário inexistente
    imprimeResultado("loginAluno - Caso 1: Usuário inexistente 'pedro'", 0, loginAluno("pedro", "qualquer"));

    // testes acessaAluno

    // Caso 1: Aluno acessado com sucesso
    AlunoComp* acesso1 = acessaAluno("maria");
    imprimeResultado("acessaAluno - Caso 1: Aluno 'maria' acessado com sucesso", 1, acesso1 != NULL);
    free(acesso1);

    // Caso 2: Aluno não encontrado
    AlunoComp* acesso2 = acessaAluno("naoexiste");
    imprimeResultado("acessaAluno - Caso 2: Aluno 'naoexiste' não encontrado", 0, acesso2 != NULL);
    free(acesso2);

    // testes modificaAluno 

    // Caso 1: Aluno existente
    AlunoComp novo;
    strcpy(novo.nomeUsu, "maria");  // mantemos o mesmo nome
    strcpy(novo.senha, "novaSenha");
    AlunoComp* modificado = modificaAluno("maria", novo);
    imprimeResultado("modificaAluno - Caso 1: Aluno 'maria' modificado", 1, modificado != NULL);
    imprimeResultado("loginAluno - Após modificação de senha para 'maria'", 1, loginAluno("maria", "novaSenha"));
    free(modificado);

    // Caso 2: Aluno inexistente
    AlunoComp* naoModificado = modificaAluno("inexistente", novo);
    imprimeResultado("modificaAluno - Caso 2: Aluno 'inexistente' não modificado", 0, naoModificado != NULL);
    free(naoModificado);

    // testes deletaAluno

    // Caso 2: Aluno deletado com sucesso
    int del1 = deletaAluno("joao");
    imprimeResultado("deletaAluno - Caso 2: 'joao' deletado com sucesso", 1, del1);

    // Tentativa de login após deleção
    imprimeResultado("loginAluno - Após deletar 'joao'", 0, loginAluno("joao", "1234"));

    // Caso 1: Aluno não encontrado
    int del2 = deletaAluno("inexistente");
    imprimeResultado("deletaAluno - Caso 1: 'inexistente' não encontrado", 0, del2);

    printf("****** FIM DOS TESTES ******\n");
    return 0;
}
