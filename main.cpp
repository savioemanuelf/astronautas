#include <iostream>
#include <unordered_map>
#include <list>
#include <chrono>
#include <thread>

#include "astronauta.h"
#include "voo.h"


using std::cin; 
using std::cout;
using std::endl;

unordered_map<string, Astronauta*> astronautas;
unordered_map<int, Voo*> voos;
list<Astronauta*> astronautasMortos;

void clearScreen() {
    #ifdef _WIN32
        std::system("cls"); // Limpa a tela no Windows
    #else
        std::system("clear"); //Limpa a tela no Linux/Mac
    #endif
}

void pauseScreen() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout << "\nPRESSIONE ENTER PARA VOLTAR AO MENU" << endl;
    cin.ignore();
    clearScreen();
}

void cadastrarAstronauta(const string& cpf, const string& nome, int idade) {
    cout << "\n";
    if (astronautas.find(cpf) == astronautas.end()) {
        astronautas[cpf] = new Astronauta(cpf, nome, idade);
        cout << "Astronauta cadastrado com sucesso!" << endl;
    } else {
        cout << "Este CPF ja esta cadastrado" << endl;
    }
    pauseScreen();
}

void cadastrarVoo(int codigo) {
    if (voos.find(codigo) == voos.end()) {
        voos[codigo] = new Voo(codigo);
        cout << "Voo cadastrado com sucesso!" << endl;
    } else {
        cout << "Codigo de voo ja cadastrado" << endl;
    }
    pauseScreen();
}

void adicionarAstronautaEmVoo(int codigoVoo, const string& cpf) {
    cout << "\n";
    if (voos.find(codigoVoo) != voos.end() && astronautas.find(cpf) != astronautas.end()) {
        Voo* voo = voos[codigoVoo];
        Astronauta* astronauta = astronautas[cpf];
        if (voo->getEmPlanejamento() && astronauta->getDisponibilidade()) {
            voo->addPassageiro(cpf);
            astronauta->addVoo(codigoVoo);
            cout << "Astronauta adicionado ao voo com sucesso!" << endl;
        } else {
            cout << "Astronauta nao pode ser adicionado. Verifique se o voo esta em planejamento e a disponibilidade do astronauta" << endl;
        }
    } else {
        cout << "Voo ou astronauta nao encontrado." << endl;
    }
    pauseScreen();
}

void removerAstronautaDeVoo(int codigoVoo, const string& cpf) {
    cout << "\n";
    if (voos.find(codigoVoo) != voos.end() && astronautas.find(cpf) != astronautas.end()) {
        Voo* voo = voos[codigoVoo];
        if (voo->getEmPlanejamento()) {
            voo->remPassageiro(cpf);
            astronautas[cpf]->remVoo(codigoVoo);
            cout << "Astronauta removido do voo com sucesso!" << endl;
        } else {
            cout << "Astronauta não pode ser removido. O voo não está em planejamento." << endl;
        }
    } else {
        cout << "Voo ou Astronauta não encontrado." << endl;
    }
    pauseScreen();
}

void lancarVoo(int codigoVoo) {
    cout << "\n";
    if (voos.find(codigoVoo) != voos.end()) {
        Voo* voo = voos[codigoVoo];
        if (voo->getEmPlanejamento() && !voo->getPassageiros().empty()) {
            bool todosDisponiveis = true;
            for (const string& cpf : voo->getPassageiros()) {
                if (!astronautas[cpf]->getDisponibilidade()) {
                    todosDisponiveis = false;
                    break;
                }
            }
            if (todosDisponiveis) {
                voo->setEmPlanejamento(false);
                voo->setEmCurso(true);
                for (const string& cpf : voo->getPassageiros()) {
                    astronautas[cpf]->setDisponibilidade(false);
                }
                cout << "Voo lancado com sucesso!" << endl;
            } else {
                cout << "Ao menos 1 astronauta nao esta disponivel" << endl;
            }
        } else {
            cout << "Voo nao pode ser lancado. Verifique se está em planejamento e se ha astronautas a bordo." << endl;
        }
    } else {
        cout << "Voo nao encontrado." << endl;
    }
    pauseScreen();
}

void explodirVoo(int codigoVoo) {
    cout << "\n";
    if (voos.find(codigoVoo) != voos.end()) {
        Voo* voo = voos[codigoVoo];
        if (voo->getEmCurso()) {
            voo->setEmCurso(false);
            voo->setFinalizado(true);
            voo->setSucesso(false);
            for (const string& cpf : voo->getPassageiros()) {
                Astronauta* astronauta = astronautas[cpf];
                astronauta->setVivo(false);
                astronautasMortos.push_back(astronauta);
            }
            cout << "Voo explodiu. Todos os astronautas a bordo morreram." << endl;
        } else {
            cout << "Voo nao esta em curso." << endl;
        }
    } else {
        cout << "Voo nao encontrado." << endl;
    }
    pauseScreen();
}

void finalizarVoo(int codigoVoo) {
    cout << "\n";
    if (voos.find(codigoVoo) != voos.end()) {
        Voo* voo = voos[codigoVoo];
        if (voo->getEmCurso()) {
            voo->setEmCurso(false);
            voo->setFinalizado(true);
            voo->setSucesso(true);
            for (const string& cpf : voo->getPassageiros()) {
                astronautas[cpf]->setDisponibilidade(true);
            }
            cout << "Voo finalizado com sucesso!" << endl;
        } else {
            cout << "Voo nao esta em curso." << endl;
        }
    } else {
        cout << "Voo nao encontrado." << endl;
    }
    pauseScreen();
}

void listarVoos() {
    cout << "\n";
    cout << "===============================" << endl;
    cout << "VOOS PLANEJADOS:" << endl;
    for (const auto& pair : voos) {
        Voo* voo = pair.second;

        if (voo->getEmPlanejamento()) {
            cout << "Voo " << voo->getCodigo() << " com astronautas: ";
            for (const string& cpf : voo->getPassageiros()) {
                cout << "\n- " << astronautas[cpf]->getNome() << ";";
            }
        }
        cout << "\n";
    }

    cout << "VOOS EM CURSO:" << endl;
    for (const auto& pair : voos) {
        Voo* voo = pair.second;
        if (voo->getEmCurso()) {
            cout << "Voo " << voo->getCodigo() << " com astronautas: ";
            for (const string& cpf : voo->getPassageiros()) {
                cout << "\n- " << astronautas[cpf]->getNome() << ";";
            }
        }
        cout << "\n";
    }

    cout << "VOOS FINALIZADOS:" << endl;
    for (const auto& pair : voos) {
        Voo* voo = pair.second;
        if (voo->getFinalizado()) {
            cout << "Voo " << voo->getCodigo() << " com astronautas: ";
            for (const string& cpf : voo->getPassageiros()) {
                cout << "\n- " << astronautas[cpf]->getNome() << ";" << endl;
            }
            cout << " - " << (voo->getSucesso() ? "Sucesso" : "Falha") << endl;
        }
        cout << "\n";
    }
    pauseScreen();
}

void listarAstronautasMortos() {
    cout << "Astronautas Mortos:" << endl;
    for (const Astronauta* astronauta : astronautasMortos) {
        cout << "CPF: " << astronauta->getCPF() << ", Nome: " << astronauta->getNome() << ", Voos: ";
        for (int codigoVoo : astronauta->getVoosAstronauta()) {
            cout << codigoVoo << " ";
        }
        cout << endl;
    }
    pauseScreen();
}

void exibirMenu() {
    cout << "===============================" << endl;
    cout << "1. Cadastrar Astronauta" << endl;
    cout << "2. Cadastrar Voo" << endl;
    cout << "3. Adicionar Astronauta em Voo" << endl;
    cout << "4. Remover Astronauta de Voo" << endl;
    cout << "5. Lancar Voo" << endl;
    cout << "6. Explodir Voo" << endl;
    cout << "7. Finalizar Voo" << endl;
    cout << "8. Listar Voos" << endl;
    cout << "9. Listar Astronautas Mortos" << endl;
    cout << "0. Sair" << endl;
    cout << "===============================" << endl;
}

int main() {
    int escolha;
    do {
        exibirMenu();
        cout << "Escolha uma opcao: ";
        cin >> escolha;
        cin.ignore();
        
        switch (escolha) {
            case 1: {
                string cpf, nome;
                int idade;
                cout << "CPF: ";
                getline(cin, cpf);
                cout << "Nome: ";
                getline(cin, nome);
                cout << "Idade: ";
                cin >> idade;
                cin.ignore();
                cadastrarAstronauta(cpf, nome, idade);
                break;
            }
            case 2: {
                int codigo;
                cout << "Codigo do Voo: ";
                cin >> codigo;
                cadastrarVoo(codigo);
                break;
            }
            case 3: {
                int codigoVoo;
                string cpf;
                cout << "Codigo do Voo: ";
                cin >> codigoVoo;
                cout << "CPF do Astronauta: ";
                cin.ignore(); //Limpa o buffer de entrada
                getline(cin, cpf);
                adicionarAstronautaEmVoo(codigoVoo, cpf);
                break;
            }
            case 4: {
                int codigoVoo;
                string cpf;
                cout << "Codigo do Voo: ";
                cin >> codigoVoo;
                cout << "CPF do Astronauta: ";
                cin.ignore(); //Limpa o buffer de entrada
                getline(cin, cpf);
                removerAstronautaDeVoo(codigoVoo, cpf);
                break;
            }
            case 5: {
                int codigoVoo;
                cout << "Codigo do Voo: ";
                cin >> codigoVoo;
                lancarVoo(codigoVoo);
                break;
            }
            case 6: {
                int codigoVoo;
                cout << "Codigo do Voo: ";
                cin >> codigoVoo;
                explodirVoo(codigoVoo);
                break;
            }
            case 7: {
                int codigoVoo;
                cout << "Codigo do Voo: ";
                cin >> codigoVoo;
                finalizarVoo(codigoVoo);
                break;
            }
            case 8:
                listarVoos();
                break;
            case 9:
                listarAstronautasMortos();
                break;
            case 0:
                cout << "Saindo do programa..." << endl;
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
        }
    } while (escolha != 0);

    return 0;
}
