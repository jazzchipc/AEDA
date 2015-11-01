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

using namespace std;

class Servico
{private:
	int id;
	float preco;
	vector <Cliente*> clientes;
	bool status;
public:
	Servico(int id, float preco);
	~Servico() {};
	void statusServico();
	int getId() const;
	bool getStatus() const;
	float getPreco() const;
	vector<Cliente*> getClientes() const;
	void adicionaCliente(Cliente *j1);
	void retiraCliente(Cliente *j1); //criar exceçao
	void readClientes() const;
	void updatePreco(float preco);

};

class ServicoInexistente
{
	int codigo;
public:
	int getCodigo() { return codigo; };
	ServicoInexistente(int codigo) : codigo(codigo) {};
};


#endif /* SRC_SERVICO_H_ */
