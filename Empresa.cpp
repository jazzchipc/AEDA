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

/**
* \brief Cria uma Empresa usando os parâmetros para definir as sua caracteristicas
* \param nome Nome da Empresa
* \return Esta função não possui retorno
*/
Empresa::Empresa(string nome)
{
	this->nome = nome;
}

/**
* \brief Atribui um frota a uma Empresa
* \param frota Frota a atribuir
* \return Esta função não possui retorno
*/
void Empresa::setFrota(Frota frota)
{
	this->frota = frota;
}

/**
* \brief Obtém o vetor que guarda todos os Serviços da Empresa
* \return Retorna o vetor
*/
vector<Servico*> Empresa::getServicos() const
{
	return servicos;
}

/**
* \brief Obtém a frota da empresa
* \return Retorna o objeto Frota com a frota da empresa
*/

Frota Empresa::getFrota() const
{
	return frota;
}

/**
* \brief Adiciona um Serviço ao vetor
* \param s1 Serviço a adicionar
* \return Esta função não possui retorno
*/
void Empresa::adicionaServico(Servico *s1)
{
	servicos.push_back(s1);
}

/**
* \brief Retira um Serviço do vetor, caso este lá esteja, caso contrário lança a excessão ClienteInexistente
* \param s1 Serviço a retirar
* \return Esta função não possui retorno
*/
void Empresa::retiraServico(Servico *s1)
{
	int index = sequentialSearch(servicos, s1);
	if (index == -1)
		throw ServicoInexistente(s1->getId());
	else
		servicos.erase(servicos.begin() + index);
}

/**
* \brief Lê todas as informações dos serviços e dos clientes que usufruem deles
* \return Esta função não possui retorno
*/
void Empresa::readServicos() const
{
	for (unsigned int i = 0; i < getServicos().size(); i++)
	{
		cout << getServicos()[i]->getPreco() << endl;
		for (unsigned int j = 0; j < getServicos()[i]->getClientes().size(); j++)
		{
			cout << getServicos()[i]->getClientes()[j]->getNome() << endl;
		}
	}
}

/**
* \brief Cria um vetor com todos os serviços ativos
* \return Retorna o vetor
*/
vector< Servico*> Empresa::returnAtivos()
{
	vector< Servico*> ativos;

	for (unsigned int i = 0; i < servicos.size(); i++)
	{
		if (servicos[i]->getStatus() == true)
			ativos.push_back(servicos[i]);
	}

	return ativos;
}

/**
* \brief Cria um vetor com todos os serviços inativos
* \return Retorna o vetor
*/
vector< Servico*> Empresa::returnInativos()
{
	vector< Servico*> inativos;

	for (unsigned int i = 0; i < servicos.size(); i++)
	{
		if (servicos[i]->getStatus() == false)
			inativos.push_back(servicos[i]);
	}

	return inativos;
}

/**
* \brief Imprime todas as informações dos serviços do vetor
* \return Esta função não possui retorno
*/
void Empresa::printServicos()
{
	
	/*Algoritmo para ordenar o vetor por ordem crescente do código identificador.
	Foi feito depois do Doxygen, pelo que não é um função à parte.
	Mecanismo Bubblesort.*/

	int n = this->servicos.size();

	while (1)
	{
		bool swap = false;

		for (unsigned int i = 1; i < n; i++)
		{
			if (servicos[i - 1]->getId() > servicos[i]->getId())
			{
				iter_swap(servicos.begin() + i - 1, servicos.begin() + i);
				swap = true;
			}
		}

		n--;
		if (!swap)
			break;
	}

	cout << "SERVICOS" << endl << endl;

	cout << setw(4) << "ID" << setw(10) << "Preco (€)" << setw(9) << "Status" << endl;
	for (unsigned int i = 0; i < this->servicos.size(); i++)
	{
		cout << setw(4) << this->servicos[i]->getId() << setw(10) << this->servicos[i]->getPreco() << setw(9) << this->servicos[i]->printStatus() << endl;
	}
}

/**
* \brief Cria um vetor com todos os serviços cujo cliente identificado pelos parâmetros
* \param nome Nome do Cliente a pesquisar
* \param nif NIF do Cliente a pesquisar
* \return Retorna o vetor criado
*/
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

/**
* \brief Guarda um Empresa, e consequentemente todas as suas informações, num ficheiro a especificar
* \return Esta função não possui retorno
*/
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
		output << "END_CLIENTES" << endl;

	}

	output.close();


}


/*LISTA DE ERROS
* -1 : não abriu o ficheiro com o nome dado
* */

/**
* \brief Carrega uma Empresa criada e guardada previamente num ficheiro a especificar
* \return Retorna 0;*/
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
	char lixo; // para descartar partes desnecessárias. Ex: serparadores (";")


	// Adicionar os camiões à frota
	Frota frota;

	getline(input, linha);

	if (linha == "BEGIN_FROTA")
	{
		while (linha != "END_FROTA")
		{
			getline(input, linha);

			istringstream copia(linha);

			int codigo;
			unsigned int cap_max;
			bool cap_cong;

			copia >> codigo >> lixo >> cap_max >> lixo >> cap_cong;
			Camiao* camiao = new Camiao(codigo, cap_max, cap_cong);
			frota.adicionaCamiao(camiao);
		}
	}

	this->setFrota(frota);

	// Adicionar os serviços e os respetivos clientes

	int indice = 0;

	while (!input.eof())
	{
		getline(input, linha);

		if (linha == "SERVICO")
		{
			getline(input, linha);

			int id;
			float preco;
			vector <Cliente*> clientes;
			bool status;

			char waste;

			istringstream copia(linha);

			copia >> id >> waste >> preco >> waste >> status;

			Servico* servico = new Servico(id, preco);
			this->adicionaServico(servico);
		}

		if (linha == "BEGIN_CLIENTES")
		{
			while (1)
			{
				getline(input, linha);

				if (linha == "END_CLIENTES")
					break;
				else
				{
					string nome;
					unsigned int nif;

					nome = linha;

					getline(input, linha);

					istringstream copia(linha);
					copia >> nif;

					Cliente* cliente = new Cliente(nome, nif);
					this->servicos[indice]->adicionaCliente(cliente);
				}
			}

			indice++;
		}
	}

	input.close();

	return 0;
}



