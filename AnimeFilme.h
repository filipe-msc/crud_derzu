#ifndef ANIME_FILME_H
#define ANIME_FILME_H

#include "Midia.h"

class AnimeFilme : public Midia {
private:
    int duracaoMinutos; // Atributo privado da subclasse

public:
    AnimeFilme(std::string n, int epsAss, float nt, Data dt, int duracao)
        : Midia(n, epsAss, nt, dt), duracaoMinutos(duracao) {}

    int getDuracaoMinutos() const { return duracaoMinutos; }
    void setDuracaoMinutos(int duracao) { duracaoMinutos = duracao; }

    // Sobrescrita de método
    void exibirInfo() const override {
        std::cout << "[Filme/OVA] " << nome 
                  << " | Duração: " << duracaoMinutos << " min"
                  << " | EPs/Partes: " << epsAssistidos
                  << " | Nota: " << nota 
                  << " | Cadastrado em: " << dataCadastro.toString() << "\n";
    }

    std::string getTipo() const override { return "AnimeFilme"; }
};

#endif
