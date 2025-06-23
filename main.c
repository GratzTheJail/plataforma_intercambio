/*
 * Guilherme Melo Gratz 			2211068
 * João Miguel Rodrigues Montenegro da Franca	2411289
 * Lorena Silveira dos Santos 			2312667
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "inst.h"
#include "aluno.h"
#include "aval.h"

int main() {
    int opcao;
    char continuar = 's';
    bool alunoLogin = false;
    bool instLogin = false;
    AlunoComp* alunoAtual = (AlunoComp*)malloc(sizeof(AlunoComp));
    InstComp* instAtual = (InstComp*)malloc(sizeof(InstComp));

    inicializaAlunos();
    inicializaInst();
    init_aval();

    while (continuar == 's' || continuar == 'S') {
        if (!alunoLogin && !instLogin) {
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
                    alunoLogin = true;
                    alunoAtual = acessaAluno(nomeUsu);
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
                    instLogin = true;
                    instAtual = acessaInst(idInst);
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

                printf("Pais da instituicao: ");
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
        }

        if (alunoLogin && alunoAtual != NULL) {
            int opAluno;
            printf("\n=== Menu do Aluno ===\n");
            printf("1 - Modificar dados\n");
            printf("2 - Deletar conta\n");
            printf("3 - Visualizar perfil\n");
            printf("4 - Buscar universidade e ver avaliacoes\n");
            printf("Opcao: ");
            scanf("%d", &opAluno);
            getchar();

            if (opAluno == 1) {
                AlunoComp novo;
                strcpy(novo.nomeUsu, alunoAtual->nomeUsu); // mantém nome
                printf("Nova senha: ");
                fgets(novo.senha, sizeof(novo.senha), stdin);
                novo.senha[strcspn(novo.senha, "\n")] = '\0';

                if (modificaAluno(alunoAtual->nomeUsu, novo) != NULL) {
                    printf("Dados modificados com sucesso!\n");
                }
                else {
                    printf("Erro ao modificar.\n");
                }

            }
            else if (opAluno == 2) {
                if (deletaAluno(alunoAtual->nomeUsu) == 1) {
                    printf("Conta deletada.\n");
                    alunoLogin = false;
                }
                else {
                    printf("Erro ao deletar conta.\n");
                }

            }
            else if (opAluno == 3) {
                printf("\nPerfil do Aluno:\n");
                printf("Usuario: %s\n", alunoAtual->nomeUsu);

                Node* lista = acessaAvaliacoesAluno(alunoAtual->nomeUsu);
                if (lista == NULL) {
                    printf("Voce ainda nao fez nenhuma avaliacao.\n");
                }
                else {
                    printf("\n--- Suas Avaliacoes ---\n");
                    Node* atual = lista;
                    while (atual != NULL) {
                        AvalComp* a = (AvalComp*)atual->obj;
                        printf("- ID: %d | Inst: %d\n", a->id, a->idInst);
                        printf("  \"%s\"\n", a->texto);
                        atual = atual->next;
                    }
                }

                int subop;
                printf("\n--- Acoes ---\n");
                printf("1 - Criar nova avaliacao\n");
                printf("2 - Modificar avaliacao existente\n");
                printf("3 - Deletar avaliacao\n");
                printf("Opcao: ");
                scanf("%d", &subop);
                getchar();

                if (subop == 1) {
                    AvalComp nova;
                    nova.id = 0; // será atribuído automaticamente
                    strcpy(nova.autor, alunoAtual->nomeUsu);

                    printf("ID da instituicao que deseja avaliar: ");
                    scanf("%d", &nova.idInst);
                    getchar();

                    printf("Texto da avaliacao: ");
                    fgets(nova.texto, sizeof(nova.texto), stdin);
                    nova.texto[strcspn(nova.texto, "\n")] = '\0';

                    if (criaAvaliacao(nova) != 0) {
                        printf("Avaliacao criada com sucesso!\n");
                    }
                    else {
                        printf("Erro ao criar avaliacao.\n");
                    }

                }
                else if (subop == 2) {
                    int idMod;
                    printf("ID da avaliacao a modificar: ");
                    scanf("%d", &idMod);
                    getchar();

                    AvalComp* existente = acessaAvaliacao(idMod);
                    if (existente == NULL) {
                        printf("Avaliacao nao encontrada.\n");
                    }
                    else if (strcmp(existente->autor, alunoAtual->nomeUsu) != 0) {
                        printf("Voce nao tem permissao para modificar esta avaliacao.\n");
                    }
                    else {
                        AvalComp nova;
                        nova.id = idMod;
                        nova.idInst = existente->idInst;
                        strcpy(nova.autor, alunoAtual->nomeUsu);

                        printf("Novo texto: ");
                        fgets(nova.texto, sizeof(nova.texto), stdin);
                        nova.texto[strcspn(nova.texto, "\n")] = '\0';

                        if (modificaAvaliacao(idMod, nova) == 1) {
                            printf("Avaliacao modificada com sucesso.\n");
                        }
                        else {
                            printf("Erro ao modificar avaliacao.\n");
                        }
                    }
                }
                else if (subop == 3) {
                    int idDel;
                    printf("ID da avaliacao a deletar: ");
                    scanf("%d", &idDel);
                    getchar();

                    AvalComp* existente = acessaAvaliacao(idDel);
                    if (existente == NULL) {
                        printf("Avaliacao nao encontrada.\n");
                    }
                    else if (strcmp(existente->autor, alunoAtual->nomeUsu) != 0) {
                        printf("Voce nao tem permissao para deletar esta avaliacao.\n");
                    }
                    else {
                        if (deletaAvaliacao(idDel) == 1) {
                            printf("Avaliacao deletada com sucesso.\n");
                        }
                        else {
                            printf("Erro ao deletar avaliacao.\n");
                        }
                    }
                }
                else {
                    printf("Opcao invalida.\n");
                }
            }
            else if (opAluno == 4) {
                int idInst;
                printf("Digite o ID da universidade que deseja buscar: ");
                scanf("%d", &idInst);
                getchar();

                InstComp* inst = acessaInst(idInst);
                if (inst == NULL) {
                    printf("Instituicao nao encontrada.\n");
                }
                else {
                    printf("\n--- Perfil da Instituicao ---\n");
                    printf("ID: %d\n", inst->id);
                    printf("Nome: %s\n", inst->nome);
                    printf("Pais: %s\n", inst->pais);

                    printf("\n--- Avaliacoes ---\n");
                    Node* lista = acessaAvaliacoesInst(idInst);
                    if (lista == NULL) {
                        printf("Nenhuma avaliacao encontrada para esta instituicao.\n");
                    }
                    else {
                        Node* atual = lista;
                        while (atual != NULL) {
                            AvalComp* a = (AvalComp*)atual->obj;
                            printf("- Avaliacao #%d por %s:\n", a->id, a->autor);
                            printf("  \"%s\"\n\n", a->texto);
                            atual = atual->next;
                        }
                    }
                }
            }
            else {
                printf("Opcao invalida.\n");
            }
        }

        if (instLogin && instAtual != NULL) {
            int opInst;
            printf("\n=== Menu da Instituicao ===\n");
            printf("1 - Modificar dados\n");
            printf("2 - Deletar conta\n");
            printf("3 - Visualizar perfil\n");
            printf("Opcao: ");
            scanf("%d", &opInst);
            getchar();

            if (opInst == 1) {
                InstComp nova;
                nova.id = instAtual->id;
                printf("Novo nome: ");
                fgets(nova.nome, sizeof(nova.nome), stdin);
                nova.nome[strcspn(nova.nome, "\n")] = '\0';

                printf("Novo pais: ");
                fgets(nova.pais, sizeof(nova.pais), stdin);
                nova.pais[strcspn(nova.pais, "\n")] = '\0';

                printf("Nova senha: ");
                fgets(nova.senha, sizeof(nova.senha), stdin);
                nova.senha[strcspn(nova.senha, "\n")] = '\0';

                if (modificaInst(instAtual->id, nova) != NULL) {
                    printf("Dados modificados com sucesso!\n");
                }
                else {
                    printf("Erro ao modificar.\n");
                }

            }
            else if (opInst == 2) {
                if (deletaInst(instAtual->id) == 1) {
                    printf("Conta deletada.\n");
                    instLogin = false;
                }
                else {
                    printf("Erro ao deletar conta.\n");
                }

            }
            else if (opInst == 3) {
                printf("\nPerfil da Instituicao:\n");
                printf("Nome: %s\n", instAtual->nome);
                printf("Pais: %s\n", instAtual->pais);
                printf("ID: %d\n", instAtual->id);
                printf("\n--- Avaliacoes Recebidas ---\n");
                Node* lista = acessaAvaliacoesInst(instAtual->id);
                if (lista == NULL) {
                    printf("Nenhuma avaliacao ainda.\n");
                }
                else {
                    Node* atual = lista;
                    while (atual != NULL) {
                        AvalComp* a = (AvalComp*)atual->obj;
                        printf("- Avaliacao #%d por %s:\n", a->id, a->autor);
                        printf("  \"%s\"\n\n", a->texto);
                        atual = atual->next;
                    }
                }
            }
            else {
                printf("Opcao invalida.\n");
            }
        }

        printf("\nDeseja voltar ao menu? (s/n): ");
        scanf(" %c", &continuar);
        getchar();
    }

    finalizaAlunos();
    finalizaInst();
    end_aval();

    printf("Encerrando o programa...\n");
    return 0;
}

/*
COMPILACAO
Sistema: 		Linux Fedora 42 x86_64 - Intel CPU
Versao do Compilador: 	gcc 15.1.1
Comando:		gcc -Wall -o prog main.c aluno.c aval.c inst.c list/list.c
*/
