#include <iostream>
#include <vector>

using namespace std;

// Función para calcular el siguiente elemento de la secuencia
int siguiente_elemento(const vector<int>& coeficientes, const vector<int>& valores_iniciales, int i) {
  int siguiente = 0;
  for (int j = 0; j < coeficientes.size(); j++) {
    siguiente += coeficientes[j] * valores_iniciales[i - j - 1];
  }
  return siguiente;
}

// Función para generar los primeros 10 elementos de la secuencia
vector<int> generar_secuencia(const vector<int>& coeficientes, const vector<int>& valores_iniciales) {
  vector<int> secuencia(valores_iniciales);
  for (int i = valores_iniciales.size(); i < 10; i++) {
    secuencia.push_back(siguiente_elemento(coeficientes, secuencia, i));
  }
  return secuencia;
}

// Función para imprimir la secuencia PLRR
void imprimir_secuencia(const int& orden, const vector<int>& coeficientes, const vector<int>& valores_iniciales, const vector<int>& secuencia) {
  cout << "Orden: " << orden << endl;
  cout << "Coeficientes: ";
  for (int c : coeficientes) {
    cout << c << " ";
  }
  cout << endl;
  cout << "Valores iniciales: ";
  for (int a : valores_iniciales) {
    cout << a << " ";
  }
  cout << endl;
  cout << "Primeros 10 elementos: ";
  for (int s : secuencia) {
    cout << s << " ";
  }
  cout << endl;
}

// Función principal
int main() {
  int n; // Número de la tarjeta
  cin >> n;

  // Procesamiento del índice de la tarjeta
  int orden, i, j;
  vector<int> coeficientes, valores_iniciales;

  // Calcular orden, coeficientes y valores iniciales a partir del índice de la tarjeta
  i = 1;
  orden = 1;
  while (i * orden < n) {
    orden++;
    i *= orden;
  }
  n -= i * (orden - 1);
  i = n;
  for (j = orden - 1; j >= 0; j--) {
    coeficientes.push_back(i % (orden - j));
    i /= (orden - j);
  }
  for (j = 0; j < orden; j++) {
    valores_iniciales.push_back(n % (orden + 1));
    n /= (orden + 1);
  }

  // Generar y imprimir la secuencia PLRR
  vector<int> secuencia = generar_secuencia(coeficientes, valores_iniciales);
  imprimir_secuencia(orden, coeficientes, valores_iniciales, secuencia);

  return 0;
}
