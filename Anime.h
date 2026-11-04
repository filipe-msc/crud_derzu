#ifndef ANIME_H
#define ANIME_H

#include "Midia.h"

class Anime : public Midia {
private:
    int totalEpisodios; // Atributo privado da subclasse

public:
    Anime(std::string n, int epsAss, float nt, Data dt, int totalEps)
        : Midia(n, epsAss, nt, dt), totalEpisodios(totalEps) {}

    int getTotalEpisodios() const { return totalEpisodios; }
    void setTotalEpisodios(int total) { totalEpisodios = total; }

    // Sobrescrita de método
    void exibirInfo() const override {
        std::cout << "[Anime TV/Série] " << nome 
                  << " | EPs Assistidos: " << epsAssistidos << "/" << totalEpisodios
                  << " | Nota: " << nota 
                  << " | Cadastrado em: " << dataCadastro.toString() << "\n";
    }

    std::string getTipo() const override { return "Anime"; }
};

#endif
