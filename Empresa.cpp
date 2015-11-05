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
#include <sstream>

#include "Camiao.h"
#include "Cliente.h"
#include "Empresa.h"
#include "Frota.h"
#include "Servico.h"
#include "sequentialSearch.h"


Empresa::Empresa(string nome)
{
	this->nome = nome;
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
	string f = this->nome;

	f = f + ".txt";

	char* ficheiro = &f[0]; // converte para array de chars, de forma a poder ser usado pelo ofstream

	ofstream output; // cria um ficheiro "<nome da empresa>.txt" para armazenar os dados
	output.open(ficheiro);

	//Guardar frota

	vector <Camiao *> camioes = this->frota.getCamioes();

	output << "BEGIN_FROTA" << endl;

	for (unsigned int i = 0; i < camioes.size(); i++)
	{
		output << camioes[i]->getCapCong() << ";" << camioes[i]->getCapMax() << ";" <<
			camioes[i]->getCodigo() << endl;
	}

	output << "END_FROTA" << endl;

	//Guardar servicos e respetivos clientes

	for (unsigned int i = 0; i < this->servicos.size(); i++)
	{
		output << "SERVICO" << endl;
		output << this->servicos[i]->getId() << ";" << this->servicos[i]->getPreco() << ";" << this->servicos[i]->getStatus() << endl;

		vector <Cliente *> clientes = this->servicos[i]->getClientes();

		output << "BEGIN_CLIENTES" << endl;

		for (unsigned int j = 0; j < clientes.size(); j++)
		{
			output << clientes[j]->getNome() << endl << clientes[j]->getNif() << endl;
		}

		output << "END_CLIENTES" << endl;

	}

	output.close();


}


/*LISTA DE ERROS
 * -1 : não abriu o ficheiro com o nome dado
 * */


int Empresa::loadEmpresa()

{
	string f = this->nome;

	f = f + ".txt";

	char* ficheiro = &f[0];

	ifstream input;
	input.open(ficheiro);	//abre o ficheiro com o nome da empresa

	if (!input.is_open())	// se o ficheiro não estiver aberto, quer dizer que não existe
	{
		cout << "Nao ha ficheiro para a empresa referida." << endl;
		return -1;
	}

	string linha; // string que vai guardar o conteúdo da linha a ser lida
	string lixo; // para descartar partes desnecessárias. Ex: serparadores (";")


	// Adicionar os camiões à frota
	Frota frota;

	while (getline(input, linha) != "END_FROTA")
	{
		istringstream copia(linha);

		int codigo;
		unsigned int cap_max;
		bool cap_cong;

		if (linha == "BEGIN_FROTA")
			copia >> lixo;
		else
		{
			copia >> codigo >> lixo >> cap_max >> lixo >> cap_cong;
			Camiao* camiao = new Camiao (codigo, cap_max, cap_cong);
			frota.adicionaCamiao(camiao);
		}

	}

	this->setFrota(frota); //Atualizar a frota da empresa

	// Adicionar os serviços e os respetivos clientes
	while (getline(input, linha)) //até ao final do ficheiro
	{

		if (linha == "SERVICO")
		{
			int id;
			float preco;
			vector <Cliente*> clientes;
			bool status;

			getline (input, linha);
			istringstream copia(linha);

			copia >> id >> lixo >> preco >> lixo >> status;

			Servico* servico = new Servico (id, preco);
			this->adicionaServico(servico);
		}

		if (linha == "BEGIN_CLIENTES")
		{
			string nome;
			unsigned int nif;

			getline (input, nome);
			getline (input, linha);

			istringstream copia(linha);
			copia >> nif;
		}
	}

}



