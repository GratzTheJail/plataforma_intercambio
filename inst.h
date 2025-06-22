// Modulo Instituições

#ifndef AVALCOMP
#define AVALCOMP
#include "instComp.h"
#endif

#include <stdbool.h>

void inicializaInst();
void finalizaInst();
InstComp* acessaInst(int idInst);
bool loginInst(int idInst, char* senha);
int criaInst(InstComp novaInst);
InstComp* modificaInst(int idInst, InstComp novaInst);
int deletaInst(int idInst);
