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

int main(){
	// EU
	AvalComp aval; 

	strcpy(aval.autor, "The; Jail");
	strcpy(aval.texto, "Melhor ;faculdade do mundo!");
	aval.idInst = 123;
	aval.id = 0;

	criaAvaliacao(aval);

	
	// MARY 
	strcpy(aval.autor, "Mary Tony;");
	strcpy(aval.texto, "Mellieur; faculté de mondé!");
	aval.idInst = 333;
	aval.id = 1;

	criaAvaliacao(aval);
	
	
	// ISA
	strcpy(aval.autor, "Isabela Melo");
	strcpy(aval.texto, "Ja fui a faculdades melhores;...");
	aval.idInst = 123;
	aval.id = 2;

	criaAvaliacao(aval);
	return 0;
}

/*
COMPILAÇÃO USANDO:
Linux Fedora 42
gcc 15.1.1
gcc -Wall -o progAval testeAval.c aval.c list/list.c
*/