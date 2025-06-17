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
	AvalComp aval; 
	
	// TESTES INSERÇÃO
	printf("-------------------------------------------------\n");
	printf("-------------------------------------------------\n");
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
	printf("-------------------------------------------------\n");
	
	// 1 
	strcpy(aval.autor, "Mary Tony;");
	strcpy(aval.texto, "Mellieur; faculté de mondé!");
	aval.idInst = 333;
	aval.id = 1;

	printf("Inserção de:\tAutor: %s\tInstituição: %d\nTexto: %s\n", aval.autor, aval.idInst, aval.texto);
	criou = criaAvaliacao(aval);
	printf((criou) ? ("Sucesso! :)\n"):("Fracasso! :(\n"));
	printf("-------------------------------------------------\n");
	
	
	// 2
	strcpy(aval.autor, "Isabela Melo");
	strcpy(aval.texto, "Ja fui a faculdades melhores;...");
	aval.idInst = 123;
	aval.id = 2;

	printf("Inserção de:\tAutor: %s\tInstituição: %d\nTexto: %s\n", 
		aval.autor, aval.idInst, aval.texto);
	criou = criaAvaliacao(aval);
	printf((criou) ? ("Sucesso! :)\n"):("Fracasso! :(\n"));
	printf("-------------------------------------------------\n");
	printf("-------------------------------------------------\n");
	printf("-------------------------------------------------\n");



	// TESTES DE BUSCA
	printf("TESTES DE BUSCA:\n");
	printf("----------------\n");
	// caso: encontrado
	printf("Busca do índice %d:\n", 1);
	AvalComp* busca = acessaAvaliacao(1);
	if(busca == NULL)
		printf("Não encontrado :(\n");
	else
	 	printf("Encontrado: Autor: %s\tInstituição: %d\nTexto: %s\n", 
			busca->autor, busca->idInst, busca->texto);
	
	// caso: nao encontrado
	printf("-------------------------------------------------\n");
	printf("Busca do índice %d:\n", -1341);
	busca = acessaAvaliacao(-1341);
	if(busca == NULL)
		printf("Não encontrado :(\n");
	else
	 	printf("Encontrado: Autor: %s\tInstituição: %d\nTexto: %s\n", 
			busca->autor, busca->idInst, busca->texto);
	
	free(busca);
	printf("-------------------------------------------------\n");
	printf("-------------------------------------------------\n");
	printf("-------------------------------------------------\n");



	// TESTES DE MODIFICAÇÃO
	printf("TESTES DE MODIFICAÇÃO:\n");
	printf("----------------------\n");
	
	// caso: encontrado
	printf("Modificação do texto do índice %d:\n", 2);
	
	busca = acessaAvaliacao(1);
	if(busca != NULL)
		printf("Antes:\n%s\n", busca->texto);
	free(busca);
	
	AvalComp modifica;
	strcpy(modifica.texto, "Essa faculdade é meio ruim...");
	
	if(modificaAvaliacao(1, modifica)){
		busca = acessaAvaliacao(1);
		if(busca != NULL)
			printf("\nDepois:\n%s\nModificado com sucesso :)\n", busca->texto);
	} else {
		printf("Não encontrado...\n");
	}
	printf("-------------------------------------------------\n");

	// caso: nao encontrado
	printf("Modificação do texto do índice %d:\n", -2342);
	
	busca = acessaAvaliacao(-2342);
	if(busca != NULL)
		printf("Antes:\n%s\n", busca->texto);
	free(busca);
	
	strcpy(modifica.texto, "Essa faculdade é meio ruim...");
	
	if(modificaAvaliacao(-2342, modifica)){
		busca = acessaAvaliacao(-2342);
		if(busca != NULL)
			printf("\nDepois:\n%s\nModificado com sucesso :)\n", busca->texto);
	} else {
		printf("Não encontrado...\n");
	}
	printf("-------------------------------------------------\n");

	return 0;
}

/*
COMPILAÇÃO USANDO:
Linux Fedora 42
gcc 15.1.1
gcc -Wall -o progAval testeAval.c aval.c list/list.c
*/