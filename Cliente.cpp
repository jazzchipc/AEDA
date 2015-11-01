/*
 * Cliente.cpp
 *
 *  Created on: 27/10/2015
 *      Author: ASUS
 */

#include "Camiao.h"
#include "Cliente.h"
#include "Empresa.h"
#include "Frota.h"
#include "Servico.h"
#include "sequentialSearch.h"

Cliente::Cliente(string nome, unsigned int nif)
{
	this-> nome = nome;
	this-> nif = nif;
}

string Cliente::getNome() const
{
	return nome;
}

unsigned int Cliente::getNif() const
{
	return nif;
}

void Cliente::updateNome(string nome)
{
	this -> nome = nome;
}

void Cliente::updateNif(unsigned int nif)
{
	this -> nif = nif;
}

bool Cliente::operator==(Cliente c1)
{
	if ((c1.nome == nome) && (c1.nif == nif))
		return true;
	else
		return false;
}



