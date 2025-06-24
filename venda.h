#ifndef VENDA_H
#define VENDA_H

typedef struct produtoVenda {
	int idProduto;
	int quantidade;
} ProdutoVenda;

typedef struct venda {
	int idNotaFiscal;
	int idCliente;
	ProdutoVenda produtos[QTD_LIMITE_VENDAS];
	float valorTotal;
	int numDeProdutosDiferentesComprados;
} Venda;

extern Venda venda[QTD_VENDAS];

void gerarVendaNova();
int verificarPossibilidadeDeVenda();
int solicitarIdCliente();
Venda criarNovaVenda(int idCliente);
void salvarVenda(Venda novaVenda);
void listarVendas();
void menuEditarVenda();
void buscarVendaMenu();
void menuVendaSelecionada(int id, int index);
void excluirVendaPorIndex(int id, int index);
void reporEstoqueDaVenda(int index);
void alterarClienteDaVenda(int id, int index);
void removerProdutoDaVenda(int id, int index);

#endif