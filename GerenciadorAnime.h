#ifndef GERENCIADOR_ANIME_H
#define GERENCIADOR_ANIME_H

#include <vector>
#include <memory>
#include <string>
#include "Midia.h"

class GerenciadorAnime {
private:
    std::vector<std::unique_ptr<Midia>> colecao;
    const std::string arquivoDados = "animes.txt";

public:
    GerenciadorAnime();
    ~GerenciadorAnime();

    // Métodos de Persistência em Arquivo
    void salvarEmArquivo();
    void carregarDoArquivo();

    // Pesquisa
    int Pesquisar(std::string nome);

    // Operações do CRUD
    void Inserir();
    void ListarTodos();
    void ExibirUm();
    void Alterar();
    void Remover();
    void ExibirRelatorio();

    // Ordenações requeridas
    void OrdenarPorNome();
    void OrdenarPorNota();
    void OrdenarPorEpisodios();
};

#endif
