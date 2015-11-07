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

/**
* \brief Cria uma Frota sem parâmetros
* \return Esta função não possui retorno
*/
Frota::Frota()
{}

/**
* \brief Adiciona um Camião à frota
* \param c1 Camião a adicionar
* \return Esta função não possui retorno
*/
void Frota::adicionaCamiao(Camiao *c1)
{
	camioes.push_back(c1);
}

/**
* \brief Retira um  Camião da frota, caso este lá esteja, caso contrário lança a excessão CamiaoInexistente
* \param c1 Camião a retirar
* \return Esta função não possui retorno
*/
void Frota::retiraCamiao(Camiao *c1)
{
	int index = sequentialSearch(camioes, c1);
	if (index == -1)
		throw CamiaoInexistente(c1->getCodigo());
	else
		camioes.erase(camioes.begin() + index);

}

/**
* \brief Imprime todas as informações dos camiões da frota
* \return Esta função não possui retorno
*/
void Frota::readCamioes()const
{
	for (unsigned int i = 0; i < camioes.size(); i++)
	{
		cout << camioes[i]->getCodigo() << " " << camioes[i]->getCapMax() << " " << camioes[i]->getCapCong() << endl;
	}
}

/**
* \brief Obtém o vetor que guarda todos os camiões da frota
* \return Retorna o vetor
*/
vector <Camiao *> Frota::getCamioes()
{
	return this->camioes;
}



