/*
* Servico.cpp
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
* \brief Cria um Serviço usando os parâmetros para definir as sua caracteristicas
* \param id ID do Serviço
* \param preco Preço do Serviço em custo por quilograma de carga (€/kg)
* \param distancia Distância que o camião vai percorrer durante o serviço (km)
* \return Esta função não possui retorno
*/
Servico::Servico(int id, float preco, float distancia)
{
	this->id = id;
	this->preco = preco;
	this->distancia = distancia;
	status = false;
}

/**
* \brief Atribui um status a um Serviço, ativo(true) ou inativo(false)
* \param status Status a atribuir
* \return Esta função não possui retorno
*/
void Servico::setStatus(bool status)
{
	this->status = status;
}

/**
* \brief Obtém o ID de um Serviço
* \return Retorna o ID de um Serviço
*/
int Servico::getId() const
{
	return id;
}

/**
* \brief Verifica se um Serviço está ou não ativo
* \return Retorna o valor lógico do status
*/
bool Servico::getStatus() const
{
	return status;
}

/**
* \brief Averigua o valor lógico do status
* \return Retorna o status de um Serviço, ativo ou inativo
*/
string Servico::printStatus()
{
	if (this->status)
		return "Ativo";
	else
		return "Inativo";
}

/**
* \brief Obtém o Preço de um Serviço
* \return Retorna o Preço de um Serviço
*/
float Servico::getPreco() const
{
	return preco;
}

/**
* \brief Altera, se necessário, o preço de um Serviço
* \param preco Novo valor (em €/kg) do serviço
* \return Esta função não possui retorno
*/
void Servico::updatePreco(float preco)
{
	this->preco = preco;
}

/**
* \brief Obtém o vetor que guarda todos os Clientes
* \return Retorna o vetor
*/
vector<Cliente*> Servico::getClientes() const
{
	return clientes;
}

/**
* \brief Obtém a distância necessária para executar o serviço
* \return Retorna o valor em km
*/
float Servico::getDistancia() const
{
	return distancia;
}

/**
* \brief Adiciona um Cliente ao vetor
* \param j1 Cliente a adicionar
* \return Esta função não possui retorno
*/
void Servico::adicionaCliente(Cliente *j1)
{
	clientes.push_back(j1);

	this->setStatus(true);
}

/**
* \brief Retira um Cliente do vetor, caso este lá esteja, caso contrário lança a excessão ClienteInexistente
* \param j1 Cliente a retirar
* \return Esta função não possui retorno
*/
void Servico::retiraCliente(Cliente *j1)
{
	int index = sequentialSearch(clientes, j1);
	if (index == -1)
		throw ClienteInexistente(j1->getNif());
	else
		clientes.erase(clientes.begin() + index);

	if (this->clientes.size() == 0)
		this->setStatus(false);
}

/**
* \brief Imprime todas as informações dos clientes do vetor
* \return Esta função não possui retorno
*/
void Servico::readClientes() const
{
	cout << setw(20) << "Nome" << setw(15) << "NIF" << endl;
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		cout << setw(20) << clientes[i]->getNome() << setw(15) << clientes[i]->getNif() << endl;
	}
}

/**
* \brief Operador utilizado para verificar se dois serviços são iguais
* \param s1 Serviço a comparar
* \return Retorna true se os Serviços forem iguais e false se não forem
*/
bool Servico::operator==(const Servico& s1)
{
	if (s1.id == this->id)
		return true;
	else
		return false;
}







