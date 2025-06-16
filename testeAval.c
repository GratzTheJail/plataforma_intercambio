// MODULO TEMPORARIO
// TESTES MODULO AVALIAÇÕES

#include "aval.h"
#ifndef LIST
#define LIST
#include "list/list.h"
#endif
#include <stdlib.h>
#include <string.h>

int main(){
	Node* lst = NULL;

	// EU
	Aval avalEu; 

	strcpy(avalEu.autor, "The Jail");
	strcpy(avalEu.texto, "Melhor faculdade do mundo!");
	avalEu.idInst = 123;
	avalEu.id = 0;

	lst = preInsert(lst, avalEu.id);
	lst->obj = (void*)&avalEu;


	// MARY
	Aval avalMary; 

	strcpy(avalMary.autor, "Mary Tony");
	strcpy(avalMary.texto, "Mellieur faculté de mondé!");
	avalMary.idInst = 333;
	avalMary.id = 1;

	lst = preInsert(lst, avalMary.id);
	lst->obj = (void*)&avalMary;


	// ISA
	Aval avalIsa; 

	strcpy(avalIsa.autor, "Isabela Melo");
	strcpy(avalIsa.texto, "Ja fui a faculdades melhores...");
	avalIsa.idInst = 123;
	avalIsa.id = 2;

	lst = preInsert(lst, avalIsa.id);
	lst->obj = (void*)&avalIsa;

	// PRINTS
	printList(lst);

	for(Node* p = lst; p != NULL; p = p->next){
		printf("%s disse sobre %d:\n%s\n\n", ((Aval*)p->obj)->autor, ((Aval*)p->obj)->idInst, ((Aval*)p->obj)->texto);
	}

	lst2arq(lst);
	lst = deleteList(lst);

	lst = arq2lst();

	printList(lst);
	for(Node* p = lst; p != NULL; p = p->next){
		printf("%s disse sobre %d:\n%s\n\n", ((Aval*)p->obj)->autor, ((Aval*)p->obj)->idInst, ((Aval*)p->obj)->texto);
	}

	lst = deleteList(lst);

	return 0;
}
