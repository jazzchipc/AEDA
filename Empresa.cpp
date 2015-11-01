/*
 * Empresa.cpp
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

Empresa::Empresa()
{

}

vector<Servico*> Empresa::getServicos() const
{
	return servicos;
}

void Empresa::adicionaServico(Servico *s1)
{
	servicos.push_back(s1);
}

void Empresa::retiraServico(Servico *s1)
{
	int index = sequentialSearch(servicos, s1);
	if(index == -1)
		throw ServicoInexistente(s1->getId());
	else
		servicos.erase(servicos.begin() + index);
}

void Empresa::readServicos() const
{
	for(unsigned int i = 0; i < getServicos().size(); i++)
	{
		cout << getServicos()[i]->getPreco() << endl;
		for(unsigned int j = 0; j < getServicos()[i]->getClientes().size(); j++)
		{
			cout << getServicos()[i]->getClientes()[j]->getNome() << endl;
		}
	}
}

vector< Servico*> Empresa::returnAtivos()
{
	vector< Servico*> ativos;

	for(unsigned int i = 0 ; i < servicos.size() ; i++)
	{
		if(servicos[i]->getStatus() == true)
			ativos.push_back(servicos[i]);
	}

	return ativos;
}

vector< Servico*> Empresa::returnInativos()
{
	vector< Servico*> inativos;

	for(unsigned int i = 0; i < servicos.size() ; i++)
	{
		if(servicos[i]->getStatus() == false)
			inativos.push_back(servicos[i]);
	}

	return inativos;
}

void Empresa::printServicos(vector< Servico*> s1)
{
	for(unsigned int i = 0;i < s1.size(); i++)
	{
		cout << s1[i]->getId() << " , " << s1[i]->getPreco() << " , " << s1[i]->getStatus() << endl;
	}
}

vector<Servico*> Empresa::servicoCliente(string nome, unsigned int nif) {
	vector<Servico*> retorno;
	vector<Cliente*> c1;

	for (unsigned int i = 0; i < servicos.size(); i++)
	{
		c1 = servicos[i]->getClientes();

		for (unsigned int j = 0; j < c1.size(); j++)
		{
			if ((c1[j]->getNome() == nome) && (c1[j]->getNif() == nif)) {
				retorno.push_back(servicos[i]);
			}
		}
	}

	return retorno;
}


