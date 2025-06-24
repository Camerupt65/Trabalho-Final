#include <stdio.h>
#include <string.h>
#include "cliente.h"
#include "produto.h"
#include "venda.h"
#include "menus.h"

int ultimoIdVendaCadastrada = 0;
int qtdVendasCadastradas = 0;

Venda venda[QTD_VENDAS];
ProdutoVenda produtoVenda;


// 7 insercao
void gerarVendaNova() {
	if (!verificarPossibilidadeDeVenda()) return;

	int idClienteSelecionado = solicitarIdCliente();
	if (idClienteSelecionado == -1) return;

	Venda novaVenda = criarNovaVenda(idClienteSelecionado);

	if (novaVenda.numDeProdutosDiferentesComprados == 0) {
		printf("Nenhum produto adicionado. Venda cancelada.\n");
		return;
	}

	salvarVenda(novaVenda);
	printf("\nVenda cadastrada com sucesso.\nTotal: R$ %.2f\n", novaVenda.valorTotal);
}
// codigo para cadastrar venda nova separado em funcoes
// verifica se e possivel cadastrar uma nova venda (limites e se existem clientes e produtos)
int verificarPossibilidadeDeVenda() {
	if (qtdVendasCadastradas >= QTD_VENDAS) {
		printf("\nLimite de vendas atingido.\n");
		return 0;
	}
	if (qtdClientesCadastrados == 0) {
		printf("\nNenhum cliente cadastrado para realizar a compra.\n");
		return 0;
	}
	if (qtdProdutosCadastrados == 0) {
		printf("\nNenhum produto cadastrado para realizar a compra.\n");
		return 0;
	}
	return 1;
}
// solicita o id do cliente que vai realizar a compra
int solicitarIdCliente() {
	int idClienteSelecionado;
	listarClientes();
	printf("\nDigite o ID do cliente: ");
	scanf("%d", &idClienteSelecionado);

	int indexCliente = encontraIndexDeCliente(idClienteSelecionado);

	if (indexCliente == -1) {
		printf("\nCliente com ID %d nao encontrado.\n", idClienteSelecionado);
		return -1;
	}

	return idClienteSelecionado;
}
// realiza todo o processo para armazenar as informacoes da venda
Venda criarNovaVenda(int idCliente) {
    // criacao inicial da struct para armazenar as informacoes da venda
	Venda novaVenda;
	novaVenda.idNotaFiscal = ultimoIdVendaCadastrada + 1;
	novaVenda.idCliente = idCliente;
	novaVenda.numDeProdutosDiferentesComprados = 0;
	novaVenda.valorTotal = 0;

	int adicionarMaisProdutos = 1;

    // loop para adicionar produtos na venda
	while (adicionarMaisProdutos) {
		listarProdutos();

		ProdutoVenda novoProduto;
		int indexProduto;

		printf("\nDigite o ID do produto (ou 0 para voltar): ");
		scanf("%d", &novoProduto.idProduto);

		if (novoProduto.idProduto == 0) {
			printf("\nVoltando...\n");
			break;
		}

		indexProduto = encontraIndexDeProduto(novoProduto.idProduto);

		if (indexProduto == -1) {
			printf("\nProduto nao encontrado. Tente novamente.\n");
			continue;
		}

		printf("Informe a quantidade desejada: ");
		scanf("%d", &novoProduto.quantidade);

		if (novoProduto.quantidade <= 0 || novoProduto.quantidade > produtosStruct[indexProduto].estoqueDisponivel) {
			printf("\nQuantidade invalida ou acima do estoque disponivel.\n");
			continue;
		}

        // salva dentro da struct criada anteriormente as informacoes da venda com o produto que foi adicionado a venda
		produtosStruct[indexProduto].estoqueDisponivel -= novoProduto.quantidade;
		novaVenda.valorTotal += novoProduto.quantidade * produtosStruct[indexProduto].valor;
		novaVenda.produtos[novaVenda.numDeProdutosDiferentesComprados] = novoProduto;
		novaVenda.numDeProdutosDiferentesComprados++;

		if (novaVenda.numDeProdutosDiferentesComprados >= QTD_LIMITE_VENDAS) {
			printf("\nLimite de %d produtos diferentes por venda atingido.\n", QTD_LIMITE_VENDAS);
			break;
		}

		printf("\n0 - finalizar venda\n1 - adicionar mais produtos\n");
		scanf("%d", &adicionarMaisProdutos);
	}

	return novaVenda;
}
// salva no sistema as informacoes da venda que vem da funcao anterior
void salvarVenda(Venda novaVenda) {
	venda[qtdVendasCadastradas] = novaVenda;
	qtdVendasCadastradas++;
	ultimoIdVendaCadastrada++;
}


// 8 listagem
void listarVendas() {
	if (qtdVendasCadastradas == 0) {
		printf("Nenhuma venda cadastrada.\n");
		return;
	}

	for (int i = 0; i < qtdVendasCadastradas; i++) {
	    // informacoes gerais da venda (cliente comprador, id da venda, etc)
		printf("\n---------------------------------\n");
		printf("ID DA VENDA: %d\n", venda[i].idNotaFiscal);

		// Buscar nome do cliente
		int indexCliente = encontraIndexDeCliente(venda[i].idCliente);
		if (indexCliente != -1) {
			printf("ID: %d | NOME: %s \n", venda[i].idCliente, clientesStruct[indexCliente].nome);
		} else {
			printf("ID: %d | ID INVALIDO OU DELETADO\n", venda[i].idCliente);
		}

        // informacoes relacionadas aos produtos vendidos
		printf("\n<ITENS DA VENDA>\n");

		for (int j = 0; j < venda[i].numDeProdutosDiferentesComprados; j++) {
			int idProd = venda[i].produtos[j].idProduto;
			int indexProduto = encontraIndexDeProduto(idProd);

			if (indexProduto != -1) {
				printf("PRODUTO: %s | QUANTIDADE: %d | PRECO UNITARIO: R$ %.2f\n",
				       produtosStruct[indexProduto].nome,
				       venda[i].produtos[j].quantidade,
				       produtosStruct[indexProduto].valor);
			} else {
				printf("PRODUTO COM ID %d NAO ENCONTRADO / DELETADO\n", idProd);
			}
		}

        // informacao quanto ao valor total da transacao
		printf("\nTOTAL DA VENDA: R$ %.2f\n", venda[i].valorTotal);
		printf("---------------------------------\n");
	}
}


// 9 menu de edicao
void menuEditarVenda() {
	int opcao;
	do {
		if (qtdVendasCadastradas == 0) return;
		mostraOpcoesVendas();
		scanf("%d", &opcao);

		switch(opcao) {
		case 1:
			buscarVendaMenu();
			break;
		case 2:
			listarVendas();
			break;
		case 0:
			printf("\nVoltando...\n");
			break;
		default:
			printf("\nOpcao invalida.\n");
		}
	} while (opcao != 0);
}

// 9.1 busca
void buscarVendaMenu() {
	int id, index = -1;

	printf("\nDigite o ID da venda a ser editada: ");
	scanf("%d", &id);

    // procura o id da venda escolhida
	for (int i = 0; i < qtdVendasCadastradas; i++) {
		if (venda[i].idNotaFiscal == id) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		printf("\nVenda com ID %d nao encontrada.\n", id);
	} else {
		menuVendaSelecionada(id, index);
	}
}

// 9.1 menu de edicao 2
void menuVendaSelecionada(int id, int index) {
	int opcao;
	do {
		mostraOpcoesVendaSelecionada();
		scanf("%d", &opcao);

		switch (opcao) {
		case 1:
			excluirVendaPorIndex(id, index);
			return;
		case 2:
			alterarClienteDaVenda(id, index);
			break;
		case 3:
			removerProdutoDaVenda(id, index);
			break;
		case 0:
			printf("\nVoltando...\n");
			break;
		default:
			printf("\nOpcao invalida.\n");
		}
	} while (opcao != 0);
}


// 9.1.1 exclusao
void excluirVendaPorIndex(int id, int index) {
	int desejaRepor;

	printf("\nDeseja repor o estoque dos produtos desta venda?\n0 - nao\n1 - sim\n");
	scanf("%d", &desejaRepor);

	if (desejaRepor == 1) {
		reporEstoqueDaVenda(index);
	} else {
		printf("\nEstoque nao foi alterado.\n");
	}

	// desloca as posicoes(dentro da lista de structs vendas) das vendas seguintes
	for (int i = index; i < qtdVendasCadastradas - 1; i++) {
		venda[i] = venda[i + 1];
	}

	qtdVendasCadastradas--;

	printf("\nVenda com ID %d excluida com sucesso.\n", id);
}
void reporEstoqueDaVenda(int index) {
	for (int j = 0; j < venda[index].numDeProdutosDiferentesComprados; j++) {
		int idProd = venda[index].produtos[j].idProduto;
		int indexProduto = encontraIndexDeProduto(idProd);

		if (indexProduto != -1) {
			produtosStruct[indexProduto].estoqueDisponivel += venda[index].produtos[j].quantidade;
		}
	}
	printf("\nEstoque dos produtos da venda excluida foi reposto.\n");
}


// 9.1.2 alteracao cliente comprador
void alterarClienteDaVenda(int id, int index) {
	int novoIdCliente;
	int indexCliente;

	listarClientes();
	printf("\nInforme o novo ID do cliente para esta venda: ");
	scanf("%d", &novoIdCliente);

	indexCliente = encontraIndexDeCliente(novoIdCliente);

	if (indexCliente == -1) {
		printf("\nCliente com ID %d nao encontrado. Alteracao cancelada.\n", novoIdCliente);
		return;
	}

	venda[index].idCliente = novoIdCliente;
	printf("\nCliente da venda com ID %d alterado com sucesso.\n", id);
}

// 9.1.3 alteracao remover produto da venda
void removerProdutoDaVenda(int id, int index) {
	if (venda[index].numDeProdutosDiferentesComprados == 0) {
		printf("\nEsta venda nao possui produtos para remover.\n");
		return;
	}

    // escolhendo produto para remover da venda
	printf("\nProdutos nesta venda:\n");
	for (int i = 0; i < venda[index].numDeProdutosDiferentesComprados; i++) {
		int idProd = venda[index].produtos[i].idProduto;
		int indexProduto = encontraIndexDeProduto(idProd);

		if (indexProduto != -1) {
			printf("%d - Produto: %s | Quantidade: %d | Preco unitario: R$ %.2f\n",
			       i + 1,
			       produtosStruct[indexProduto].nome,
			       venda[index].produtos[i].quantidade,
			       produtosStruct[indexProduto].valor);
		} else {
			printf("%d - Produto com ID %d (nao encontrado / deletado)\n", i + 1, idProd);
		}
	}

	int escolha;
	printf("\nInforme o numero do produto que deseja remover (1 a %d): ", venda[index].numDeProdutosDiferentesComprados);
	scanf("%d", &escolha);

	if (escolha < 1 || escolha > venda[index].numDeProdutosDiferentesComprados) {
		printf("\nOpcao invalida.\n");
		return;
	}

	int posicao = escolha - 1;
	int idProd = venda[index].produtos[posicao].idProduto;
	int indexProduto = encontraIndexDeProduto(idProd);

	// repoe o estoque do produto
	if (indexProduto != -1) {
		produtosStruct[indexProduto].estoqueDisponivel += venda[index].produtos[posicao].quantidade;
	}

	// diminui o valor total da venda
	if (indexProduto != -1) {
		venda[index].valorTotal -= venda[index].produtos[posicao].quantidade * produtosStruct[indexProduto].valor;
	}

	// remove o produto da venda (deslocando os produtos seguintes)
	for (int i = posicao; i < venda[index].numDeProdutosDiferentesComprados - 1; i++) {
		venda[index].produtos[i] = venda[index].produtos[i + 1];
	}

	venda[index].numDeProdutosDiferentesComprados--;

	printf("\nProduto removido da venda com sucesso.\n");

	// se a venda ficar sem produtos, avisa o usuario
	if (venda[index].numDeProdutosDiferentesComprados == 0) {
		printf("\nAviso: esta venda agora nao tem mais produtos.\n");
	}
}