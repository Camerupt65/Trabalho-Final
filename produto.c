#include <stdio.h>
#include <string.h>
#include "produto.h"
#include "menus.h"

Produto produtosStruct[QTD_PRODUTOS];
int qtdProdutosCadastrados = 0;
int ultimoIdProduto = 0;


// 4 insercao
void insereProduto() {
	if (qtdProdutosCadastrados >= QTD_PRODUTOS) {
		printf("Limite de produtos atingido.\n");
		return;
	}
	printf("Nome do produto: ");
	
	limparBuffer();
	fgets(produtosStruct[qtdProdutosCadastrados].nome, sizeof(produtosStruct[qtdProdutosCadastrados].nome), stdin);
	produtosStruct[qtdProdutosCadastrados].nome[strcspn(produtosStruct[qtdProdutosCadastrados].nome, "\n")] = 0;

	printf("Valor do produto: ");
	scanf(" %lf", &produtosStruct[qtdProdutosCadastrados].valor);

	printf("Estoque do produto: ");
	scanf(" %d", &produtosStruct[qtdProdutosCadastrados].estoqueDisponivel);

	ultimoIdProduto++;
	produtosStruct[qtdProdutosCadastrados].id = ultimoIdProduto;

	qtdProdutosCadastrados++;
}


// 5 listagem
void listarProdutos() {
	if (qtdProdutosCadastrados == 0) {
		printf("Nenhum produto cadastrado.\n");
		return;
	}
	printf("\n--------------------------");
	for (int i = 0; i < qtdProdutosCadastrados; i++) {
		if (i > 0) printf("\n<><><><><><><><><><><><>");
		printf("\nID: %d | NOME: %s"
		       "\nVALOR: R$%.2lf"
		       "\nESTOQUE DISPONIVEL: %d"
		       , produtosStruct[i].id, produtosStruct[i].nome, produtosStruct[i].valor, produtosStruct[i].estoqueDisponivel);
	}
	printf("\n--------------------------\n");
}


// 6 menu de edicao
void menuEditarProduto() {
	int opcao;
	do {
		if(qtdProdutosCadastrados == 0) return;
		mostraOpcoesProdutos();
		scanf("%d", &opcao);
		switch(opcao) {
		case 1: buscarProdutoMenu(); break;
		case 2: listarProdutos(); break;
		case 0: printf("Voltando...\n"); break;
		default: printf("Opcao invalida.\n");
		}
	} while (opcao != 0);
}

// 6.1 busca
void buscarProdutoMenu() {
	int id, index;

	printf("Digite o ID do produto a ser editado: ");
	scanf("%d", &id);

	index = encontraIndexDeProduto(id);

	if (index == -1) {
		printf("Produto com ID %d nao encontrado.\n", id);
	} else {
		menuProdutoSelecionado(id, index);
	}
}
int encontraIndexDeProduto(int id) {
	for (int i = 0; i < qtdProdutosCadastrados; i++) {
		if (produtosStruct[i].id == id) {
			return i;
		}
	}
	return -1;
}

// 6.1 menu de edicao 2
void menuProdutoSelecionado(int id, int index) {
	int opcao;

	do {
		mostraOpcoesProdutoSelecionado();
		scanf("%d", &opcao);

		switch (opcao) {
		case 1: excluirProduto(id, index); return;
		case 2: alterarProdutoNome(id, index); break;
		case 3: alterarProdutoValor(id, index); break;
		case 4: alterarProdutoEstoque(id, index); break;
		case 0: printf("Voltando...\n"); break;
		default: printf("Opcao invalida.\n");
		}
	} while (opcao != 0);
}


// 6.1.1 exclusao
void excluirProduto(int id, int index) {
	for (int j = index; j < qtdProdutosCadastrados - 1; j++) {
		produtosStruct[j] = produtosStruct[j + 1];
	}
	qtdProdutosCadastrados--;
	printf("Produto com ID %d excluido com sucesso.\n", id);
}


// 6.1.2 alteracao nome
void alterarProdutoNome(int id, int index) {
	char novoNome[200];
	
	printf("Digite o novo nome: ");
	
    limparBuffer();
	fgets(novoNome, sizeof(novoNome), stdin);
    novoNome[strcspn(novoNome, "\n")] = 0;
    
	strcpy(produtosStruct[index].nome, novoNome);
	printf("Nome do produto com ID %d alterado com sucesso!\n", id);
}


// 6.1.3 alteracao valor
void alterarProdutoValor(int id, int index) {
	double novoValor;
	
	printf("Digite o novo valor: ");
	scanf(" %lf", &novoValor);
	
	produtosStruct[index].valor = novoValor;
	printf("Valor do produto com ID %d alterado com sucesso!\n", id);
}


// 6.1.4 alteracao estoque
void alterarProdutoEstoque(int id, int index) {
	int novoEstoque;
	
	printf("Digite o novo estoque: ");
	scanf(" %d", &novoEstoque);
	
	produtosStruct[index].estoqueDisponivel = novoEstoque;
	printf("Estoque do produto com ID %d alterado com sucesso!\n", id);
}