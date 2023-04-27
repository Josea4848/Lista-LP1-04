#include <iostream>
#include <string>
#include <vector>

#define tamanho 3

using namespace std;

// Insumo
class Insumo {
public:
  Insumo();
  Insumo(int tipoInsumo);
  virtual ~Insumo();
  // LerAtributos
  void lerAtributos();

  // Gets
  string getNome();
  int getQuantidade();
  int getValorUnitario();
  string getDtVencimento();
  string getNomeFabricante();
  int getTipoInsumo();

  // Sets
  void setNome(string nome);
  void setQuantidade(int quantidade);
  void setValorUnitario(int valorUnitario);
  void setDtVencimento(string dtVencimento);
  void setNomeFabricante(string nomeFabricante);
  void setTipoInsumo(int tipoInsumo);

protected:
  string nome, dtVencimento, nomeFabricante;
  int quantidade, valorUnitario, tipoInsumo;
};
Insumo::Insumo() : Insumo(0) {}
Insumo::Insumo(int tipoInsumo) {
  setTipoInsumo(tipoInsumo);
  setNome(nome);
}

// Gets
string Insumo::getNome() { return nome; }
int Insumo::getQuantidade() { return quantidade; }
int Insumo::getValorUnitario() { return valorUnitario; }
string Insumo::getDtVencimento() { return dtVencimento; }
string Insumo::getNomeFabricante() { return nomeFabricante; }
int Insumo::getTipoInsumo() { return tipoInsumo; }

// Sets
void Insumo::setNome(string nome) { this->nome = nome; }
void Insumo::setQuantidade(int quantidade) { this->quantidade = quantidade; }
void Insumo::setValorUnitario(int valorUnitario) {
  this->valorUnitario = valorUnitario;
}
void Insumo::setDtVencimento(string dtVencimento) {
  this->dtVencimento = dtVencimento;
}
void Insumo::setNomeFabricante(string nomeFabricante) {
  this->nomeFabricante = nomeFabricante;
}
void Insumo::setTipoInsumo(int tipoInsumo) { 
  this->tipoInsumo = tipoInsumo; 
}
// Ler atributos
void Insumo::lerAtributos() {
  getline(cin, nome);
  cin >> quantidade;
  cin >> valorUnitario;
  cin.ignore();
  getline(cin, dtVencimento);
  getline(cin, nomeFabricante);
}
Insumo::~Insumo() {
    cout << "Deletando Insumos\n";
}

// Insumo END

// Vacina
class Vacina : public Insumo {
public:
  Vacina();
  virtual ~Vacina();

  void lerAtributos();

private:
  string tipo;
  int quantDoses, intervalo;
};
Vacina::Vacina() : Insumo(1) {}
Vacina::~Vacina() {
  cout << "Deletando Vacina\n";
}

void Vacina::lerAtributos() {
  Insumo::lerAtributos();
  getline(cin, tipo);
  cin >> quantDoses;
  cin >> intervalo;
  cin.ignore();
}
// Vacina END

// Medicamento
class Medicamento: public Insumo {
public:
  Medicamento();

  void lerAtributos();
  virtual ~Medicamento();

private:
  string dosagem, administracao, disponibilizacao;
};
Medicamento::Medicamento() : Insumo(2) {}
void Medicamento::lerAtributos() {
  Insumo::lerAtributos();
  getline(cin, dosagem);
  getline(cin, administracao);
  getline(cin, disponibilizacao);
}

Medicamento::~Medicamento() {
  cout << "Deletando Medicamento\n";
}
//Medicamento END

//EPI
class EPI: public Insumo {
public:
  EPI();
  virtual ~EPI();
  void lerAtributos();
private:
  string tipo, descricao;
};
EPI::EPI() : Insumo(3) {}

void EPI::lerAtributos() {
  Insumo::lerAtributos();
  getline(cin, tipo);
  getline(cin, descricao);
}

EPI::~EPI() {
  cout << "Deletando EPI\n";
}
//EPI END

//LocalController
class LocalController {
public:
  LocalController();

  void addInsumoArr(Insumo *in, int index);
  void addInsumoVec(Insumo *in);

  ~LocalController();

private:  
  vector<Insumo*> insumosVec;
  Insumo *insumosArr[tamanho];
};
LocalController::LocalController() {}

void LocalController::addInsumoArr(Insumo *in, int index) {
  insumosArr[index] = in;
}
void LocalController::addInsumoVec(Insumo *in) {
  insumosVec.push_back(in);
}

LocalController::~LocalController() {
  cout << "Deletando Local\n";
  
  for(Insumo *insumo: insumosVec) {
    delete insumo;
  } 

  for(int i = 0; i < tamanho; i++) {
    delete insumosArr[i];
  }
}
//LocalController END

int main() {
  LocalController *l1 = new LocalController();
  Medicamento *med1, *med2;
  Vacina *vac1, *vac2;
  EPI *epi1, *epi2;
  
  
  for(int i = 0; i < 3; i++) {
    switch (i) {
      case 0:
        cout << "Vacina\n";
        vac1 = new Vacina();
        vac2 = new Vacina();
        vac1->lerAtributos();
        *vac2 = *vac1;
        l1->addInsumoArr(vac1, i);
        l1->addInsumoVec(vac2);
        break;
      case 1:
        cout << "Medicamento\n";
        med1 = new Medicamento();
        med2 = new Medicamento();
        med1->lerAtributos();
        *med2 = *med1;
        l1->addInsumoArr(med1, i);
        l1->addInsumoVec(med2);
        break;
      case 2:
        cout << "EPI\n";
        epi1 = new EPI();
        epi2 = new EPI();
        epi1->lerAtributos();
        *epi2 = *epi1;
        l1->addInsumoArr(epi1, i);
        l1->addInsumoVec(epi2);
        break;
    }
  }

  delete l1;
}