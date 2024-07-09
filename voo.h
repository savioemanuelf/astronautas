#ifndef VOO_H
#define VOO_H

#include <string>
#include <list>

using namespace std;

class Voo {
private:
    int codigo;
    bool emPlanejamento;
    bool emCurso;
    bool finalizado;
    bool sucesso;
    list<string> passageiros;

public:
    Voo(int codigo);
    int getCodigo() const;
    list<string> getPassageiros() const;
    bool getEmPlanejamento() const;
    bool getEmCurso() const;
    bool getFinalizado() const;
    bool getSucesso() const;
    void setEmPlanejamento(bool emPlanejamento);
    void setEmCurso(bool emCurso);
    void setFinalizado(bool finalizado);
    void setSucesso(bool sucesso);
    void addPassageiro(const string& cpf);
    void remPassageiro(const string& cpf);
};

#endif // VOO_H
