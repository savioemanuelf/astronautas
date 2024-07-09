#ifndef ASTRONAUTA_H
#define ASTRONAUTA_H

#include <string>
#include <list>

using namespace std;

class Astronauta {
private:
    string cpf;
    string nome;
    int idade;
    bool disponibilidade;
    bool vivo;
    list<int> voosAstronauta;

public:
    Astronauta(const string& cpf, const string& nome, int idade);
    string getCPF() const;
    string getNome() const;
    int getIdade() const;
    bool getDisponibilidade() const;
    bool getVivo() const;
    list<int> getVoosAstronauta() const;
    void setDisponibilidade(bool disponibilidade);
    void setVivo(bool vivo);
    void addVoo(int codigoVoo);
    void remVoo(int codigoVoo);
};

#endif // ASTRONAUTA_H
