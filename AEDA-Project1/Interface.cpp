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

void primaEnter()
{
	string enter;
	cout << endl << "Prima ENTER para continuar." << endl;
	getline(cin, enter);
}

// DESCOMENTAR SE ESTIVER EM VISUAL STUDIO
/*void printTitulo()

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
}*/

string nomeEmpresa;

Empresa firstScreen()
{
	cout << "Transportex 1.0.0" << endl;

	// DESCOMENTAR SE ESTIVER EM VISUAL STUDIO 
	// printTitulo();

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
	default: break;
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

	string input;
	float custoDist, custoCong, custoPerig;

	while (1)
	{
		cout << "Taxa que a empresa vai cobrar por cada km perocrrido: ";
		getline(cin, input);
		cout << endl;

		stringstream myStream(input);
		if (myStream >> custoDist && custoDist >= 0)
			break;
		cout << "Insira uma taxa válida" << endl;
	}

	while (1)
	{
		cout << "Preco extra por capacidade de congelacao: ";
		getline(cin, input);
		cout << endl;

		stringstream myStream(input);
		if (myStream >> custoCong && custoCong >= 0)
			break;
		cout << "Insira um custo valido." << endl;
	}

	while (1)
	{
		cout << "Preco extra por capacidade de transporte de carga perigosa: ";
		getline(cin, input);
		cout << endl;

		stringstream myStream(input);
		if (myStream >> custoPerig && custoPerig >= 0)
			break;
		cout << "Insira um custo valido." << endl;
	}

	empresa.setCustoCong(custoCong);
	empresa.setCustoPerig(custoPerig);
	empresa.setCustoDist(custoDist);

	empresa.saveEmpresa();
	
	cout << "Acabou de ser gerado um ficheiro para a sua empresa com o titulo: " << nomeEmpresa << ".txt" << endl << endl;

	//this_thread::sleep_for(std::chrono::seconds(2));
	primaEnter();

	return empresa;

}

Empresa carregar()
{
	clearScreen();

	std::cout << "CARREGAR FICHEIRO DE EMPRESA" << endl << endl;

	std::cout << "Nome da empresa: ";
	std::getline(std::cin, nomeEmpresa);
	std::cout << endl << endl;

	Empresa empresa(nomeEmpresa);

	if (empresa.loadEmpresa() == -1)
	{
		std::cout << "Nao ha nenhum ficheiro para essa empresa. Por favor crie um.\n";
		//this_thread::sleep_for(std::chrono::seconds(2));
		primaEnter();
		clearScreen();
		firstScreen();
	}

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
			//this_thread::sleep_for(std::chrono::milliseconds(2000));
			primaEnter();
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
			//this_thread::sleep_for(std::chrono::milliseconds(2000));
			primaEnter();
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
				//this_thread::sleep_for(std::chrono::milliseconds(2000));
				primaEnter();

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
	float preco, distancia;
	string input;

	while (1)
	{
		cout << "Preco do novo servico por kq de carga: ";
		getline(cin, input);

		stringstream myStream(input);
		if (myStream >> preco && preco >= 0)
			break;
		cout << "Insira um preco valido, por favor." << endl;
	}

	while (1)
	{
		cout << "Distancia a percorrer no servico: ";
		getline(cin, input);

		stringstream myStream(input);
		if (myStream >> distancia && distancia >= 0)
			break;
		cout << "Insira uma distancia, por favor." << endl;
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

	Servico* servico = new Servico (id, preco, distancia);

	if (sequentialSearch(empresa.getServicos(), servico) != -1)
	{
		cout << "\nJa existe um servico com esse ID. Volte a adicionar um servico com ID diferente.\n";
		//this_thread::sleep_for(std::chrono::milliseconds(2000));
		primaEnter();
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

	Servico* servico = new Servico(id, 0, 0);

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

	if (empresa.getServicos().size() == 0)
	{
		cout << "Nao ha servicos disponiveis para mostrar clientes." << endl << "Crie primeiro um servico e adicione um cliente." << endl;
		//this_thread::sleep_for(std::chrono::seconds(2));
		primaEnter();
		menuPrincipal(empresa);
	}

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

	cout << "Taxa por km percorrido: " << empresa.getCustoDist() << " euros" << endl;
	cout << "Custo extra por transporte de carga congelada: " << empresa.getCustoCong() << " euros" << endl;
	cout << "Custo extra por transporte de cargas perigosas: " << empresa.getCustoPerig() << " euros" << endl << endl;

	empresa.getFrota().readCamioes();

	vector <Camiao* > camioesFrota = empresa.getFrota().getCamioes();

	cout << "\n\nServicos e precos respetivos: " << endl;

	for (unsigned int i = 0; i < camioesFrota.size(); i++)
	{
		cout << camioesFrota[i]->getCodigo() << ": ";

		for (unsigned int j = 0; j < camioesFrota[i]->getServicos().size(); j++)
		{
			float custo = 0;
			Servico* servico = camioesFrota[i]->getServicos()[j];

			custo = custo + servico->getPreco() * camioesFrota[i]->getCapMax();
			custo = custo + servico->getDistancia() * empresa.getCustoDist();
			
			if (camioesFrota[i]->getCapCong())
				custo = custo + empresa.getCustoCong();
			if (camioesFrota[i]->getCapPerig())
				custo = custo + empresa.getCustoPerig();

			cout << camioesFrota[i]->getServicos()[j]->getId() << " ---> " << custo <<endl;
		}

		cout << endl;
	}

	cout << endl << "Pretende (e)ditar os servicos, (a)dicionar ou (r)emover um camiao? ";
	char opcao;
	cin >> opcao;
	cin.ignore(256, '\n');

	while (opcao != 'e' && opcao != 'E' && opcao != 'A' && opcao != 'a' && opcao != '0' && opcao != 'r' && opcao != 'R')
	{
		cin.clear();
		cout << "Por favor, utilize as letras \"E\", \"A\" ou \"R\" para especificar a acao." << endl << endl;

		cout << "Pretende (e)ditar os servicos, (a)dicionar ou (r)emover um camiao? ";
		cin >> opcao;
		cin.ignore(256, '\n');
	}

	switch (opcao)
	{
	case 'A':
	case 'a': adicionarCamiao(empresa); break;
	case 'e':
	case 'E':
		if (empresa.getFrota().getCamioes().size() == 0)
		{
			cout << "\nNao ha camioes para editar. Adicione um camioes primeiro.\n";
			//this_thread::sleep_for(std::chrono::milliseconds(2000));
			primaEnter();
			mostrarFrota(empresa);
		}
		else
			editarCamiao(empresa);
		break;
	case 'r':
	case 'R':
			removerCamiao(empresa);
		break;
	case '0': menuPrincipal(empresa); break;
	}

}

/*MENU DE ADIÇÃO DE CAMIÕES*/
void adicionarCamiao(Empresa &empresa)
{
	int codigo;
	unsigned int capMax;
	bool capCong, capPerig;

	string input;

	while (1)
	{
		cout << "Codigo do novo camiao: ";
		getline(cin, input);

		stringstream myStream(input);
		if (myStream >> codigo)
			break;
		cout << "Insira um codigo valido, por favor." << endl;
	}

	while (1)
	{
		cout << "Carga maxima do novo camiao: ";
		getline(cin, input);

		stringstream myStream(input);
		if (myStream >> capMax && capMax >= 0)
			break;
		cout << "Insira um valor valido, por favor." << endl;
	}

	while (1)
	{
		cout << "O camiao tem funcao congeladora? (1: true/0: false): ";
		getline(cin, input);

		stringstream myStream(input);
		if (myStream >> capCong)
			break;
		cout << "Utilize um bool: true ou false." << endl;
	}

	while (1)
	{
		cout << "O camiao pode transportar cargas perigosas? (1: true/0: false): ";
		getline(cin, input);

		stringstream myStream(input);
		if (myStream >> capPerig)
			break;
		cout << "Utilize um bool: true ou false." << endl;
	}

	Camiao* camiao = new Camiao(codigo, capMax, capCong, capPerig);

	if (sequentialSearch(empresa.getFrota().getCamioes(), camiao) != -1)
	{
		cout << "\nJa existe um camiao com esse codigo. Volte a adicionar um camiao com codigo diferente.\n";
		//this_thread::sleep_for(std::chrono::milliseconds(2000));
		primaEnter();
		adicionarServicos(empresa);
	}
	else
	{
		Frota frota (empresa.getFrota());
		frota.adicionaCamiao(camiao);

		empresa.setFrota(frota);
		empresa.saveEmpresa();
		mostrarFrota(empresa);
	}
}

/*MENU DE EDIÇÃO DE CAMIÕES*/
void editarCamiao(Empresa &empresa)
{
	string input;

	int codigo;

	while (1)
	{
		cout << "Codigo do camiao que pretende editar: ";
		getline(cin, input);

		stringstream myStream(input);
		if (myStream >> codigo)
			break;
		cout << "Insira um codigo valido, por favor." << endl;
	}

	Camiao* c1 = new Camiao (codigo, 0, 0, 0);

	while (sequentialSearch(empresa.getFrota().getCamioes(), c1) == -1) // se não encontra
	{
		cout << "Codigo de camiao nao encontrado." << endl;
		while (1)
		{
			cout << "Codigo do camiao que pretende editar: ";
			getline(cin, input);

			stringstream myStream(input);
			if (myStream >> codigo)
				break;
			cout << "Insira um codigo valido, por favor." << endl;
		}
	}


	c1 = empresa.getFrota().getCamioes()[sequentialSearch(empresa.getFrota().getCamioes(), c1)];

	cout << endl << endl << "CAMIAO - " << c1->getCodigo() << endl << endl;

	cout << setw(10) << "Codigo" << setw(12) << "N Clientes" << endl;

	for (unsigned int i = 0; i < c1->getServicos().size(); i++)
	{
		cout << setw(10) << c1->getServicos()[i]->getId() << setw(12) << c1->getServicos()[i]->getClientes().size() << endl;
	}

	int id;

	empresa.printServicos();

	while (1)
	{
		cout << "ID do servico que pretende adicionar/remover: ";
		getline(cin, input);

		stringstream myStream(input);
		if (myStream >> id)
			break;
		cout << "Insira um ID valido, por favor." << endl;
	}

	Servico* s1 = new Servico(id, 0, 0);

	int index = sequentialSearch(empresa.getServicos(), s1);

	while (index == -1) // se não encontra
	{
		cout << "Esse servico nao existe." << endl;
		while (1)
		{
			cout << "ID do servico que pretende alterar: ";
			getline(cin, input);

			stringstream myStream(input);
			if (myStream >> id)
				break;
			cout << "Insira um ID valido, por favor." << endl;
		}

		int index = sequentialSearch(empresa.getServicos(), s1);
	}

	char opcao;

	while (1)
	{
		cout << endl << "Pretende (r)emover ou (a)dicionar o servico? ";
		getline(cin, input);

		stringstream myStream(input);
		if (myStream >> opcao && (opcao == 'r' || opcao == 'R' || opcao == 'a' || opcao == 'A'))
			break;
		cout << "Insira uma opcao valida, por favor." << endl;
	}

	switch (opcao)
	{
	case 'r':
	case 'R':  c1->retiraServico(empresa.getServicos()[index]); break;
	case 'a':
	case 'A': c1->adicionaServico(empresa.getServicos()[index]); break;
	}

	empresa.saveEmpresa();
	mostrarFrota(empresa);
}

void removerCamiao(Empresa &empresa)
{
	string input;

	int codigo;

	while (1)
	{
		cout << "Codigo do camiao a remover: ";
		getline(cin, input);

		stringstream myStream(input);
		if (myStream >> codigo)
			break;
		cout << "Insira um codigo valido, por favor." << endl;
	}

	Camiao* c1 = new Camiao(codigo, 0, 0, 0);

	if (sequentialSearch(empresa.getFrota().getCamioes(), c1) == -1)
	{
		cout << "Nao ha nenhum camiao com esse ID. Tente um ID novo." << endl;
		removerCamiao(empresa);
	}

	else
	{
		empresa.getFrota().retiraCamiao(empresa.getFrota().getCamioes()[sequentialSearch(empresa.getFrota().getCamioes(), c1)]);
	}

	empresa.saveEmpresa();
	mostrarFrota(empresa);
}