/*
 * Guilherme Melo Gratz 			2211068
 * João Miguel Rodrigues Montenegro da Franca	2411289
 * Lorena Silveira dos Santos 			2312667
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "inst.h"
#include "aluno.h"
//#include "aval.h"

int main() {
    int opcao;
    char continuar = 's';

    inicializaAlunos();
    inicializaInst();

    while (continuar == 's' || continuar == 'S') {
        printf("\n===== MENU =====\n");
        printf("1 - Login como Aluno\n");
        printf("2 - Login como Instituicao\n");
        printf("3 - Cadastrar novo Aluno\n");
        printf("4 - Cadastrar nova Instituicao\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer

        if (opcao == 1) {
            char nomeUsu[30], senha[20];

            printf("Nome de usuario: ");
            fgets(nomeUsu, sizeof(nomeUsu), stdin);
            nomeUsu[strcspn(nomeUsu, "\n")] = '\0';

            printf("Senha: ");
            fgets(senha, sizeof(senha), stdin);
            senha[strcspn(senha, "\n")] = '\0';

            if (loginAluno(nomeUsu, senha)) {
                printf("Login de aluno bem-sucedido!\n");
            }
            else {
                printf("Falha no login de aluno.\n");
            }

        }
        else if (opcao == 2) {
            int idInst;
            char senha[20];

            printf("ID da instituicao: ");
            scanf("%d", &idInst);
            getchar();

            printf("Senha: ");
            fgets(senha, sizeof(senha), stdin);
            senha[strcspn(senha, "\n")] = '\0';

            if (loginInst(idInst, senha)) {
                printf("Login de instituicao bem-sucedido!\n");
            }
            else {
                printf("Falha no login de instituicao.\n");
            }

        }
        else if (opcao == 3) {
            AlunoComp novo;
            printf("Nome de usuario do novo aluno: ");
            fgets(novo.nomeUsu, sizeof(novo.nomeUsu), stdin);
            novo.nomeUsu[strcspn(novo.nomeUsu, "\n")] = '\0';

            printf("Senha: ");
            fgets(novo.senha, sizeof(novo.senha), stdin);
            novo.senha[strcspn(novo.senha, "\n")] = '\0';

            if (criaAluno(novo) == 1) {
                printf("Aluno cadastrado com sucesso!\n");
            }
            else {
                printf("Erro ao cadastrar aluno.\n");
            }

        }
        else if (opcao == 4) {
            InstComp nova;

            printf("Nome da instituicao: ");
            fgets(nova.nome, sizeof(nova.nome), stdin);
            nova.nome[strcspn(nova.nome, "\n")] = '\0';

            fgets(nova.pais, sizeof(nova.pais), stdin);
            nova.pais[strcspn(nova.pais, "\n")] = '\0';

            printf("Senha: ");
            fgets(nova.senha, sizeof(nova.senha), stdin);
            nova.senha[strcspn(nova.senha, "\n")] = '\0';
            int id = criaInst(nova);
            if (id != 0) {
                printf("Instituicao cadastrada com sucesso! ID - %d\n", id);
            }
            else {
                printf("Erro ao cadastrar instituicao.\n");
            }

        }
        else {
            printf("Opcao invalida.\n");
        }

        printf("\nDeseja voltar ao menu? (s/n): ");
        scanf(" %c", &continuar);
        getchar();
    }

    finalizaAlunos();
    finalizaInst();

    printf("Encerrando o programa...\n");
    return 0;
}