/*
 * Empresa.cpp
 *
 *  Created on: 27/10/2015
 *      Author: ASUS
 */

#include <fstream>
#include "string.h"
#include <cstring>
#include <iomanip>

#include "Camiao.h"
#include "Cliente.h"
#include "Empresa.h"
#include "Frota.h"
#include "Servico.h"
#include "sequentialSearch.h"


Empresa::Empresa()
{

}

void Empresa::setFrota(Frota frota)
{
	this->frota = frota;
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

void Empresa::printServicos()
{
	for(unsigned int i = 0;i < this->servicos.size(); i++)
	{
		cout << this->servicos[i]->getId() << " , " << this->servicos[i]->getPreco() << " , " << this->servicos[i]->getStatus() << endl;
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

void Empresa::saveEmpresa()
{
	string f;

	cout << "Indique o nome com que quer guardar o ficheiro: " << endl;
	getline(cin, f);

	f = f + ".txt";

	char* ficheiro = &f[0]; // converte para array de chars, de forma a poder ser usado pelo ofstream

	ofstream output; // cria um ficheiro para armazenar os dados
	output.open(ficheiro);

	//Guardar frota

	vector <Camiao *> camioes = this->frota.getCamioes();

	output << "FROTA" << endl;

	for (unsigned int i = 0; i < camioes.size(); i++)
	{
		output << camioes[i]->getCapCong() << " " << camioes[i]->getCapMax() << " " <<
			camioes[i]->getCodigo() << endl;
	}

	//Guardar servicos e clientes
	output << "SERVICOS" << endl;

	for (unsigned int i = 0; i < this->servicos.size(); i++)
	{
		output << this->servicos[i]->getId() << " " << this->servicos[i]->getPreco() << " " << this->servicos[i]->getStatus() << endl;

		vector <Cliente *> clientes = this->servicos[i]->getClientes();

		output << "Clientes" << endl;

		for (unsigned int j = 0; j < clientes.size(); j++)
		{
			output << clientes[j]->getNome() << " " << clientes[j]->getNif() << endl;
		}

	}

	output.close();


}




