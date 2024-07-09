#include "astronauta.h"

Astronauta::Astronauta(const string& cpf, const string& nome, int idade)
    : cpf(cpf), nome(nome), idade(idade), disponibilidade(true), vivo(true) {}

string Astronauta::getCPF() const {
    return cpf;
}

string Astronauta::getNome() const {
    return nome;
}

int Astronauta::getIdade() const {
    return idade;
}

bool Astronauta::getDisponibilidade() const {
    return disponibilidade;
}

bool Astronauta::getVivo() const {
    return vivo;
}

list<int> Astronauta::getVoosAstronauta() const {
    return voosAstronauta;
}

void Astronauta::setDisponibilidade(bool disponibilidade) {
    this->disponibilidade = disponibilidade;
}

void Astronauta::setVivo(bool vivo) {
    this->vivo = vivo;
}

void Astronauta::addVoo(int codigoVoo) {
    voosAstronauta.push_back(codigoVoo);
}

void Astronauta::remVoo(int codigoVoo) {
    voosAstronauta.remove(codigoVoo);
}
