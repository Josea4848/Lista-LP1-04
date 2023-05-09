#include <iostream>
#include <string>
#include <vector>

#define VARIACAO 51
#define SALDOINICIAL 0
#define TAXAPADRAO 0.006
#define LIMITEPADRAO 2
#define LIMITEESPECIAL 4

using namespace std;

const static string vazio = "Campo Vazio";

// Conta
class Conta {
public:
  // Standard Constructor
  Conta();
  Conta(string nomeCliente, int num, double saldo);

  // nomeCliente
  string getNomeCliente();
  void setNomeCliente(string nomeCliente);

  // num
  virtual int getNum();
  virtual void setNum(int num);

  // Saldo
  virtual double getSaldo();
  virtual void setSaldo(double saldo);

  //Sacar
  virtual void sacar(double valor);

  //Depositar
  virtual void depositar(double valor);

  //Display info
  virtual void toString();

  //Saldo total disponível
  virtual double saldoTotalDisponivel();

protected:
  string nomeCliente;
  int num;
  double saldo;
};
Conta::Conta() : Conta(vazio, 0, 0) {}
Conta::Conta(string nomeCliente, int num, double saldo) {
  setNomeCliente(nomeCliente);
  setNum(num);
  setSaldo(saldo);
}
// nomeCliente implementation
string Conta::getNomeCliente() { return nomeCliente; }
void Conta::setNomeCliente(string nomeCliente) {
  this->nomeCliente = nomeCliente;
}
// num implementation
int Conta::getNum() { return num; }
void Conta::setNum(int num) { this->num = num; }
// saldo implementation
double Conta::getSaldo() { return saldo; }
void Conta::setSaldo(double saldo) { this->saldo = saldo;}
// depositar
void Conta::depositar(double valor) {
  if(valor > 0) {
    saldo += valor;
  }
}
// sacar 
void Conta::sacar(double valor){
  if(valor > 0) {
    saldo -= valor;
  } else {
    cout << "\nsaldo insuficiente\n";
  }
}
double Conta::saldoTotalDisponivel() {
  return getSaldo();
}
void Conta::toString() {
    cout << getNomeCliente() << ", cc: " << getNum() << ", ";
}
// Conta END

//Conta corrente
class ContaCorrente: public Conta {
public:
    ContaCorrente();
    ContaCorrente(double salario, int limite);
    ContaCorrente(string nomeCliente, int num, double saldo, double salario, int limite);

    //Salário
    double getSalario();
    void setSalario(double salario);

    //Limite
    int getLimite();
    void setLimite(int limite);

    //Sacar virtual
    void sacar(double valor);

    //Saldo total disponível
    double saldoTotalDisponivel();

    //Other methods
    double definirLimite();

    //toString
    void toString();

protected:
    double salario;
    int limite;
};
ContaCorrente::ContaCorrente() : ContaCorrente(vazio,  0, 0, 0, 0) {}
ContaCorrente::ContaCorrente(double salario, int limite) : ContaCorrente(vazio,  0, 0, salario, limite) {}
ContaCorrente::ContaCorrente(string nomeCliente, int num, double saldo, double salario, int limite) : Conta(nomeCliente, num, saldo) {
    setSalario(salario);
    setLimite(limite);
    setSaldo(0);  
}
//Salario implementation
double ContaCorrente::getSalario() { return salario; }
void ContaCorrente::setSalario(double salario) {
    this->salario = salario;
}
//Limite implementation
int ContaCorrente::getLimite() { return limite; }
void ContaCorrente::setLimite(int limite) {
    this->limite = limite;
}
//Definir limite
double ContaCorrente::definirLimite() {
    return getSalario()*getLimite();
}
//saldo total disponível
double ContaCorrente::saldoTotalDisponivel() {
  return getSaldo() + definirLimite();
}
//sacar
void ContaCorrente::sacar(double valor) {
    if(valor <= saldoTotalDisponivel()) {
        setSaldo(getSaldo() - valor);
    } else {
        cout << "\nsaldo insuficiente" << endl;
    }
}

//toString
void ContaCorrente::toString() {
  cout << getNomeCliente() << ", cc: " << getNum() <<  ", salário " << getSalario() << ", ";
}

//Conta corrente END

//Conta Especial
class ContaEspecial : public ContaCorrente {
public:
    ContaEspecial();
    ContaEspecial(double salario, double limite);
    ContaEspecial(string nomeCliente, int num, double saldo, double salario, double limite);

    //Definir limite
    double definirLimite();
};
//Constructor implementation
ContaEspecial::ContaEspecial() : ContaEspecial(0, 0) {}
ContaEspecial::ContaEspecial(double salario, double limite) : ContaEspecial(vazio, 0, 0, salario, limite) {}
ContaEspecial::ContaEspecial(string nomeCliente, int num, double saldo, double salario, double limite) : ContaCorrente(nomeCliente, num, saldo, salario, limite) {}

//Definir Limite implementation
double ContaEspecial::definirLimite() {
    setLimite(getSalario()*getLimite());
    return limite;
}
//Conta Especial END

//Conta Poupança
class Poupanca : public Conta {
public:
  //Standard Constructor
  Poupanca();
  Poupanca(double taxa, int variacao);
  Poupanca(string nomeCliente, int num, double saldo, double taxa, int variacao);

  //Taxa
  double getTaxa();
  void setTaxa(double taxa);

  //Variacao
  int getVariacao();
  void setVariacao(int variacao);
  //Render 
  virtual double render();
private:
  double taxa;
  int variacao;
};
Poupanca::Poupanca() : Poupanca(0, 0) {}
Poupanca::Poupanca(double taxa, int variacao): Poupanca(vazio, 0, 0, taxa, variacao) {}
Poupanca::Poupanca(string nomeCliente, int num, double saldo, double taxa, int variacao) : Conta(nomeCliente, num, saldo) {
  setTaxa(taxa);
  setVariacao(variacao);
}
//Taxa implementation
double Poupanca::getTaxa() { return taxa; }
void Poupanca::setTaxa(double taxa) {
  this->taxa = taxa;
}
//Variacao implementation
int Poupanca::getVariacao() { return variacao; }
void Poupanca::setVariacao(int variacao) {
  this->variacao = variacao;
}
//Render implementation
double Poupanca::render() {
  double valor = 0;

  if(getVariacao() == 51) {
    valor = getSaldo()*(getTaxa()+1);
    setSaldo(valor);
  }
  else if (getVariacao() == 1) {
    valor = getSaldo()*(getTaxa()+1.005);
    setSaldo(valor);
  }
  
  return valor;
}
//Conta Poupança END

int main() {
  vector<Conta*> contas;
  string nome;
  int num;
  double deposito, saque, salario;

  for(int i = 0; i < 3; i++) {
    //Nome
    getline(cin, nome);
    //Numero
    cin >> num;
    //Salário
    if(i != 2) {
      cin >> salario;
    }
    //Conta corrente
    if(!i) {
      ContaCorrente *cc = new ContaCorrente(nome, num, SALDOINICIAL, salario, LIMITEPADRAO);
      contas.push_back(cc);
    } 
    //Conta Especial
    else if(i == 1) {
      ContaEspecial *cc = new ContaEspecial(nome, num, SALDOINICIAL, salario, LIMITEESPECIAL);
      contas.push_back(cc);
    } 
    //Conta poupanca
    else {
      Poupanca *cc = new Poupanca(nome, num, SALDOINICIAL, TAXAPADRAO, VARIACAO);
      contas.push_back(cc);
    }
    //Depósito
    cin >> deposito;
    contas[i]->depositar(deposito);
    //Saque
    cin >> saque;
    //Display info
    contas[i]->toString();
    //Saque
    contas[i]->sacar(saque);
    //cleaning buffer
    cin.ignore();
    //se a conta for poupança, irá render
    if(Poupanca* cp = dynamic_cast<Poupanca*>(contas[i])) {
      cp->render();
    }
    //Saldo total disponível
    cout << "saldo total disponível: R$ " << contas[i]->saldoTotalDisponivel() << endl;
  }
  
  return 0;
}
