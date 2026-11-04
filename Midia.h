#ifndef MIDIA_H
#define MIDIA_H

#include <string>
#include <iostream>
#include "Data.h"

class Midia {
protected:
    std::string nome; // nome do anime
    int epsAssistidos;
    float nota; // nota dos animes vistos ou cada um
    Data dataCadastro; // Composição (Atributo de Data.h)

public:
    Midia(std::string n, int eps, float nt, Data dt) // construtor
        : nome(n), epsAssistidos(eps), nota(nt), dataCadastro(dt) {}

    virtual ~Midia() {} // destrutor classe mãe

    // Getters
    std::string getNome() const { return nome; }
    int getEpsAssistidos() const { return epsAssistidos; }
    float getNota() const { return nota; }
    Data getDataCadastro() const { return dataCadastro; }

    // Setters
    void setNome(const std::string& n) { nome = n; }
    void setEpsAssistidos(int eps) { epsAssistidos = eps; }
    void setNota(float nt) { nota = nt; }
    void setDataCadastro(Data dt) { dataCadastro = dt; }

    // Método polimórfico abstrato
    virtual void exibirInfo() const = 0;
    virtual std::string getTipo() const = 0;
    // se herdar de mídia, a classe herdada é obrigada a escrever sua versao
    // de exibirInfo() e getTipo()
};

#endif
