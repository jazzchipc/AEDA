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

using namespace std;

class Camiao
{private:
	int codigo;
	unsigned int cap_max;
	bool cap_cong;
public:
	Camiao(int codigo, unsigned int cap_max, bool cap_cong);
	~Camiao() {};
	unsigned int getCapMax() const;
	bool getCapCong() const;
	int getCodigo() const;
	void updateCodigo(int codigo);
	void updateCapMax(unsigned int cap_max);
	void updateCapCong(bool cap_cong);
};

class CamiaoInexistente
{
	int codigo;
public:
	int getCodigo() { return codigo; };
	CamiaoInexistente(int codigo) : codigo(codigo) {};
};




#endif /* SRC_CAMIAO_H_ */
