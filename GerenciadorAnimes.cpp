#include "GerenciadorAnime.h"
#include "Anime.h"
#include "AnimeFilme.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>

GerenciadorAnime::GerenciadorAnime() {
    carregarDoArquivo();
}

GerenciadorAnime::~GerenciadorAnime() {
    salvarEmArquivo();
}

int GerenciadorAnime::Pesquisar(std::string nome) {
    if (colecao.empty()) return -1;

    std::string busca = nome;
    std::transform(busca.begin(), busca.end(), busca.begin(), ::tolower);

    std::vector<int> indicesEncontrados;

    for (size_t i = 0; i < colecao.size(); ++i) {
        std::string nomeItem = colecao[i]->getNome();
        std::transform(nomeItem.begin(), nomeItem.end(), nomeItem.begin(), ::tolower);

        // Verifica correspondencia exata ou inicio do nome
        if (nomeItem.rfind(busca, 0) == 0) {
            indicesEncontrados.push_back(i);
        }
    }

    if (indicesEncontrados.empty()) {
        return -1;
    } else if (indicesEncontrados.size() == 1) {
        return indicesEncontrados[0];
    } else {
        std::cout << "\nForam encontrados múltiplos animes com este termo:\n";
        for (size_t i = 0; i < indicesEncontrados.size(); ++i) {
            int idx = indicesEncontrados[i];
            std::cout << "[" << idx << "] " << colecao[idx]->getNome() << "\n";
        }
        std::cout << "Digite o índice desejado: ";
        int escolha;
        std::cin >> escolha;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (int idx : indicesEncontrados) {
            if (idx == escolha) return escolha;
        }
        return -1;
    }
}

void GerenciadorAnime::Inserir() {
    int tipo;
    std::cout << "\n--- Adicionar Novo Anime ---\n";
    std::cout << "1. Anime (Série/TV)\n";
    std::cout << "2. Filme / OVA\n";
    std::cout << "Escolha o tipo: ";
    std::cin >> tipo;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string nome;
    int epsAssistidos, dia, mes, ano;
    float nota;

    std::cout << "Nome do Anime: ";
    std::getline(std::cin, nome);

    std::cout << "Episodios Assistidos: ";
    std::cin >> epsAssistidos;

    std::cout << "Nota (0.0 a 10.0): ";
    std::cin >> nota;

    std::cout << "Data de cadastro (Dia Mes Ano separados por espaço): ";
    std::cin >> dia >> mes >> ano;

    Data dt(dia, mes, ano);

    if (tipo == 1) {
        int totalEps;
        std::cout << "Total de episodios do anime: ";
        std::cin >> totalEps;
        colecao.push_back(std::make_unique<Anime>(nome, epsAssistidos, nota, dt, totalEps));
    } else {
        int duracao;
        std::cout << "Duracao em minutos: ";
        std::cin >> duracao;
        colecao.push_back(std::make_unique<AnimeFilme>(nome, epsAssistidos, nota, dt, duracao));
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Anime cadastrado com sucesso!\n";
}

void GerenciadorAnime::ListarTodos() {
    if (colecao.empty()) {
        std::cout << "\nNenhum anime cadastrado no sistema.\n";
        return;
    }

    std::cout << "\nOpcoes de Exibicao/Ordenacao:\n";
    std::cout << "1. Ordem atual\n";
    std::cout << "2. Ordem Alfabetica\n";
    std::cout << "3. Maiores Notas\n";
    std::cout << "4. Mais Episodios Assistidos\n";
    std::cout << "Escolha uma opcao: ";
    int opt;
    std::cin >> opt;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (opt == 2) OrdenarPorNome();
    else if (opt == 3) OrdenarPorNota();
    else if (opt == 4) OrdenarPorEpisodios();

    std::cout << "\n================ LISTA DE ANIMES ================\n";
    for (size_t i = 0; i < colecao.size(); ++i) {
        std::cout << "indice [" << i << "] ";
        colecao[i]->exibirInfo();
    }
    std::cout << "=================================================\n";
}

void GerenciadorAnime::ExibirUm() {
    std::string busca;
    std::cout << "Digite o nome (ou inicio do nome) para pesquisar: ";
    std::getline(std::cin, busca);

    int idx = Pesquisar(busca);
    if (idx != -1) {
        std::cout << "\n--- Anime Encontrado ---\n";
        colecao[idx]->exibirInfo();
    } else {
        std::cout << "Anime nao encontrado.\n";
    }
}

void GerenciadorAnime::Alterar() {
    std::string busca;
    std::cout << "Digite o nome do anime que deseja alterar: ";
    std::getline(std::cin, busca);

    int idx = Pesquisar(busca);
    if (idx == -1) {
        std::cout << "Anime nao encontrado.\n";
        return;
    }

    std::cout << "\nEditando o anime: " << colecao[idx]->getNome() << "\n";

    int eps;
    float nota;

    std::cout << "Novo numero de episodios assistidos: ";
    std::cin >> eps;
    std::cout << "Nova nota (0-10): ";
    std::cin >> nota;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    colecao[idx]->setEpsAssistidos(eps);
    colecao[idx]->setNota(nota);

    std::cout << "Cadastro atualizado com sucesso!\n";
}

void GerenciadorAnime::Remover() {
    std::string busca;
    std::cout << "Digite o nome do anime que deseja remover: ";
    std::getline(std::cin, busca);

    int idx = Pesquisar(busca);
    if (idx == -1) {
        std::cout << "Anime nao encontrado.\n";
        return;
    }

    std::cout << "Tem certeza que deseja remover '" << colecao[idx]->getNome() << "'? (s/n): ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (confirm == 's' || confirm == 'S') {
        colecao.erase(colecao.begin() + idx);
        std::cout << "Anime removido com sucesso.\n";
    } else {
        std::cout << "Operacao cancelada.\n";
    }
}

void GerenciadorAnime::ExibirRelatorio() {
    std::cout << "\n================ RELATORIO DO SISTEMA ================\n";
    std::cout << "Quantidade de animes cadastrados: " << colecao.size() << "\n";

    if (colecao.empty()) {
        std::cout << "======================================================\n";
        return;
    }

    int totalEps = 0;
    float somaNotas = 0.0f;
    int qtdSeries = 0;
    int qtdFilmes = 0;

    for (const auto& item : colecao) {
        totalEps += item->getEpsAssistidos();
        somaNotas += item->getNota();
        if (item->getTipo() == "Anime") qtdSeries++;
        else qtdFilmes++;
    }

    std::cout << "Series de TV: " << qtdSeries << "\n";
    std::cout << "Filmes/OVAs: " << qtdFilmes << "\n";
    std::cout << "Total de episodios assistidos: " << totalEps << "\n";
    std::cout << "Midia das notas: " << (somaNotas / colecao.size()) << "\n";
    std::cout << "======================================================\n";
}

void GerenciadorAnime::OrdenarPorNome() {
    std::sort(colecao.begin(), colecao.end(), [](const std::unique_ptr<Midia>& a, const std::unique_ptr<Midia>& b) {
        return a->getNome() < b->getNome();
    });
}

void GerenciadorAnime::OrdenarPorNota() {
    std::sort(colecao.begin(), colecao.end(), [](const std::unique_ptr<Midia>& a, const std::unique_ptr<Midia>& b) {
        return a->getNota() > b->getNota();
    });
}

void GerenciadorAnime::OrdenarPorEpisodios() {
    std::sort(colecao.begin(), colecao.end(), [](const std::unique_ptr<Midia>& a, const std::unique_ptr<Midia>& b) {
        return a->getEpsAssistidos() > b->getEpsAssistidos();
    });
}

void GerenciadorAnime::salvarEmArquivo() {
    std::ofstream arq(arquivoDados);
    if (!arq.is_open()) return;

    for (const auto& item : colecao) {
        arq << item->getTipo() << ";"
            << item->getNome() << ";"
            << item->getEpsAssistidos() << ";"
            << item->getNota() << ";"
            << item->getDataCadastro().getDia() << ";"
            << item->getDataCadastro().getMes() << ";"
            << item->getDataCadastro().getAno() << ";";

        if (item->getTipo() == "Anime") {
            Anime* anime = static_cast<Anime*>(item.get());
            arq << anime->getTotalEpisodios() << "\n";
        } else {
            AnimeFilme* filme = static_cast<AnimeFilme*>(item.get());
            arq << filme->getDuracaoMinutos() << "\n";
        }
    }
    arq.close();
}

void GerenciadorAnime::carregarDoArquivo() {
    std::ifstream arq(arquivoDados);
    if (!arq.is_open()) return;

    colecao.clear();
    std::string linha;

    while (std::getline(arq, linha)) {
        if (linha.empty()) continue;

        std::stringstream ss(linha);
        std::string tipo, nome, token;
        int eps, dia, mes, ano, extra;
        float nota;

        std::getline(ss, tipo, ';');
        std::getline(ss, nome, ';');
        
        std::getline(ss, token, ';'); eps = std::stoi(token);
        std::getline(ss, token, ';'); nota = std::stof(token);
        std::getline(ss, token, ';'); dia = std::stoi(token);
        std::getline(ss, token, ';'); mes = std::stoi(token);
        std::getline(ss, token, ';'); ano = std::stoi(token);
        std::getline(ss, token, '\n'); extra = std::stoi(token);

        Data dt(dia, mes, ano);

        if (tipo == "Anime") {
            colecao.push_back(std::make_unique<Anime>(nome, eps, nota, dt, extra));
        } else if (tipo == "AnimeFilme") {
            colecao.push_back(std::make_unique<AnimeFilme>(nome, eps, nota, dt, extra));
        }
    }
    arq.close();
}
