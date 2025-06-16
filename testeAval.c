// MODULO TEMPORARIO
// TESTES MODULO AVALIAÇÕES
#ifndef AVAL
#define AVAL
#include "aval.h"
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
	

	// TESTES DE BUSCA
	printf("TESTES DE BUSCA:\n");
	printf("Busca do índice %d:\n", 1);
	AvalComp* busca = acessaAvaliacao(1);
	if(busca == NULL)
		printf("Não encontrado :(\n");
	else
	 	printf("Encontrado: Autor: %s\tInstituição: %d\nTexto: %s\n", 
			busca->autor, busca->idInst, busca->texto);
	
	printf("-------------------------------------------------\n");
	printf("Busca do índice %d:\n", -1341);
	busca = acessaAvaliacao(-1341);
	if(busca == NULL)
		printf("Não encontrado :(\n");
	else
	 	printf("Encontrado: Autor: %s\tInstituição: %d\nTexto: %s\n", 
			busca->autor, busca->idInst, busca->texto);
	printf("-------------------------------------------------\n");
	printf("-------------------------------------------------\n");



	return 0;
}

/*
COMPILAÇÃO USANDO:
Linux Fedora 42
gcc 15.1.1
gcc -Wall -o progAval testeAval.c aval.c list/list.c
*/