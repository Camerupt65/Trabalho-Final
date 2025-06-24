#include <stdio.h>
#include <string.h>
#include "cliente.h"
#include "menus.h"

Cliente clientesStruct[QTD_CLIENTES];
int qtdClientesCadastrados = 0;
int ultimoIdCliente = 0;


// 1 insercao
void cadastrarCliente() {
	if (qtdClientesCadastrados >= QTD_CLIENTES) {
		printf("Limite de clientes atingido.\n");
		return;
	}
	printf("Nome do cliente: ");

	limparBuffer();
	fgets(clientesStruct[qtdClientesCadastrados].nome, sizeof(clientesStruct[qtdClientesCadastrados].nome), stdin);
	clientesStruct[qtdClientesCadastrados].nome[strcspn(clientesStruct[qtdClientesCadastrados].nome, "\n")] = 0;

	printf("CPF do cliente: ");
	scanf(" %s", clientesStruct[qtdClientesCadastrados].cpf);

	printf("Email do cliente: ");
	scanf(" %s", clientesStruct[qtdClientesCadastrados].email);

	ultimoIdCliente++;
	clientesStruct[qtdClientesCadastrados].id = ultimoIdCliente;

	qtdClientesCadastrados++;
}


// 2 listagem
void listarClientes() {
	if (qtdClientesCadastrados == 0) {
		printf("Nenhum cliente cadastrado.\n");
		return;
	}
	printf("\n--------------------------");
	for (int i = 0; i < qtdClientesCadastrados; i++) {
		if (i > 0) printf("\n<><><><><><><><><><><><>");
		printf("\nID: %d | NOME: %s"
		       "\nCPF: %s"
		       "\nEMAIL: %s"
		       , clientesStruct[i].id, clientesStruct[i].nome, clientesStruct[i].cpf, clientesStruct[i].email);
	}
	printf("\n--------------------------\n");
}


// 3 menu de edicao
void menuEditarCliente() {
	int opcao;
	do {
		if (qtdClientesCadastrados == 0) return;
		mostraOpcoesClientes();
		scanf("%d", &opcao);
		switch(opcao) {
		case 1: buscarClienteMenu(); break;
		case 2: listarClientes(); break;
		case 0: printf("Voltando...\n"); break;
		default: printf("Opcao invalida.\n");
		}
	} while (opcao != 0);
}

// 3.1 busca
void buscarClienteMenu() {
	int id, index;

	printf("Digite o ID do cliente a ser editado: ");
	scanf("%d", &id);

	index = encontraIndexDeCliente(id);

	if (index == -1) {
		printf("Cliente com ID %d nao encontrado.\n", id);
	} else {
		menuClienteSelecionado(id, index);
	}
}
int encontraIndexDeCliente(int id) {
	for (int i = 0; i < qtdClientesCadastrados; i++) {
		if (clientesStruct[i].id == id) {
			return i;
		}
	}
	return -1;
}

// 3.1 menu de edicao 2
void menuClienteSelecionado(int id, int index) {
	int opcao;

	do {
		mostraOpcoesClienteSelecionado();
		scanf("%d", &opcao);

		switch (opcao) {
		case 1: excluirCliente(id, index); return;
		case 2: alterarClienteNome(id, index); break;
		case 3: alterarClienteCpf(id, index); break;
		case 4: alterarClienteEmail(id, index); break;
		case 0: printf("Voltando...\n"); break;
		default: printf("Opcao invalida.\n");
		}
	} while (opcao != 0);
}


// 3.1.1 exclusao
void excluirCliente(int id, int index) {
	for (int j = index; j < qtdClientesCadastrados - 1; j++) {
		clientesStruct[j] = clientesStruct[j + 1];
	}
	qtdClientesCadastrados--;
	printf("Cliente com ID %d excluido com sucesso.\n", id);
}


// 3.1.2 alteracao nome
void alterarClienteNome(int id, int index) {
	char novoNome[200];

	printf("Digite o novo nome: ");

	limparBuffer();
	fgets(novoNome, sizeof(novoNome), stdin);
	novoNome[strcspn(novoNome, "\n")] = 0;

	strcpy(clientesStruct[index].nome, novoNome);
	printf("Nome do cliente com ID %d alterado com sucesso!\n", id);
}


// 3.1.3 alteracao cpf
void alterarClienteCpf(int id, int index) {
	char novoCpf[14];

	printf("Digite o novo CPF: ");
	scanf(" %s", novoCpf);

	strcpy(clientesStruct[index].cpf, novoCpf);
	printf("Cpf do cliente com ID %d alterado com sucesso!\n", id);
}


// 3.1.4 alteracao email
void alterarClienteEmail(int id, int index) {
	char novoEmail[200];

	printf("Digite o novo email: ");
	scanf(" %s", novoEmail);

	strcpy(clientesStruct[index].email, novoEmail);
	printf("\nEmail do cliente com ID %d alterado com sucesso!\n", id);
}