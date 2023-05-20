#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Eleitor
class Eleitor {
public:
  Eleitor(string nome, int idade, string titulo);

  //gets
  string getNome() {return nome;};
  int getIdade() {return idade;};
  string getTitulo() {return titulo;};

  //sets
  void setNome(string nome){this->nome=nome;};
  void setIdade(int idade){this->idade=idade;};
  void setTitulo(string titulo){this->titulo=titulo;};
private:
  string nome, titulo;
  int idade;
};

Eleitor::Eleitor(string nome, int idade, string titulo) {
  setNome(nome);
  setIdade(idade);
  setTitulo(titulo);
}
//Eleitor END

//GerenciadorEleitores
class GerenciadorEleitores {
public:
  GerenciadorEleitores();
  //Cadastra eleitor
  void cadastrarEleitor(string nome, int idade, string titulo);
  void verificaEleitores();
private:
  vector<Eleitor*> eleitores;

  //verificar menor de idade
  void verificaMenordeIdade(Eleitor *el);
  void verificaPendencia(Eleitor *el);
};

//implementation
GerenciadorEleitores::GerenciadorEleitores() {}

void GerenciadorEleitores::cadastrarEleitor(string nome, int idade, string titulo) {
  eleitores.push_back(new Eleitor(nome, idade, titulo));
}

void GerenciadorEleitores::verificaMenordeIdade(Eleitor *el) {
  if(el->getIdade() < 16)
    throw new overflow_error("Eleitor " + el->getNome() + " não pode ser cadastrado");
}

void GerenciadorEleitores::verificaPendencia(Eleitor *el) {
  if(el->getIdade() > 20)
    throw new overflow_error("Eleitor " + el->getNome() + " com pendência");
}

void GerenciadorEleitores::verificaEleitores() {
  for(auto eleitor: eleitores) {
    try {
      verificaMenordeIdade(eleitor);
    } catch(overflow_error *e) {
      cout << e->what() << endl;
    }
    
    try {
      verificaPendencia(eleitor);
    } catch(overflow_error *e) {
      cout << e->what() << endl;
    }
  }
}
//GerenciadorEleitoresEND

int main() {
  GerenciadorEleitores g1;
  int n_eleitores = 0;
  string nome, titulo;
  int idade;

  //Número de eleitores
  cin >> n_eleitores;
  cin.ignore();

  for(int i = 0; i < n_eleitores; i++) {
    getline(cin, nome);
    cin >> idade;
    cin.ignore();
    getline(cin, titulo);
    g1.cadastrarEleitor(nome, idade, titulo);
  }

  g1.verificaEleitores();

  return 0;
}