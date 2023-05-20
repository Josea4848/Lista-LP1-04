#include <iostream>
#include <vector>
#include <string>

using namespace std;

//Pedido
class Pedido {
public:
  Pedido(float valor, int quant);
  float getTotal() {return valor*quant;};
  void toString();
private:
  float valor;
  int quant;
};
Pedido::Pedido(float valor, int quant) {
  this->valor = valor;
  this->quant = quant;
}
void Pedido::toString() {
  cout << "R$ " << valor << ", quant: " << quant << ", total: R$ " << getTotal() << endl;
}
//Pedido END

//Livro
class Livro {
public:
  Livro(string tituloLivro, int paginas);

  int getTotal() {return paginas;};
  void toString();
private:
  string tituloLivro;
  int paginas;
};
Livro::Livro(string tituloLivro, int paginas) {
  this->tituloLivro = tituloLivro;
  this->paginas = paginas;
}
void Livro::toString() {
  cout << tituloLivro << ", páginas: " << paginas << endl;
}
//Livro END

//Estatisticas TEMPLATE
template <class T> class Estatisticas {
public:
  int indexOfMaior(vector<T> vec);
  int indexOfMenor(vector<T> vec);
  float media(vector<T> vec);
};
template <class T> int Estatisticas<T>::indexOfMaior(vector<T> vec) {
  int maiorIndex = 0;
  for(int i = 0; i < vec.size(); i++) {
    if(vec[i].getTotal() > vec[maiorIndex].getTotal())
      maiorIndex = i;
  }
  return maiorIndex;
}

template <class T> int Estatisticas<T>::indexOfMenor(vector<T> vec) {
  int menorIndex = 0;
  for(int i = 0; i < vec.size(); i++) {
    if(vec[i].getTotal() < vec[menorIndex].getTotal())
      menorIndex = i;
  }
  return menorIndex;
}

template <class T> float Estatisticas<T>::media(vector<T> vec) {
  float total = 0;
  for(T classe: vec) {
    total += classe.getTotal();
  }

  return total/vec.size();
}
//TEMPLATE end

int main() {
  int nLivros, nPedidos;
  vector<Pedido> pedidos;
  vector<Livro> livros;

  //Número de pedidos
  cin >> nPedidos;

  for(int i = 0; i < nPedidos; i++) {
    float valor;
    int quant;

    //Valor
    cin >> valor;
    //Quantidade
    cin >> quant;

    pedidos.push_back(Pedido(valor, quant));
  }

  //Número de livros
  cin >> nLivros;

  for(int i = 0; i < nLivros; i++) {
    int paginas;
    string titulo;

    cin.ignore();
    //Título
    getline(cin, titulo);
    //Páginas
    cin >> paginas;

    livros.push_back(Livro(titulo, paginas));
  }

  Estatisticas<Pedido> estatisticaPedido;

  int pedidosMaior = estatisticaPedido.indexOfMaior(pedidos);
  int pedidosMenor = estatisticaPedido.indexOfMenor(pedidos);
  float mediaPedidos = estatisticaPedido.media(pedidos);

  cout << "Maior: ";
  pedidos[pedidosMaior].toString();
  cout << "Menor: ";
  pedidos[pedidosMenor].toString();
  cout << "Média: " << mediaPedidos << endl;

  Estatisticas<Livro> estatisticaLivro;

  int livroMaior = estatisticaLivro.indexOfMaior(livros);
  int livroMenor = estatisticaLivro.indexOfMenor(livros);
  float livroMedia = estatisticaLivro.media(livros);

  cout << "Maior: ";
  livros[livroMaior].toString();
  cout << "Menor: ";
  livros[livroMenor].toString();
  cout << "Média: " << livroMedia << endl;

  return 0;
}