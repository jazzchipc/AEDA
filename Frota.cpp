/*
 * Frota.cpp
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


Frota::Frota()
{}

void Frota::adicionaCamiao(Camiao *c1)
{
	camioes.push_back(c1);
}

void Frota::retiraCamiao(Camiao *c1)
{
	int index = sequentialSearch(camioes, c1);
	if(index == -1)
		throw CamiaoInexistente(c1->getCodigo());
	else
		camioes.erase(camioes.begin() + index);

}

void Frota::readCamioes()const
{
	for(unsigned int i = 0; i < camioes.size(); i++)
	{
		cout << camioes[i]->getCodigo() << " " << camioes[i]->getCapMax()<< " " << camioes[i]->getCapCong() << endl;
	}
}



