/*
 * Frota.h
 *
 *  Created on: 27/10/2015
 *      Author: ASUS
 */

#ifndef SRC_FROTA_H_
#define SRC_FROTA_H_

#include "Camiao.h"
#include <vector>

using namespace std;

class Frota
{private:
	vector <Camiao*> camioes;
public:
	Frota();
	~Frota() {};
	void adicionaCamiao(Camiao *c1);
	void retiraCamiao(Camiao *c1);//criar exceçao
	void readCamioes() const;
	vector <Camiao*> getCamioes();

};


#endif /* SRC_FROTA_H_ */
