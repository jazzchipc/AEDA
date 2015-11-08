/*
 * Servico.h
 *
 *  Created on: 27/10/2015
 *      Author: ASUS
 */

#ifndef SRC_SERVICO_H_
#define SRC_SERVICO_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "Cliente.h"

using namespace std;

class Servico
{private:
	int id;
	float preco;
	float distancia;
	vector <Cliente*> clientes;
	bool status;	// status = true se o serviço está a ser usado por alguém.
					// status = false caso contrário
public:
	//Construtor
	Servico(int id, float preco, float distancia);

	//Destrutor
	~Servico() {};

	//Altera status do serviço
	void setStatus(bool status);

	//Retorna o ID do serviço
	int getId() const;

	//Retorna o status do serviço
	bool getStatus() const;
	
	//Retorna uma string com "ativo" (a ser usado por clientes) ou "inativo"
	string printStatus();

	//Retorna o preço do serviço
	float getPreco() const;

	float getDistancia() const;

	//Retorna o vetor de clientes que está a usufruir do serviço
	vector<Cliente*> getClientes() const;

	//Adiciona um cliente que tenha requisitado o serviço
	void adicionaCliente(Cliente *j1);

	//Retira um cliente que use o serviço, lançando uma exceção caso o cliente não seja encontrado
	void retiraCliente(Cliente *j1);

	//Imprime a lista de clientes que usa o serviço
	void readClientes() const;

	//Altera o preço do serviço
	void updatePreco(float preco);

	//Retorna true se dois serviços tiverem o mesmo ID
	bool operator==(const Servico& s1);

};

class ServicoInexistente
{
	int codigo;
public:
	int getCodigo() { return codigo; };
	ServicoInexistente(int codigo) : codigo(codigo) {};
};


#endif /* SRC_SERVICO_H_ */
