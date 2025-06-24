#ifndef CLIENTE_H
#define CLIENTE_H

#include "constantes.h"

typedef struct cliente {
	char nome[200];
	char cpf[14];
	char email[200];
	int id;
} Cliente;

extern Cliente clientesStruct[QTD_CLIENTES];
extern int qtdClientesCadastrados;

void cadastrarCliente();
void listarClientes();
void menuEditarCliente();
void mostraOpcoesClientes();
void buscarClienteMenu();
int encontraIndexDeCliente(int id);
void menuClienteSelecionado(int id, int index);
void excluirCliente(int id, int index);
void alterarClienteNome(int id, int index);
void alterarClienteCpf(int id, int index);
void alterarClienteEmail(int id, int index);

#endif