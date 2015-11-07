#include "Interface.h"
#include <cstdlib>
#include <chrono>
#include <thread>
#include <sstream>

void clearScreen()
{
#ifdef _WIN32	
	system("cls");
#else
	// Assume POSIX
	system("clear");
#endif
}

void printTitulo()

{
	printf(R"EOF(
 _____                                    _            
|_   _|                                  | |           
  | |_ __ __ _ _ __  ___ _ __   ___  _ __| |_ _____  __
  | | '__/ _` | '_ \/ __| '_ \ / _ \| '__| __/ _ \ \/ /
  | | | | (_| | | | \__ \ |_) | (_) | |  | ||  __/>  < 
  \_/_|  \__,_|_| |_|___/ .__/ \___/|_|   \__\___/_/\_\ 1.0.0
                        | |                            
                        |_|                  
)EOF");
}

Empresa firstScreen()
{
	printTitulo();

	cout << endl << endl;

	char modo;

	cout << "Deseja (g)erar um novo ficheiro de empresa ou (c)arregar um ja existente? ";
	cin >> modo;
	cin.ignore(256, '\n');

	while (modo != 'g' && modo != 'G' && modo != 'c' && modo != 'C')
	{
		cin.clear();
		cout << "Se quiser gerar um ficheiro digite \"g\", se quiser carregar digite \"c\"" << endl << endl;

		cout << "Deseja (g)erar um novo ficheiro de empresa ou (c)arregar um já existente? ";
		cin.get(modo);
		cin.ignore(256, '\n');
	}

	switch (modo)
	{
	case 'g':
	case 'G':	return gerar(); break;
	case 'c':
	case 'C':	return carregar(); break;
	}

}

Empresa gerar()
{
	clearScreen();

	cout << "GERAR FICHEIRO DE EMPRESA" << endl << endl;

	string nomeEmpresa;

	cout << "Nome da empresa: ";
	getline(cin, nomeEmpresa);
	cout << endl << endl;

	Empresa empresa(nomeEmpresa);

	empresa.saveEmpresa();

	cout << "Acabou de ser gerado um ficheiro para a sua empresa com o titulo" << nomeEmpresa << ".txt" << endl << endl;

	return empresa;

}

Empresa carregar()
{
	clearScreen();

	cout << "CARREGAR FICHEIRO DE EMPRESA" << endl << endl;

	string nomeEmpresa;

	cout << "Nome da empresa: ";
	getline(cin, nomeEmpresa);
	cout << endl << endl;

	Empresa empresa(nomeEmpresa);

	empresa.loadEmpresa();

	return empresa;
}

void menuPrincipal(Empresa &empresa)
{
	clearScreen();

	cout << "Digitar 0 termina o programa." << endl << endl;

	cout << "MENU PRINCIPAL" << endl << endl;

	cout << "1 - Servicos" << endl;
	cout << "2 - Clientes" << endl;
	cout << "3 - Frota" << endl << endl;

	char opcao;

	cout << "Opcao: ";
	cin >> opcao;
	cin.ignore(256, '\n');

	while (opcao != '1' && opcao != '2' && opcao != '3')
	{
		cin.clear();
		cout << "Por favor digite o numero daquilo a que pretende aceder." << endl << endl;

		cout << "Opcao: ";
		cin >> opcao;
		cin.ignore(256, '\n');
	}

	switch (opcao)
	{
	case '1': mostrarServicos(empresa); break;
	//case '2': editarClientes(empresa); break;
	//case '3': editarFrota(empresa); break;
	case '0': return;
	}

}

/*MENU DE SERVIÇOS*/

void mostrarServicos(Empresa &empresa)
{
	clearScreen();

	cout << "Digitar 0 retorna-o ao menu principal." << endl << endl;

	empresa.printServicos();

	cout << "Pretende (e)ditar ou (a)dicionar um servico? ";
	char opcao;
	cin >> opcao;
	cin.ignore(256, '\n');

	while (opcao != 'e' && opcao != 'E' && opcao != 'A' && opcao != 'a' && opcao != '0' && opcao != 'r' && opcao != 'R')
	{
		cin.clear();
		cout << "Por favor, utilize as letras \"A\" ou \"E\" para especificar a acao." << endl << endl;

		cout << "Pretende (e)ditar, (a)dicionar ou (r)emover um servico? ";
		cin >> opcao;
		cin.ignore(256, '\n');
	}

	switch (opcao)
	{
	case 'A':
	//case 'a': adicionarServicos(empresa); break;
	case 'e':
	case 'E': editarServicos(empresa); break;
	case 'r':
	// case 'R': removerServicos(empresa); break;
	case '0': menuPrincipal(empresa); break;
	}

}

void editarServicos(Empresa &empresa)
{
	int id;

	cout << endl << "ID do servico a editar: ";
	cin >> id;

	int index = -1;

	for (unsigned int i = 0; i < empresa.getServicos().size(); i++)
	{
		if (empresa.getServicos()[i]->getId() == id)
			index = i;
	}

	while (index == -1)
	{
		cout << "ID inválido" << endl << endl;
		cout << endl << "ID do servico a editar: ";
		cin >> id;

		for (unsigned int i = 0; i < empresa.getServicos().size(); i++)
		{
			if (empresa.getServicos()[i]->getId() == id)
				index = i;
		}
	}

	char opcao;

	cout << "Pretende mudar o (p)reco, (r)etirar ou (a)dicionar um cliente? ";
	cin >> opcao;
	cin.ignore(256, '\n');

	while (opcao != 'p' && opcao != 'P' && opcao != 'r' && opcao != 'R' && opcao != 'a' && opcao != 'A' && opcao != '0')
	{
		cin.clear();
		cout << "Por favor, utilize as letras \"P\", \"R\" ou \"A\" para especificar a acao." << endl << endl;

		cout << "Pretende (e)ditar ou (a)dicionar um servico? ";
		cin >> opcao;
		cin.ignore(256, '\n');
	}

	if (opcao == '0')
		mostrarServicos(empresa);

	/*EDITAR SERVIÇO (mudar preço ou adicionar)*/
	if (opcao == 'P' || opcao == 'p')
	{
		float novoPreco;

		cout << endl << endl << "Novo preco do servico " << id << ": ";
		cin >> novoPreco;

		while (novoPreco < 0)
		{
			cout << "Preco invalido. Por favor escolha um valor nulo ou positivo." << endl << endl;
			cout << "Novo preco do servico " << id << ": ";
			cin >> novoPreco;
		}

		empresa.getServicos()[index]->updatePreco(novoPreco);

		empresa.saveEmpresa();
	}

	else
	{
		if (opcao == 'a' || opcao == 'A')
		{
			string nome;
			
			cout << "Escreva o nome do novo cliente: ";
			getline(cin, nome);

			string input;
			int nif;

			while (1)
			{
				cout << "Insira o NIF do novo cliente: ";
				getline(cin, input);

				stringstream myStream(input);
				if (myStream >> nif)
					break;
				cout << "Insira um NIF valido, por favor." << endl;
			}

			Cliente* clienteAAdicionar = new Cliente(nome, nif);

			empresa.getServicos()[index]->adicionaCliente(clienteAAdicionar);

			empresa.saveEmpresa();
		}

		else
		{
			cout << "LISTA DE CLIENTES" << endl << endl;
			empresa.getServicos()[index]->readClientes();

			string input;
			int nif;

			while (1) 
			{
				cout << "Insira o NIF do cliente a remover: ";
				getline(cin, input);

				stringstream myStream(input);
				if (myStream >> nif)
					break;
				cout << "Insira um NIF valido, por favor." << endl;
			}

			Cliente* clienteARemover = new Cliente("", nif);

			empresa.getServicos()[index]->retiraCliente(clienteARemover);

			empresa.saveEmpresa();

		}
	}

	mostrarServicos(empresa);

}

void adicionarServicos(Empresa &empresa)
{

}