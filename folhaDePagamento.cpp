#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

#define N_FUNC 3

std::string doubleToStringWithPrecision(double value, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    return oss.str();
}

// FuncionarioNaoExisteException
class FuncionarioNaoExisteException : public exception {
private:
  string msg = "FuncionarioNaoExisteException ";
public:
  FuncionarioNaoExisteException(string nome) {
    msg += nome;
  }
  virtual string what() {
    return msg.c_str(); 
  }
};

// OrcamentoEstouradoException
class OrcamentoEstouradoException : public exception {
private:
  string msg = "OrcamentoEstouradoException ";
public:
  OrcamentoEstouradoException(double valor){
    msg += doubleToStringWithPrecision(valor,0);
  }
  virtual const char* what() {
    return msg.c_str();
  }
};

// Funcionario
class Funcionario {
public:
  Funcionario();
  Funcionario(string nome, int matricula);

  // Gets
  string getNome();
  int getMatricula();
  // Sets
  void setNome(string nome);
  void setMatricula(int matricula);

  // Calcula salário
  virtual double calculaSalario() = 0;

protected:
  string nome;
  int matricula;
};
Funcionario::Funcionario() : Funcionario("vazio", 0) {}
Funcionario::Funcionario(string nome, int matricula) {
  setNome(nome);
  setMatricula(matricula);
}
string Funcionario::getNome() { return nome; }
int Funcionario::getMatricula() { return matricula; }
void Funcionario::setNome(string nome) { this->nome = nome; }
void Funcionario::setMatricula(int matricula) { this->matricula = matricula; }
// Funcionario END

// Assalariado
class Assalariado : public Funcionario {
public:
  Assalariado();
  Assalariado(string nome, int matricula, double salario);

  double calculaSalario();
  void setSalario(double salario);



private:
  double salario;
};
Assalariado::Assalariado() : Assalariado("none", 0, 0.0) {}
Assalariado::Assalariado(string nome, int matricula, double salario) : Funcionario(nome, matricula) {
  setSalario(salario);
}
void Assalariado::setSalario(double salario) { this->salario = salario; }
double Assalariado::calculaSalario() { return salario;}
// Assalariado END

// Horista
class Horista : public Funcionario {
public:
  Horista();
  Horista(string nome, int matricula, double salarioPorHora,
          double horasTrabalhadas);

  // sets
  void setSalarioPorHora(double valor);
  void setHorasTrabalhadas(double valor);

  // gets
  double getSalarioPorHora();
  double getHorasTrabalhadas();
  // calcula salário
  double calculaSalario();

private:
  double salarioPorHora, horasTrabalhadas;
};
Horista::Horista() {}
Horista::Horista(string nome, int matricula, double salarioPorHora,
                 double horasTrabalhadas)
    : Funcionario(nome, matricula) {
  setSalarioPorHora(salarioPorHora);
  setHorasTrabalhadas(horasTrabalhadas);
}

// sets
void Horista::setSalarioPorHora(double valor) {
  if (valor > 0)
    salarioPorHora = valor;
  else
    throw 3;
}
void Horista::setHorasTrabalhadas(double valor) {
  if (valor >= 0)
    horasTrabalhadas = valor;
  else
    throw 4;
}
// gets
double Horista::getSalarioPorHora() { return salarioPorHora; }
double Horista::getHorasTrabalhadas() { return horasTrabalhadas; }

double Horista::calculaSalario() {
  if(getHorasTrabalhadas() <= 40)
    return getSalarioPorHora()*getHorasTrabalhadas()*4;
  else 
    return getSalarioPorHora()*160 + (getHorasTrabalhadas()-40)*getSalarioPorHora()*1.5*4;
}

// Horista END
// Comissionado
class Comissionado : public Funcionario {
public:
  // Construtores
  Comissionado();
  Comissionado(string nome, int matricula, double vendasMensais,
               double percentualComissao);

  // Calcula salário
  double calculaSalario();

  // sets
  void setVendasMensais(double vendasMensais);
  void setPercentual(double percentualComissao);

  // Gets
  double getVendasMensais();
  double getPercentual();
private:
  double vendasMensais, percentualComissao;
};
Comissionado::Comissionado() {}
Comissionado::Comissionado(string nome, int matricula, double vendasMensais, double percentualComissao) : Funcionario(nome, matricula) {
  setVendasMensais(vendasMensais);
  setPercentual(percentualComissao);
}

void Comissionado::setVendasMensais(double vendasMensais) {
  if (vendasMensais >= 0)
    this->vendasMensais = vendasMensais;
  else
    throw 5;
}
void Comissionado::setPercentual(double percentualComissao) {
  if (percentualComissao > 0)
    this->percentualComissao = percentualComissao;
  else
    throw 6;
}

double Comissionado::getVendasMensais() { return vendasMensais; }
double Comissionado::getPercentual() { return percentualComissao; }

double Comissionado::calculaSalario() {
  return getVendasMensais()*getPercentual();
}
// Comissionado END

// SistemaGerenciaFolha
class SistemaGerenciaFolha {
public:
  SistemaGerenciaFolha(double orcamento);

  // Set funcionários
  void setFuncionarios(Funcionario* funcionario);
  // valor Total SistemaGerenciaFolha
  double calculaValorTotalFolha();
  // consulta salário
  double consultaSalarioFuncionario(string nome);

private:
  vector<Funcionario *> funcionarios;
  double orcamento;
};

SistemaGerenciaFolha::SistemaGerenciaFolha(double orcamento) {
  this->orcamento = orcamento;
}
// set funcionários
void SistemaGerenciaFolha::setFuncionarios(Funcionario* funcionario) {
  funcionarios.push_back(funcionario);
}
// valor Total SistemaGerenciaFolha
double SistemaGerenciaFolha::calculaValorTotalFolha() {
  double total = 0;
  for (Funcionario *funcionario : funcionarios) {
    total += funcionario->calculaSalario();
  }

  if (total > orcamento) {
    throw new OrcamentoEstouradoException(total);
  } else {
    return total;
  }
}
// consulta salário
double SistemaGerenciaFolha::consultaSalarioFuncionario(string nome) {
  for (Funcionario *funcionario : funcionarios) {
    if (funcionario->getNome() == nome) {
      return funcionario->calculaSalario();
    }
  }

  throw new FuncionarioNaoExisteException(nome);
}
// SistemaGerenciaFolha END
int main() {
    double limite;
    SistemaGerenciaFolha *s;
    vector<Funcionario*> funcionarios;
    string nome;
    int matricula, horasTrabalhadas;
    double salario, comissao, vendas, salarioPorHora;

    //limite 
    cin >> limite;

    s = new SistemaGerenciaFolha(limite);

    for (int i = 0; i < N_FUNC; i++) {
      cin.ignore();
      //nome
      getline(cin, nome);
      //matricula
      cin >> matricula;
      if(i == 0) {
        cin >> salario;
        funcionarios.push_back(new Assalariado(nome, matricula, salario));
      } 
      else if (i == 1) {
        cin >> salarioPorHora;
        cin >> horasTrabalhadas;
        funcionarios.push_back(new Horista(nome, matricula, salarioPorHora, horasTrabalhadas));
      } else {
        cin >> vendas;
        cin >> comissao;
        cin.ignore();
        funcionarios.push_back(new Comissionado(nome, matricula, vendas, comissao));
      }

      s->setFuncionarios(funcionarios[i]);
    }

    for(int i = 0; i < N_FUNC; i++) {
      getline(cin, nome);
      try {
        cout << s->consultaSalarioFuncionario(nome) << endl;
      } catch(FuncionarioNaoExisteException *f) {
        cout << f->what() << endl;
      }
    }

    try {
      cout << s->calculaValorTotalFolha();
    } catch(OrcamentoEstouradoException *o) {
      cout << o->what() << endl;
    }

    return 0;
}