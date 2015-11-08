/*
* Camiao.cpp
*
*  Created on: 27/10/2015
*      Author: ASUS
*/

/*TEST*/

#include "Camiao.h"
#include "Cliente.h"
#include "Empresa.h"
#include "Frota.h"
#include "Servico.h"
#include "sequentialSearch.h"

/**
* \brief Cria um Camião usando os parâmetros para definir as sua caracteristicas
* \param codigo Codigo identificador do Camião
* \param cap_max Capacidade Máxima do Camião
* \param cap_cong Valor Lógico da Capacidade de Congelação do Camião
* \param cap_perig Valor Lógico da Capacidade de Transporte de Cargas Perigosas do Camião
* \param taxa Custo da utilização do camião por cada quilómetro percorrido (€/km)
* \return Esta função não possui retorno
*/
Camiao::Camiao(int codigo, unsigned int cap_max, bool cap_cong, bool cap_perig)
{
	this->codigo = codigo;
	this->cap_max = cap_max;
	this->cap_cong = cap_cong;
	this->cap_perig = cap_perig;
}

/**
* \brief Obtém a Capacidade Máxima de um Camião
* \return Retorna a Capacidade Máxima de um Camião
*/
unsigned int Camiao::getCapMax() const
{
	return cap_max;
}

/**
* \brief Verifica se um Camião tem ou não capacidade de congelação
* \return Retorna o valor lógico da capacidade de congelação
*/
bool Camiao::getCapCong() const
{
	return cap_cong;
}

/**
* \brief Verifica se um Camião tem ou não capacidade de transportar cargas perigosas
* \return Retorna o valor lógico da capacidade de transporte de cargas perigosas
*/
bool Camiao::getCapPerig() const
{
	return cap_perig;
}

/**
* \brief Obtém o Código identificador de um Camião
* \return Retorna o Código de um Camião
*/
int Camiao::getCodigo() const
{
	return codigo;
}

/**
* \brief Obtém os serviços para os quais um camião está a ser usado
* \return Retorna um vetor com esses serviços
*/

vector <Servico* > Camiao::getServicos() const
{
	return servicos;
}


/**
* \brief Altera, se necessário, o código de um Camião
* \param codigo Novo valor
* \return Esta função não possui retorno
*/
void Camiao::updateCodigo(int codigo)
{
	this->codigo = codigo;
}

/**
* \brief Altera, se necessário, a capacidade máxima de um Camião
* \param cap_max Novo valor
* \return Esta função não possui retorno
*/
void Camiao::updateCapMax(unsigned int cap_max)
{
	this->cap_max = cap_max;
}

/**
* \brief Altera, se necessário, o valor lógico da capacidade de congelação de um camião
* \param cap_cong Novo valor
* \return Esta função não possui retorno
*/
void Camiao::updateCapCong(bool cap_cong)
{
	this->cap_cong = cap_cong;
}
/**
* \brief Adiciona um serviço que utiliza o camião
* \param *s1 Apontador para o serviço que usa o camião
* \return Esta função não poussui retorno
*/
void Camiao::adicionaServico(Servico *s1)
{
	servicos.push_back(s1);
}

/**
* \brief Retira um serviço que utiliza o camião
* \param *s1 Apontador para o serviço a retirar
* \return Esta função não poussui retorno
*/

void Camiao::retiraServico(Servico *s1)
{
	int index = sequentialSearch(servicos, s1);
	if (index == -1)
		throw ServicoInexistente(s1->getId());
	else
		servicos.erase(servicos.begin() + index);
}

/**
* \brief Operador utilizado para verificar se dois camiões são iguais
* \param c1 Um dos camiões a comparar
* \return Retorna true se os camiões forem iguais e false se não forem
*/
bool Camiao::operator==(const Camiao &c1)
{
	if (c1.codigo == this->codigo)
		return true;
	else
		return false;
}




