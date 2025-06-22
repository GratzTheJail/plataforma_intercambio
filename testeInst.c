// MODULO TEMPORARIO
// TESTES MODULO INSTITUICAO

#include "inst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função auxiliar para imprimir o resultado dos testes
void imprimeResultado(char* descricao, int esperado, int obtido) {
    printf("%s\nEsperado: %d | Obtido: %d\n\n", descricao, esperado, obtido);
}

int main() {
    printf(" ****** TESTES MODULO INSTITUICAO ******\n\n");

    // Lê o arquivo de instituicoes uma única vez
    inicializaInst();

    // --- Testes de criação de instituicao ---

    InstComp i;
    strcpy(i.nome, "PUC");
    strcpy(i.pais, "Brasil");
    strcpy(i.senha, "1234");
    int criacao1 = criaInst(i);
    imprimeResultado("criaInst - Caso 2: Instituicao 'PUC' do pais 'Brasil' criada com sucesso", 1, (criacao1 != 0));

    InstComp repetido;
    strcpy(repetido.nome, "PUC");
    strcpy(repetido.pais, "Brasil");
    strcpy(repetido.senha, "5678");
    int criacao2 = criaInst(repetido);
    imprimeResultado("criaInst - Caso 1: Nome de instituicao 'PUC' ja existe", 0, criacao2);

    InstComp vazio;
    strcpy(vazio.nome, "");
    strcpy(vazio.pais, "Brasil");
    strcpy(vazio.senha, "1234");
    int criacao3 = criaInst(vazio);
    imprimeResultado("criaInst - Caso 3: Nome de instituicao vazio", 0, criacao3);

    InstComp vazioSenha;
    strcpy(vazioSenha.nome, "PUC3");
    strcpy(vazioSenha.pais, "Brasil");
    strcpy(vazioSenha.senha, "");
    int criacao5 = criaInst(vazioSenha);
    imprimeResultado("criaInst - Caso 5: Senha de instituicao vazia", 0, criacao5);

    InstComp i2;
    strcpy(i2.nome, "UFRJ");
    strcpy(i2.pais, "Brasil");
    strcpy(i2.senha, "5678");
    criaInst(i2);

    // --- Testes de login ---

    imprimeResultado("loginInst - Caso 3: Login valido para 'PUC'", 1, loginInst(1, "1234"));
    imprimeResultado("loginInst - Caso 2: Senha errada para 'PUC'", 0, loginInst(1, "errada"));
    imprimeResultado("loginInst - Caso 1: ID inexistente '-1'", 0, loginInst(-1, "qualquer"));

    // --- Testes de acesso ---

    InstComp* acesso1 = acessaInst(1);
    imprimeResultado("acessaInst - Caso 1: Instituicao de ID '1' acessada com sucesso", 1, acesso1 != NULL);
    free(acesso1);

    InstComp* acesso2 = acessaInst(-1);
    imprimeResultado("acessaInst - Caso 2: Instituicao de ID '-1' nao encontrada", 0, acesso2 != NULL);
    free(acesso2);

    // --- Testes de modificação ---

    InstComp novo;
    strcpy(novo.nome, "UERJ");  // muda o nome
    strcpy(novo.pais, "Brasil");
    strcpy(novo.senha, "4321");
    InstComp* modificado = modificaInst(2, novo);
    imprimeResultado("modificaInst - Caso 1: Instituicao de ID '2' modificada", 1, modificado != NULL);
    imprimeResultado("loginInst - Apos modificacao de senha para a instituicao", 1, loginInst(2, "4321"));
    free(modificado);

    InstComp* naoModificado = modificaInst(-1, novo);
    imprimeResultado("modificaInst - Caso 2: Instituicao de ID '-1' (inexistente) nao modificada", 0, naoModificado != NULL);
    free(naoModificado);

    InstComp nomeRepetido;
    strcpy(nomeRepetido.nome, "UERJ");  //nome que ja existe no id 2
    strcpy(nomeRepetido.pais, "Brasil");
    strcpy(nomeRepetido.senha, "4321");
    InstComp* modificadoRepetido = modificaInst(1, novo);
    imprimeResultado("modificaInst - Caso 3: Instituicao de ID '2' ja possuia o nome a ser modificado", 0, modificadoRepetido != NULL);
    free(modificadoRepetido);

    // --- Testes de deleção ---

    int del1 = deletaInst(2);
    imprimeResultado("deletaInst - Caso 2: Instituicao de ID '2' deletada com sucesso", 1, del1);
    imprimeResultado("loginInst - Apos deletar ID '2'", 0, loginInst(2, "4321"));

    int del2 = deletaInst(-1);
    imprimeResultado("deletaInst - Caso 1: ID '-1' nao encontrado", 0, del2);

    // Salva os dados atualizados no arquivo
    finalizaInst();

    printf("****** FIM DOS TESTES ******\n");
    return 0;
}
