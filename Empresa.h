/*
 * Empresa.h
 *
 *  Created on: 27/10/2015
 *      Author: ASUS
 */

#ifndef SRC_EMPRESA_H_
#define SRC_EMPRESA_H_


#include "Servico.h"

using namespace std;

class Empresa
{private:
	vector <Servico*> servicos;
public:
	Empresa();
	~Empresa(){};
	vector<Servico*> getServicos() const;
	void adicionaServico(Servico *s1);
	void retiraServico (Servico *s1);//criar exceçao
	void readServicos() const;
	vector< Servico*> returnAtivos();
	vector< Servico*> returnInativos();
	void printServicos(vector< Servico*> s1); //ordenar, e ver cenas
	vector< Servico*> servicoCliente(string nome, unsigned int nif);
};




#endif /* SRC_EMPRESA_H_ */
