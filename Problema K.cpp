#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>

using namespace std;

// Función para calcular la probabilidad de formar una palabra con las letras dadas
double probabilidadPalabra(const vector<char>& letras, const unordered_set<string>& palabras) {
  int numPalabras = 0;
  string palabraActual;

  for (const char& letra : letras) {
    palabraActual += letra;

    // Si la palabra actual está en el diccionario, se incrementa el contador
    if (palabras.find(palabraActual) != palabras.end()) {
      numPalabras++;
    }
  }

  // Se calcula la probabilidad
  return (double) numPalabras / (double) palabras.size();
}

// Función para calcular el número esperado de tiradas
double numeroEsperadoTiras(int d, int w, const vector<vector<char>>& dados, const unordered_set<string>& palabras) {
  // Se crea una cola para almacenar las configuraciones de dados
  queue<pair<vector<char>, int>> cola;

  // Se agrega la configuración inicial a la cola
  vector<char> letrasIniciales(d);
  for (int i = 0; i < d; i++) {
    letrasIniciales[i] = dados[i][0];
  }
  cola.push({letrasIniciales, 0});

  // Se calcula el número esperado de tiradas
  double esperado = 0.0;
  while (!cola.empty()) {
    // Se obtiene la siguiente configuración de la cola
    auto configuracionActual = cola.front();
    cola.pop();

    vector<char> letrasActuales = configuracionActual.first;
    int tiradasActuales = configuracionActual.second;

    // Se calcula la probabilidad de formar una palabra con las letras actuales
    double probabilidad = probabilidadPalabra(letrasActuales, palabras);

    // Si se puede formar una palabra, se actualiza el valor esperado
    if (probabilidad > 0.0) {
      esperado += (double) tiradasActuales + (1.0 / probabilidad);
      break;
    }

    // Se exploran las siguientes configuraciones
    for (int i = 0; i < d; i++) {
      for (int j = 1; j < dados[i].size(); j++) {
        vector<char> nuevasLetras = letrasActuales;
        nuevasLetras[i] = dados[i][j];
        cola.push({nuevasLetras, tiradasActuales + 1});
      }
    }
  }

  return esperado;
}

int main() {
  // Se lee la entrada
  int d, w;
  cin >> d >> w;

  vector<vector<char>> dados(d);
  for (int i = 0; i < d; i++) {
    dados[i].resize(6);
    for (int j = 0; j < 6; j++) {
      cin >> dados[i][j];
    }
  }

  unordered_set<string> palabras;
  for (int i = 0; i < w; i++) {
    string palabra;
    cin >> palabra;
    palabras.insert(palabra);
  }

  // Se calcula el número esperado de tiradas
  double esperado = numeroEsperadoTiras(d, w, dados, palabras);

  // Se imprime la salida
  if (esperado < 1e9) {
    cout << esperado << endl;
  } else {
    cout << "imposible" << endl;
  }

  return 0;
}
