#include "Interface.h"
#include <cstdlib>


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
  \_/_|  \__,_|_| |_|___/ .__/ \___/|_|   \__\___/_/\_\
                        | |                            
                        |_|                  
)EOF");
}

Empresa firstScreen()
{
	printTitulo();

	cout << endl << endl;

	char modo;

	cout << "Deseja (g)erar um novo ficheiro de empresa ou (c)arregar um já existente? ";
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

	cout << "Acabou de ser gerado um ficheiro para a sua empresa com o título <nomeDaEmpresa>.txt" << endl << endl;

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
	case '1': editarServicos(empresa); break;
	case '2': editarClientes(empresa); break;
	case '3': editarFrota(empresa); break;
	}

}

void editarServicos(Empresa &empresa)
{
	empresa.printServicos();

	int id;

	cout << endl << "ID do servico a editar: ";
	cin >> id;

	for (unsigned int i = 0; i < empresa.getServicos.size(); i++)
	{
		if ()
	}

}