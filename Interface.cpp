#include "Interface.h"
#include "sequentialSearch.h"

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

string nomeEmpresa;

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

		cout << "Deseja (g)erar um novo ficheiro de empresa ou (c)arregar um ja existente? ";
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

	cout << "MENU PRINCIPAL - " << nomeEmpresa << endl << endl;

	cout << "1 - Servicos" << endl;
	cout << "2 - Clientes" << endl;
	cout << "3 - Frota" << endl << endl;

	char opcao;

	cout << "Opcao: ";
	cin >> opcao;
	cin.ignore(256, '\n');
	cin.clear();

	while (opcao != '1' && opcao != '2' && opcao != '3' && opcao !='0')
	{
		cin.clear();
		cout << "Por favor digite o numero daquilo a que pretende aceder." << endl << endl;

		cout << "Opcao: ";
		cin >> opcao;
		cin.ignore(256, '\n');
		cin.clear();
	}

	switch (opcao)
	{
	case '1': mostrarServicos(empresa); break;
	case '2': mostrarClientes(empresa); break;
	case '3': mostrarFrota(empresa); break;
	case '0': return;
	}

}

/*MENU DE SERVIÇOS*/
void mostrarServicos(Empresa &empresa)
{
	clearScreen();

	cout << "Digitar 0 retorna-o ao menu principal." << endl << endl;

	empresa.printServicos();

	cout << "Pretende (e)ditar, (a)dicionar ou (r)emover um servico? ";
	char opcao;
	cin >> opcao;
	cin.ignore(256, '\n');

	while (opcao != 'e' && opcao != 'E' && opcao != 'A' && opcao != 'a' && opcao != '0' && opcao != 'r' && opcao != 'R')
	{
		cin.clear();
		cout << "Por favor, utilize as letras \"E\", \"A\" ou \"R\" para especificar a acao." << endl << endl;

		cout << "Pretende (e)ditar, (a)dicionar ou (r)emover um servico? ";
		cin >> opcao;
		cin.ignore(256, '\n');
	}

	switch (opcao)
	{
	case 'A':
	case 'a': adicionarServicos(empresa); break;
	case 'e':
	case 'E': 
		if (empresa.getServicos().size() == 0)
		{
			cout << "\nNao ha servicos para editar. Adicione um servico primeiro.\n";
			this_thread::sleep_for(std::chrono::milliseconds(2000));
			mostrarServicos(empresa);
		}
		else
			editarServicos(empresa); 
		break;
	case 'r':
	case 'R': 
		if (empresa.getServicos().size() == 0)
		{
			cout << "\nNao ha servicos para remover. Adicione um servico primeiro.\n";
			this_thread::sleep_for(std::chrono::milliseconds(2000));
			mostrarServicos(empresa);
		}
		else
			removerServicos(empresa);
		break;
	case '0': menuPrincipal(empresa); break;
	}

}

/*MENU DE EDIÇÃO DE SERVIÇOS*/
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

		cout << "Pretende mudar o (p)reco, (r)etirar ou (a)dicionar um cliente? ";
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
			
			cout << "\nEscreva o nome do novo cliente: ";
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
			if (empresa.getServicos()[index]->getClientes().size() == 0)
			{
				cout << "Este servico nao tem clientes." << endl << endl;
				this_thread::sleep_for(std::chrono::milliseconds(2000));

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
	}

	mostrarServicos(empresa);

}

/*MENU DE ADIÇÃO DE SERVIÇOS*/
void adicionarServicos(Empresa &empresa)
{
	int id;
	float preco;
	string input;

	while (1)
	{
		cout << "Preco do novo servico: ";
		getline(cin, input);

		stringstream myStream(input);
		if (myStream >> preco && preco >= 0)
			break;
		cout << "Insira um preco valido, por favor." << endl;
	}

	while (1)
	{
		cout << "ID do novo servico: ";
		getline(cin, input);

		stringstream myStream(input);
		if (myStream >> id)
			break;
		cout << "Insira um ID valido, por favor." << endl;
	}

	Servico* servico = new Servico (id, preco);

	if (sequentialSearch(empresa.getServicos(), servico) != -1)
	{
		cout << "\nJa existe um servico com esse ID. Volte a adicionar um servico com ID diferente.\n";
		this_thread::sleep_for(std::chrono::milliseconds(2000));
		adicionarServicos(empresa);
	}
	else
	{
		empresa.adicionaServico(servico);
		empresa.saveEmpresa();
		mostrarServicos(empresa);
	}
}

/*MENU DE REMOÇÃO DE SERVIÇOS*/
void removerServicos(Empresa &empresa)
{
	int id;
	string input;

	while (1)
	{
		cout << "\nID do servico a remover: ";
		getline(cin, input);

		stringstream myStream(input);
		if (myStream >> id)
			break;
		cout << "Insira um ID valido, por favor." << endl;
	}

	Servico* servico = new Servico(id, 0);

	try
	{
		empresa.retiraServico(servico);
	}

	catch (ServicoInexistente& s)
	{
		cout << "O servico com o ID " << s.getCodigo() << " nao existe. Insira um ID valido.\n";
		removerServicos(empresa);
	}

	empresa.saveEmpresa();
	mostrarServicos(empresa);

}


/*MENU DE CLIENTES*/
void mostrarClientes(Empresa &empresa)
{
	clearScreen();

	empresa.printServicos();

	int id;

	cout << endl << "ID do servico do qual pretende visualizar os clientes: ";
	cin >> id;
	cin.clear();
	cin.ignore(10000, '\n');

	int index = -1;

	for (unsigned int i = 0; i < empresa.getServicos().size(); i++)
	{
		if (empresa.getServicos()[i]->getId() == id)
			index = i;
	}

	while (index == -1)
	{
		cout << "ID inválido" << endl << endl;
		cout << endl << "ID do servico do qual pretende visualizar os clientes: ";
		cin >> id;

		for (unsigned int i = 0; i < empresa.getServicos().size(); i++)
		{
			if (empresa.getServicos()[i]->getId() == id)
				index = i;
		}
	}

	clearScreen();

	empresa.getServicos()[index]->readClientes();

	cout << "\nQuando acabar a leitura prima ENTER.";
	string lixo;
	getline(cin, lixo);
	cin.clear();

	menuPrincipal(empresa);

}

/*MENU DE FROTA*/
void mostrarFrota(Empresa &empresa)
{
	clearScreen();

	cout << "Digitar 0 retorna-o ao menu principal." << endl << endl;

	empresa.getFrota().readCamioes();

	cout << "Pretende (e)ditar, (a)dicionar ou (r)emover um camiao? ";
	char opcao;
	cin >> opcao;
	cin.ignore(256, '\n');

	while (opcao != 'e' && opcao != 'E' && opcao != 'A' && opcao != 'a' && opcao != '0' && opcao != 'r' && opcao != 'R')
	{
		cin.clear();
		cout << "Por favor, utilize as letras \"E\", \"A\" ou \"R\" para especificar a acao." << endl << endl;

		cout << "Pretende (e)ditar, (a)dicionar ou (r)emover um camiao? ";
		cin >> opcao;
		cin.ignore(256, '\n');
	}

	switch (opcao)
	{/*
	case 'A':
	case 'a': adicionarCamiao(empresa); break;
	case 'e':
	case 'E':
		if (empresa.getFrota().getCamioes.size() == 0)
		{
			cout << "\nNao ha camioes para editar. Adicione um camioes primeiro.\n";
			this_thread::sleep_for(std::chrono::milliseconds(2000));
			mostrarFrota(empresa);
		}
		else
			editarCamiao(empresa);
		break;
	case 'r':
	case 'R':
		if (empresa.getServicos().size() == 0)
		{
			cout << "\nNao ha servicos para remover. Adicione um servico primeiro.\n";
			this_thread::sleep_for(std::chrono::milliseconds(2000));
			mostrarFrota(empresa);
		}
		else
			removerCamiao(empresa);
		break;*/
	case '0': menuPrincipal(empresa); break;
	}

}