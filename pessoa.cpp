#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Pessoa
class Pessoa {
public:
  Pessoa(string nome, string tel, int tipo, string cpf);

  // Gets
  int getTipo();
  string getNome();
  string getTel();
  string getCPF();

  // Sets
  void setTipo(int tipo);
  void setNome(string nome);
  void setTel(string tel);
  void setCPF(string cpf);

private:
  int tipo;
  string nome, tel, cpf;
};
// Constructors implementation
Pessoa::Pessoa(string nome, string tel, int tipo, string cpf = "") {
  setTipo(tipo);
  setNome(nome);
  setTel(tel);
  setCPF(cpf);
}
// Gets
int Pessoa::getTipo() { return tipo; }
string Pessoa::getNome() { return nome; }
string Pessoa::getTel() { return tel; }
string Pessoa::getCPF() { return cpf; }
// SETS
void Pessoa::setTipo(int tipo) { this->tipo = tipo; }
void Pessoa::setNome(string nome) { this->nome = nome; }
void Pessoa::setTel(string tel) { this->tel = tel; }
void Pessoa::setCPF(string cpf) { this->cpf = cpf; }
// Pessoa END

// Gera arquivo
void geraArquivo(string path, string data) {
  fstream fs;
  fs.open(path.c_str(), fstream::out);
  if (fs.is_open()) {
    fs.write(data.c_str(), data.size());
    fs.close();
  } else {
    cerr << "Arquivo não aberto";
  }
}
void geraArquivos() {
  string data1 = "1\nJoao Pedro\n(83) 8888-8888\n"
                 "2\nMaria Teresa\n(83) 9999-9999\n000.000.000-00\n"
                 "2\nLuiz Pereira\n(83) 7777-7777\n111.111.111-11\n"
                 "1\nDenis Carlos\n(83) 5555-5555\n";
  string data2 = "2\nLuma Oliveira\n(83) 1111-1111\n222.222.222-22\n"
                 "2\nTercio Marquies\n(83) 2222-2222\n333.333.222-33\n"
                 "1\nJonas Luz\n(83) 3333-3333\n";
  geraArquivo("dados01.txt", data1);
  geraArquivo("dados02.txt", data2);
}

int main() {
  int tipo;
  string nome, tel, cpf, arqN;
  fstream file;

  // gerando arquivos
  geraArquivos();

  // Nome do arquivo
  getline(cin, arqN);

  // Abrindo arqN
  file.open(arqN);

  if (!file.is_open()) {
    cerr << "Deu RUIM :(";
    return -1;
  }

  // Vector de Pessoas
  vector<Pessoa *> pessoas;

  Pessoa *pessoa;

  while (true) {
    file >> tipo;
    // Verificando END OF FILE
    if (file.eof()) {
      break;
    }
    // Limpa buffer
    file.ignore();
    getline(file, nome);
    getline(file, tel);
    if (tipo == 2) {
      getline(file, cpf);
      pessoa = new Pessoa(nome, tel, tipo, cpf);
    } else {
      pessoa = new Pessoa(nome, tel, tipo);
    }

    pessoas.push_back(pessoa);
  }

  for (int i = 0; i < pessoas.size(); i++) {
    cout << pessoas[i]->getNome() << ", tel: " << pessoas[i]->getTel();
    if(pessoas[i]->getTipo() == 2) 
      cout << ", CPF: " << pessoas[i]->getCPF();
    cout << endl;
  }

  return 0;
}
