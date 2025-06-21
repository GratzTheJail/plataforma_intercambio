// Modulo Instituições

#ifndef AVALCOMP
#define AVALCOMP
#include "instComp.h"
#endif

#include <stdbool.h>

InstComp* acessaInst(int idInst);
bool loginInst(int idInst, char* senha);
InstComp* criaInst(InstComp novaInst);
InstComp* modificaInst(int idInst, InstComp novaInst);
int deletaInst(int idInst);
