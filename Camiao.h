/*
 * Camiao.h
 *
 *  Created on: 27/10/2015
 *      Author: ASUS
 */

#ifndef SRC_CAMIAO_H_
#define SRC_CAMIAO_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "Servico.h"

using namespace std;

class Camiao
{private:
	int codigo;
	unsigned int cap_max;
	bool cap_cong;
	vector<Servico *> servicos;
public:
	Camiao(int codigo, unsigned int cap_max, bool cap_cong);
	~Camiao() {};
	unsigned int getCapMax() const;
	bool getCapCong() const;
	int getCodigo() const;
	void updateCodigo(int codigo);
	void updateCapMax(unsigned int cap_max);
	void updateCapCong(bool cap_cong);
	void adicionaServico(Servico *s1);
	void retiraServico(Servico* s1);
	bool operator==(const Camiao &c1);
};

class CamiaoInexistente
{
	int codigo;
public:
	int getCodigo() { return codigo; };
	CamiaoInexistente(int codigo) : codigo(codigo) {};
};




#endif /* SRC_CAMIAO_H_ */
