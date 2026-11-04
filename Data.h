#ifndef DATA_H
#define DATA_H // Carimbo

#include <iostream>
#include <string>

class Data {
private:
    int dia; // Encapsulamento em private p/ numero inteiro
    int mes;
    int ano;

public:
    Data(int d = 1, int m = 1, int a = 2026) : dia(d), mes(m), ano(a) {} // connstrutor
    // se nao informar valores, coloca 01/01/2026 padrão.
    // inicialização com valores dados no parâmetro int d = 1 e etc.

    int getDia() const { return dia; }
    int getMes() const { return mes; }
    int getAno() const { return ano; }
    // método get para ler private
    // const para ler dados inofensivos constantes

    void setDia(int d) { dia = d; }
    void setMes(int m) { mes = m; }
    void setAno(int a) { ano = a; }

    std::string toString() const {
        return std::to_string(dia) + "/" + std::to_string(mes) + "/" + std::to_string(ano);
    }
};

#endif
