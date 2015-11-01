/*
 * Camiao.cpp
 *
 *  Created on: 27/10/2015
 *      Author: ASUS
 */

/*TEST*/

#include "Camiao.h"
#include "Cliente.h"
#include "Empresa.h"
#include "Frota.h"
#include "Servico.h"
#include "sequentialSearch.h"

Camiao::Camiao(int codigo, unsigned int cap_max, bool cap_cong)
{
	this-> codigo = codigo;
	this-> cap_max = cap_max;
	this-> cap_cong = cap_cong;
}

unsigned int Camiao::getCapMax() const
{
	return cap_max;
}

bool Camiao::getCapCong() const
{
	return cap_cong;
}

int Camiao::getCodigo() const
{
	return codigo;
}

void Camiao::updateCodigo(int codigo)
{
	this -> codigo = codigo;
}

void Camiao::updateCapMax(unsigned int cap_max)
{
	this -> cap_max = cap_max;
}

void Camiao::updateCapCong(bool cap_cong)
{
	this -> cap_cong = cap_cong;
}




