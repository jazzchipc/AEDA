#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <iomanip>
#include <string>

#include "Empresa.h"

using namespace std;

/*Função que apaga o ecrã da consola*/
void clearScreen();

void printTitulo();

/*Primeiro ecrã a aparecer*/
Empresa firstScreen();

/*Optar por gerar ou carregar um ficheiro de empresa*/
Empresa gerar();
Empresa carregar();

/*Menu principal*/
void menuPrincipal(Empresa &empresa);

/*Opções de edição*/
void editarClientes(Empresa &empresa);
void editarServicos(Empresa &empresa);
void editarFrota(Empresa &empresa);

#endif // INTERFACE_H

