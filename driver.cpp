// Trabalho de Técnicas de Programaçao e Laboratorio de Tecnicas de Programaçao.
// Alunos: Pamela Magalhaes de Queiroz e Rafael Henrique Geres.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 

using namespace std;

// estrutura das parcela(s)//
struct parcela {

	string vencimento;
	string pagamento;
	float valor;
	bool pagou;

};

//estrutura dos cliente(s)// 
struct cliente {

	string nome;
	string cpf;
	string endereco;
	string datanascimento;
	string prazoemprestimo;
	float valoremprestimo;
	vector <parcela> parcelas;

};

//funcao para cadastrar o cliente//
void cadastrocliente(vector<cliente>& clientes) {

	cliente cliente;
	cout << "nome do cliente: ";
	getline(cin, cliente.nome);
	cout << "CPF do cliente: ";
	getline(cin, cliente.cpf);
	cout << "endereco do cliente: ";
	getline(cin, cliente.endereco);
	cout << "data de nascimento: ";
	getline(cin, cliente.datanascimento);
	cout << "data do emprestimo: ";
	getline(cin, cliente.prazoemprestimo);
	cout << "valor do emprestimo ";
	cin >> cliente.valoremprestimo;
	cin.ignore(); //cin.ignore(); seria para ignorar a quebra da linha (\n)//
	clientes.push_back(cliente);
	cout << "cadastro efetivado!" << endl;

}

// funcao para visualizar o cadastro do cliente// 
void contacliente(const vector<cliente>& clientes) {

	cout << "CPF do cliente: ";
	string cpf;
	getline(cin, cpf);

	auto it = find_if(clientes.begin(), clientes.end(), // o 'auto' tem a finalidade de deduzir o tipo apropriado para a var//
		[cpf](const cliente& c) { return c.cpf == cpf; });
	if (it != clientes.end()) {

		cout << "nome: " << it->nome << endl;
		cout << "endereco: " << it->endereco << endl;
		cout << "data de nascimento: " << it->datanascimento << endl;
		cout << "data do emprestimo: " << it->prazoemprestimo << endl;
		cout << "valor total do emprestimo: " << it->valoremprestimo << endl;
		cout << "parcelas:" << endl;
		for (const auto& parcela : it->parcelas) {
			cout << "valor: " << parcela.valor << endl;
			cout << "paga: " << (parcela.pagou ? "Sim" : "Nao") << endl;
			cout << "data de pagamento: " << parcela.pagamento << endl;
			cout << "data de vencimento: " << parcela.vencimento << endl;
		}
	}
	else {
		cout << "nao ha registros desse cliente." << endl;
	}
}

//funcao para editar informacoes do cliente//
void editarcliente(vector<cliente>& clientes) {
	cout << "CPF do cliente: ";
	string cpf;
	getline(cin, cpf);

	auto it = find_if(clientes.begin(), clientes.end(),
		[cpf](const cliente& c)
		{ return c.cpf == cpf; });
	if (it != clientes.end())

	{
		cout << "nome (deixe em branco para nao alterar): ";

		string nome;

		getline(cin, nome);

		if (!nome.empty())
		{
			it->nome = nome;
		}
		cout << "endereco (deixe em branco para nao alterar): ";

		string endereco;

		getline(cin, endereco);

		if (!endereco.empty())
		{
			it->endereco = endereco;
		}
		cout << "data de nascimento (deixe em branco para nao alterar): ";

		string datanascimento;

		getline(cin, datanascimento);

		if (!datanascimento.empty())
		{
			it->datanascimento = datanascimento;
		}
		cout << "data do emprestimo (deixe em branco para nao alterar): ";

		string vencimento;

		getline(cin, vencimento);

		if (!vencimento.empty())
		{
			it->prazoemprestimo = vencimento;
		}
		cout << "valor total do emprestimo (deixe em branco para nao alterar): ";

		string valor;

		getline(cin, valor);

		if (!valor.empty())
		{
			float valoremprestimo = stof(valor); //'stof' verifica a string com o seu conteudo como float//
			it->valoremprestimo = valoremprestimo;
		}
		cout << "Informacoes do cliente atualizadas com sucesso!" << endl;
	}
	else
	{
		cout << "não há registros desse cliente." << endl;
	}
}

// funcao para cadastrar uma parcela paga//
void cadastrodeparcelapaga(vector<cliente>& clientes) {

	cout << "CPF do cliente: ";
	string CPF;
	getline(cin, CPF);

	auto it = find_if(clientes.begin(), clientes.end(),
		[CPF](const cliente& c)
		{ return c.cpf == CPF; });
	if (it != clientes.end()) {

		cout << "numero de parcela (1 a 12): ";
		int numparcela;
		cin >> numparcela;
		cin.ignore(); // ignora a quebra da linha//

		if (numparcela < 1 || numparcela > 12) { // "||" operador logico (OR), assim retornando verdadeiro //

			cout << "numero de parcela invalido." << endl;
			return;

		}

		parcela& parcela = it->parcelas[numparcela - 1];
		if (parcela.valor == 0) {

			parcela.valor = it->valoremprestimo / 12;

		}
		if (parcela.pagou) {

			cout << "parcela ja foi paga." << endl;
			return;

		}

		cout << "data do pagamento (por gentileza, neste formato (DD/MM/AAAA)): ";
		getline(cin, parcela.pagamento);
		parcela.pagou = true;
		cout << "parcela foi paga com sucesso!"

			;
	}
	else {

		cout << "nao ha registros desse cliente." << endl;

	}

}

// funcao para cadastrar um emprestimo//
void cadastroemprestimo(vector<cliente>& clientes) {

	cout << "CPF do cliente: ";
	string cpf;
	getline(cin, cpf);

	auto it = find_if(clientes.begin(), clientes.end(),
		[cpf](const cliente& c)
		{ return c.cpf == cpf; });

	if (it != clientes.end()) {

		if (!it->parcelas.empty()) {

			cout << "cliente ja possui um emprestimo em vigencia" << endl;

			return;

		}

		cout << "valor total do emprestimo: ";
		float valordoemprestimo;
		cin >> valordoemprestimo;
		cin.ignore();
		it->valoremprestimo = valordoemprestimo;

		for (int i = 0; i < 12; i++) {

			parcela parcelas;
			parcelas.valor = valordoemprestimo / 12;
			it->parcelas.push_back(parcelas);

		}

		cout << "emprestimo cadastrado com sucesso" << endl;
	}

	else {

		cout << "nao ha registros deste cliente." << endl;

	}


}

//funcao para deletar o registro do cliente //
void deletarcliente(vector<cliente>& clientes) {

	cout << "CPF do cliente: ";
	string cpf;
	getline(cin, cpf);
	auto it = find_if(clientes.begin(), clientes.end(),
		[cpf](const cliente& c)
		{ return c.cpf == cpf; });
	if (it != clientes.end()) {

		clientes.erase(it);
		cout << "registro do cliente excluido com sucesso." << endl;

	}
	else
	{

		cout << "nao ha registros deste cliente." << endl;

	}

}

int main()
{
	vector<cliente> clientes;
	int opcao = 0;
	while (opcao != 7)

	{
		cout << "Selecione uma opcao:" << endl;
		cout << "1. Cadastrar cliente" << endl;
		cout << "2. Visualizar as informacoes de um cliente" << endl;
		cout << "3. Editar as informacoes de um cliente" << endl;
		cout << "4. Cadastrar parcela paga" << endl;
		cout << "5. Cadastrar emprestimo" << endl;
		cout << "6. Excluir cliente" << endl;
		cout << "7. Sair" << endl;
		cout << "Opcao: ";
		cin >> opcao;
		cin.ignore();

		switch (opcao)
		{
		case 1:
			cadastrocliente(clientes);
			break;
		case 2:
			contacliente(clientes);
			break;
		case 3:
			editarcliente(clientes);
			break;
		case 4:
			cadastrodeparcelapaga(clientes);
			break;
		case 5:
			cadastroemprestimo(clientes);
			break;
		case 6:
			deletarcliente(clientes);
			break;
		case 7:
			cout << "Saindo do programa..." << endl;
			break;
		default:
			cout << "Opcao invalida." << endl;
		}
	}
}

