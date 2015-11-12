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

/*Menus específicos*/
void mostrarClientes(Empresa &empresa);
void mostrarServicos(Empresa &empresa);
void mostrarFrota(Empresa &empresa);

/*Editar, remover ou adicionar serviços*/
void editarServicos(Empresa &empresa);
void adicionarServicos(Empresa &empresa);
void removerServicos(Empresa &empresa);

/*Editar, remover ou adicionar clientes*/
void mostrarClientes(Empresa &empresa);

/*Editar, remover ou adicionar camioes*/
void editarCamiao(Empresa &empresa);
void adicionarCamiao(Empresa &empresa);
void removerCamiao(Empresa &empresa);


#endif // INTERFACE_H

