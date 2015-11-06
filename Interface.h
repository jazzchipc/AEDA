#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <iomanip>
#include <string>

#include "Empresa.h"

using namespace std;

/*Fun��o que apaga o ecr� da consola*/
void clearScreen();

void printTitulo();

/*Primeiro ecr� a aparecer*/
Empresa firstScreen();

/*Optar por gerar ou carregar um ficheiro de empresa*/
Empresa gerar();
Empresa carregar();

/*Menu principal*/
void menuPrincipal(Empresa &empresa);

/*Op��es de edi��o*/
void editarClientes(Empresa &empresa);
void editarServicos(Empresa &empresa);
void editarFrota(Empresa &empresa);

#endif // INTERFACE_H

