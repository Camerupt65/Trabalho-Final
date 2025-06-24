#include <stdio.h>
#include "constantes.h"
#include "menus.h"
#include "cliente.h"
#include "produto.h"
#include "venda.h"

void menu();

int main() {
    menu();

    return 0;
}

// switch menu principal
void menu() {
    int opcao;
    do {
        mostraOpcoes();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: cadastrarCliente(); break;
            case 2: listarClientes(); break;
            case 3: menuEditarCliente(); break;
            case 4: insereProduto(); break;
            case 5: listarProdutos(); break;
            case 6: menuEditarProduto(); break;
            case 7: gerarVendaNova(); break;
            case 8: listarVendas(); break;
            case 9: menuEditarVenda(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}