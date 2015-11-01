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

Servico::Servico(int id, float preco)
{
	this-> id = id;
	this-> preco = preco;
	status = false;
}

void Servico::statusServico()
{
	if(status)
		status = false;
	else
		status = true;
}

int Servico::getId() const
{
	return id;
}

bool Servico::getStatus() const
{
	return status;
}

float Servico::getPreco() const
{
	return preco;
}

void Servico::updatePreco(float preco)
{
	this -> preco = preco;
}

vector<Cliente*> Servico::getClientes() const
{
	return clientes;
}
void Servico::adicionaCliente(Cliente *j1)
{
	clientes.push_back(j1);
}

void Servico::retiraCliente(Cliente *j1)
{
	int index = sequentialSearch(clientes, j1);
	if(index == -1)
		throw ClienteInexistente(j1->getNome());
	else
		clientes.erase(clientes.begin() + index);
}

void Servico::readClientes() const
{
	for(unsigned int i = 0; i < clientes.size(); i++)
	{
		cout << clientes[i]->getNome() << " " << clientes[i]->getNif() << endl;
	}
}




