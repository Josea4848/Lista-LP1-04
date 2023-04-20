#include <iostream>
#include <string>

using namespace std;

//IConta
class IConta {
public:
    //Virtual methods
    virtual double saldoTotalDisponivel() = 0;
    virtual void sacar(double valor) = 0;
    virtual void depositar(double valor) = 0;
};
//IConta END

const static string vazio  = "Vazio";

//Conta
class Conta : public IConta {
public:
    //Constructor
    Conta();
    Conta(string nome, string numeroConta, double salarioMensal);

    //Virtual methods
    virtual double saldoTotalDisponivel();
    virtual void sacar(double valor);
    virtual void depositar(double valor);

    //Gets
    double getSaldo();
    double getLimite();
    double getSalarioMensal();
    string getNome();
    string getNumeroConta();

    //Sets
    void setSaldo(double saldo);
    void setLimite(double limite);
    void setSalarioMensal(double salarioMensal);
    void setNome(string nomeCliente);
    void setNumeroConta(string numeroConta);

    //Other methods
    void definirLimite();

    //Destructor
    virtual ~Conta();
protected:
    double saldo, limite, salarioMensal;
    string nomeCliente, numeroConta;
};
//Constructors
Conta::Conta() : Conta(vazio, vazio, 0) {}
Conta::Conta(string nome, string numeroConta, double salarioMensal) {
    setNome(nome);
    setNumeroConta(numeroConta);
    setSalarioMensal(salarioMensal);
    setSaldo(0);
    definirLimite();
}

//Virtual implementation
double Conta::saldoTotalDisponivel() {
    return getSaldo() + getLimite();
}
void Conta::sacar(double valor) {
    if(valor <= saldoTotalDisponivel()) {
        saldo -= valor;
    } else {
        cerr << "Valor não disponível para saque";
    }
}
void Conta::depositar(double valor) {
    saldo += valor;
}

//Gets
double Conta::getSaldo() {
    return saldo;
}
double Conta::getLimite() {
    return limite;
}
double Conta::getSalarioMensal() {
    return salarioMensal;
}
string Conta::getNome(){
    return nomeCliente;
}
string Conta::getNumeroConta() {
    return numeroConta;
}

//Sets
void Conta::setSaldo(double saldo) {
    if(saldo >= 0)
        this->saldo = saldo;
    else
        this->saldo = 0;
}
void Conta::setLimite(double limite) {
    this->limite = limite;
}
void Conta::setSalarioMensal(double salarioMensal) {
    this->salarioMensal = salarioMensal;
}
void Conta::setNome(string nomeCliente) {
    if(nomeCliente != "")
        this->nomeCliente = nomeCliente;
    else {
        this->nomeCliente = vazio;
        cerr << "Nome não definido";
    }
}
void Conta::setNumeroConta(string numeroConta) {
    if(numeroConta != "") {
        this->numeroConta = numeroConta;
    } else {
        this->nomeCliente = vazio;
        cerr << "Número de conta não definido";
    }
}
//Other methods
void Conta::definirLimite() {
    setLimite(getSalarioMensal()*2);
}

Conta::~Conta() {}
//Conta END

//Conta Especial
class ContaEspecial : public Conta {
public:
    //Constructor
    ContaEspecial();
    ContaEspecial(string nome, string numeroConta, double salarioMensal);

    void definirLimite();

    //Destructor
    ~ContaEspecial();
};

//Constructors
ContaEspecial::ContaEspecial() : ContaEspecial(vazio, vazio, 0) {}
ContaEspecial::ContaEspecial(string nome, string numeroConta, double salarioMensal) : Conta(nome, numeroConta, salarioMensal) {
    definirLimite();
}
//DefinirLimite
void ContaEspecial::definirLimite() {
    setLimite(salarioMensal*3);
}
//Destructor
ContaEspecial::~ContaEspecial() {}

//Conta Especial END


int main() {
    string nomeConta, numeroConta;
    double salarioMensal, saque, deposito;
    Conta *conta1;
    ContaEspecial *conta2;

    for(int i = 0; i < 2; i++) {
        //GetName
        getline(cin, nomeConta);
        //GetnumeroConta
        getline(cin, numeroConta);
        //Salary
        cin >> salarioMensal;
        //Depósito
        cin >> deposito;
        //Saque
        cin >> saque;
        //Cleaning buffer
        cin.ignore();

        if(i == 0) {
            conta1 = new Conta(nomeConta, numeroConta, salarioMensal);
            conta1->depositar(deposito);
            conta1->sacar(saque);
        } else {
            conta2 = new ContaEspecial(nomeConta, numeroConta, salarioMensal);
            conta2->depositar(deposito);
            conta2->sacar(saque);
        }
    }

    //Display info
    cout << conta1->getNome() + ", cc: " + conta1->getNumeroConta()  << ", salário " << conta1->getSalarioMensal() << ", saldo total disponível: R$ " << conta1->saldoTotalDisponivel() << endl;
    cout << conta2->getNome() + ", cc: " + conta2->getNumeroConta()  << ", salário " << conta2->getSalarioMensal() << ", saldo total disponível: R$ " << conta2->saldoTotalDisponivel() << endl;


    return 0;
}
