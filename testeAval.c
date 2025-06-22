// MODULO TEMPORARIO
// TESTES MODULO AVALIAÇÕES
#ifndef AVAL
#define AVAL
#include "aval.h"
#include <stdlib.h>
#endif
#ifndef AVALCOMP
#define AVALCOMP
#include "avalcomp.h"
#endif
#ifndef LIST
#define LIST
#include "list/list.h"
#endif
#include <string.h>
#include <stdio.h>

int main(){
	// deletando tudo no arquivo
	FILE* arq = fopen("arquivos/avaliacoes.txt","w");
	fclose(arq);

	// inicializa BD
	init_aval();
	
	AvalComp aval; 
	int id = 0;
	
	// TESTES INSERÇÃO
	printf("------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------\n");
	printf("TESTES DE INSERÇÃO:\n");
	printf("-------------------\n");
	
	// 0
	strcpy(aval.autor, "The; Jail");
	strcpy(aval.texto, "Melhor ;faculdade do mundo!");
	aval.idInst = 123;
	aval.id = 0;
	
	printf("Inserção de:\tAutor: %s\tInstituição: %d\nTexto: %s\n", aval.autor, aval.idInst, aval.texto);
	int criou = criaAvaliacao(aval);
	printf((criou) ? ("Sucesso! :)\n"):("Fracasso! :(\n"));
	printf("------------------------------------------------------------------------\n");
	
	// 1 
	strcpy(aval.autor, "Mary Tony;");
	strcpy(aval.texto, "Meilleure; université du monde!");
	aval.idInst = 333;
	aval.id = 1;

	printf("Inserção de:\tAutor: %s\tInstituição: %d\nTexto: %s\n", aval.autor, aval.idInst, aval.texto);
	criou = criaAvaliacao(aval);
	printf((criou) ? ("Sucesso! :)\n"):("Fracasso! :(\n"));
	printf("------------------------------------------------------------------------\n");
	
	
	// 2
	strcpy(aval.autor, "Isabela Melo");
	strcpy(aval.texto, "Ja fui a faculdades melhores;...");
	aval.idInst = 123;
	aval.id = 2;

	printf("Inserção de:\tAutor: %s\tInstituição: %d\nTexto: %s\n", 
		aval.autor, aval.idInst, aval.texto);
	criou = criaAvaliacao(aval);
	printf((criou) ? ("Sucesso! :)\n"):("Fracasso! :(\n"));
	printf("------------------------------------------------------------------------\n");


	// 3
	strcpy(aval.autor, "Walter Gratz");
	strcpy(aval.texto, "Minha faculdade era muito longe... e difícil!");
	aval.idInst = 123;
	aval.id = 3;
	
	printf("Inserção de:\tAutor: %s\tInstituição: %d\nTexto: %s\n", aval.autor, aval.idInst, aval.texto);
	criou = criaAvaliacao(aval);
	printf((criou) ? ("Sucesso! :)\n"):("Fracasso! :(\n"));
	printf("------------------------------------------------------------------------\n");

	// 4
	strcpy(aval.autor, "Mary Tony;");
	strcpy(aval.texto, "Essa faculdade é uma porcaria!");
	aval.idInst = 222;
	aval.id = 4;

	printf("Inserção de:\tAutor: %s\tInstituição: %d\nTexto: %s\n", aval.autor, aval.idInst, aval.texto);
	criou = criaAvaliacao(aval);
	printf((criou) ? ("Sucesso! :)\n"):("Fracasso! :(\n"));
	printf("------------------------------------------------------------------------\n");

	// 5
	strcpy(aval.autor, "The Jail");
	strcpy(aval.texto, "Diese ist echt eine peinliche aber gute Universität!");
	aval.idInst = 666;
	aval.id = 4;

	printf("Inserção de:\tAutor: %s\tInstituição: %d\nTexto: %s\n", aval.autor, aval.idInst, aval.texto);
	criou = criaAvaliacao(aval);
	printf((criou) ? ("Sucesso! :)\n"):("Fracasso! :(\n"));
	printf("------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------\n");



	// TESTES DE BUSCA
	printf("TESTES DE BUSCA:\n");
	printf("----------------\n");
	
	// caso: encontrado
	id = 1;
	printf("Busca do índice %d:\n", id);
	AvalComp* busca = acessaAvaliacao(id);
	if(busca == NULL)
		printf("Não encontrado :(\n");
	else{
		printf("Encontrado: Autor: %s\tInstituição: %d\nTexto: %s\n", 
			busca->autor, busca->idInst, busca->texto);
		printf("Note que o caracter ';' foi retirado do texto e do nome\n");

	}
	
	// caso: nao encontrado
	id = -1341;
	printf("------------------------------------------------------------------------\n");
	printf("Busca do índice %d:\n", id);
	busca = acessaAvaliacao(id);
	if(busca == NULL)
		printf("Não encontrado :(\n");
	else
	 	printf("Encontrado: Autor: %s\tInstituição: %d\nTexto: %s\n", 
			busca->autor, busca->idInst, busca->texto);
	
	free(busca);
	printf("------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------\n");



	// TESTES DE MODIFICAÇÃO
	printf("TESTES DE MODIFICAÇÃO:\n");
	printf("----------------------\n");
	
	// caso: encontrado
	id = 2;
	printf("Modificação do texto do índice %d:\n", id);
	
	busca = acessaAvaliacao(id);
	if(busca != NULL)
		printf("Antes:\n%s\n", busca->texto);
	free(busca);
	
	AvalComp modifica;
	strcpy(modifica.texto, "Essa faculdade é meio ruim...");
	
	if(modificaAvaliacao(id, modifica)){
		busca = acessaAvaliacao(id);
		if(busca != NULL)
			printf("\nDepois:\n%s\nModificado com sucesso :)\n", busca->texto);
	} else {
		printf("Não encontrado...\n");
	}
	printf("------------------------------------------------------------------------\n");

	// caso: nao encontrado
	id = -2342;
	printf("Modificação do texto do índice %d:\n", id);
	
	busca = acessaAvaliacao(id);
	if(busca != NULL)
		printf("Antes:\n%s\n", busca->texto);
	free(busca);
	
	strcpy(modifica.texto, "Essa faculdade é meio ruim...");
	
	if(modificaAvaliacao(id, modifica)){
		busca = acessaAvaliacao(id);
		if(busca != NULL)
			printf("\nDepois:\n%s\nModificado com sucesso :)\n", busca->texto);
	} else {
		printf("Não encontrado...\n");
	}
	printf("------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------\n");

	
	
	// TESTES DE EXCLUSÃO
	printf("TESTES DE EXCLUSÃO:\n");
	printf("-------------------\n");
	
	id = 0;
	// caso: encontrado
	printf("Exclusão do índice %d:\n", id);

	if(deletaAvaliacao(id)){
		busca = acessaAvaliacao(id);
		if(busca == NULL)
			printf("Deletado com sucesso :)\n");
	} else {
		printf("Não encontrado...\n");
	}

	// printf(">Atenção: caso neste primeiro caso diga que não houve sucesso, ");
	// printf("apague o banco de dados, pois o programa já foi rodado e a entrada já foi exluída.\n");
	// printf(">Quando o banco de dados for deletado, será re-criado com o índice %d nele\n", id);
	printf("------------------------------------------------------------------------\n");

	id = -87090;
	// caso: não encontrado
	printf("Exclusão do índice %d:\n", id);
	
	if(deletaAvaliacao(id)){
		busca = acessaAvaliacao(id);
		if(busca == NULL)
			printf("Deletado com sucesso :)\n");
	} else {
		printf("Não encontrado...\n");
	}
	printf("------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------\n");


	// TESTES DE BUSCA POR INSTITUIÇÃO
	printf("TESTES DE BUSCA POR INST:\n");
	printf("-------------------------\n");

	// caso: encontrado
	id = 123;
	printf("Busca Avals da inst %d:\n", id);
	
	Node* buscaAvals = acessaAvaliacoesInst(id);
	if(buscaAvals != NULL){
		for(Node* p = buscaAvals; p != NULL; p = p->next){
			printf("Autor: %s\tInst: %d\nTexto:%s\n\n", ((AvalComp*)(p->obj))->autor, 
				((AvalComp*)(p->obj))->idInst, ((AvalComp*)(p->obj))->texto);
		}
		deleteList(buscaAvals);
	} else {
		printf("Nenhuma Avaliação encontrada...\n");
	}
	printf("------------------------------------------------------------------------\n");

	// caso: não encontrado
	id = -9823;
	printf("Busca Avals da inst %d:\n", id);
	
	buscaAvals = acessaAvaliacoesInst(id);
	if(buscaAvals != NULL){
		for(Node* p = buscaAvals; p != NULL; p = p->next){
			printf("Autor: %s\tInst: %d\nTexto:%s\n\n", ((AvalComp*)(p->obj))->autor, 
				((AvalComp*)(p->obj))->idInst, ((AvalComp*)(p->obj))->texto);
		}
		deleteList(buscaAvals);
	} else {
		printf("Nenhuma Avaliação encontrada...\n");
	}
	printf("------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------\n");

	// TESTES DE BUSCA POR AUTOR
	printf("TESTES DE BUSCA POR AUTOR:\n");
	printf("--------------------------\n");

	// caso: encontrado
	char* nome = "The Jail";
	printf("Busca Avals do autor %s:\n", nome);
	
	buscaAvals = acessaAvaliacoesAluno(nome);
	if(buscaAvals != NULL){
		for(Node* p = buscaAvals; p != NULL; p = p->next){
			printf("Autor: %s\tInst: %d\nTexto:%s\n\n", ((AvalComp*)(p->obj))->autor, 
				((AvalComp*)(p->obj))->idInst, ((AvalComp*)(p->obj))->texto);
		}
		deleteList(buscaAvals);
	} else {
		printf("Nenhuma Avaliação encontrada...\n");
	}
	printf("------------------------------------------------------------------------\n");	

	// caso: encontrado
	nome = "Mary Tony";
	printf("Busca Avals do autor %s:\n", nome);
	
	buscaAvals = acessaAvaliacoesAluno(nome);
	if(buscaAvals != NULL){
		for(Node* p = buscaAvals; p != NULL; p = p->next){
			printf("Autor: %s\tInst: %d\nTexto:%s\n\n", ((AvalComp*)(p->obj))->autor, 
				((AvalComp*)(p->obj))->idInst, ((AvalComp*)(p->obj))->texto);
		}
		deleteList(buscaAvals);
	} else {
		printf("Nenhuma Avaliação encontrada...\n");
	}
	printf("------------------------------------------------------------------------\n");	

	// caso: encontrado
	nome = "Tony Ramos";
	printf("Busca Avals do autor %s:\n", nome);
	
	buscaAvals = acessaAvaliacoesAluno(nome);
	if(buscaAvals != NULL){
		for(Node* p = buscaAvals; p != NULL; p = p->next){
			printf("Autor: %s\tInst: %d\nTexto:%s\n\n", ((AvalComp*)(p->obj))->autor, 
				((AvalComp*)(p->obj))->idInst, ((AvalComp*)(p->obj))->texto);
		}
		deleteList(buscaAvals);
	} else {
		printf("Nenhuma Avaliação encontrada...\n");
	}
	printf("------------------------------------------------------------------------\n");	
	printf("------------------------------------------------------------------------\n");	
	printf("------------------------------------------------------------------------\n");	

	// persiste BD
	end_aval();
	return 0;
}

/*
COMPILAÇÃO USANDO:
Linux Fedora 42
gcc 15.1.1
gcc -Wall -o progAval testeAval.c aval.c list/list.c
*/
