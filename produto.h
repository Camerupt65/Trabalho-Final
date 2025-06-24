#ifndef PRODUTO_H
#define PRODUTO_H

#include "constantes.h"

typedef struct produto {
	char nome[200];
	double valor;
	int estoqueDisponivel;
	int id;
} Produto;

extern Produto produtosStruct[QTD_PRODUTOS];
extern int qtdProdutosCadastrados;

void insereProduto();
void listarProdutos();
void menuEditarProduto();
void buscarProdutoMenu();
int encontraIndexDeProduto(int id);
void menuProdutoSelecionado(int id, int index);
void excluirProduto(int id, int index);
void alterarProdutoNome(int id, int index);
void alterarProdutoValor(int id, int index);
void alterarProdutoEstoque(int id, int index);

#endif