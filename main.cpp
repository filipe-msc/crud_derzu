#include <iostream>
#include "GerenciadorAnime.h"

int main() {
    GerenciadorAnime sistema;
    int opcao = 0;

    while (opcao != 7) {
        std::cout << "\n================ MENU PRINCIPAL ================\n";
        std::cout << "1. Inserir Anime\n";
        std::cout << "2. Listar todos\n";
        std::cout << "3. Exibir um (pesquisar por nome)\n";
        std::cout << "4. Alterar (pesquisar por nome)\n";
        std::cout << "5. Remover (pesquisar por nome)\n";
        std::cout << "6. Exibir Relatorio\n";
        std::cout << "7. Sair\n";
        std::cout << "================================================\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        // Limpeza de buffer
        std::cin.ignore(10000, '\n');

        switch (opcao) {
            case 1: sistema.Inserir(); break;
            case 2: sistema.ListarTodos(); break;
            case 3: sistema.ExibirUm(); break;
            case 4: sistema.Alterar(); break;
            case 5: sistema.Remover(); break;
            case 6: sistema.ExibirRelatorio(); break;
            case 7: std::cout << "Encerrando e salvando dados...\n"; break;
            default: std::cout << "Opcao invalida!\n"; break;
        }
    }

    return 0;
}
