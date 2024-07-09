#include "voo.h"

Voo::Voo(int codigo)
    : codigo(codigo), emPlanejamento(true), emCurso(false), finalizado(false), sucesso(false) {}

int Voo::getCodigo() const {
    return codigo;
}

list<string> Voo::getPassageiros() const {
    return passageiros;
}

bool Voo::getEmPlanejamento() const {
    return emPlanejamento;
}

bool Voo::getEmCurso() const {
    return emCurso;
}

bool Voo::getFinalizado() const {
    return finalizado;
}

bool Voo::getSucesso() const {
    return sucesso;
}

void Voo::setEmPlanejamento(bool emPlanejamento) {
    this->emPlanejamento = emPlanejamento;
}

void Voo::setEmCurso(bool emCurso) {
    this->emCurso = emCurso;
}

void Voo::setFinalizado(bool finalizado) {
    this->finalizado = finalizado;
}

void Voo::setSucesso(bool sucesso) {
    this->sucesso = sucesso;
}

void Voo::addPassageiro(const string& cpf) {
    passageiros.push_back(cpf);
}

void Voo::remPassageiro(const string& cpf) {
    passageiros.remove(cpf);
}
