#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Función para calcular la puntuación esperada entre dos dados
double score(const vector<int>& A, const vector<int>& B) {
    int n = A.size();
    int m = B.size();
    double total = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (A[i] > B[j]) total += 1.0;
            else if (A[i] == B[j]) total += 0.5;
        }
    }
    return total / (n * m);
}

int main() {
    int n, m;
    cin >> n;
    vector<int> D1(n);
    for (int i = 0; i < n; ++i) {
        cin >> D1[i];
    }

    cin >> m;
    vector<int> D2(m);
    for (int i = 0; i < m; ++i) {
        cin >> D2[i];
    }

    double D1_D2_score = score(D1, D2);
    double D2_D1_score = score(D2, D1);

    // Asegurarse de que D1 tiene ventaja sobre D2
    if (D1_D2_score <= D2_D1_score) {
        swap(D1, D2);
        swap(n, m);
    }

    // Buscar D3 tal que puntaje(D3, D2) es lo más bajo posible
    // y puntaje(D3, D1) es lo más alto posible.
    vector<int> possible_faces = D1; // Un candidato inicial es usar las caras de D1
    possible_faces.insert(possible_faces.end(), D2.begin(), D2.end());
    sort(possible_faces.begin(), possible_faces.end());

    double min_score_D3_D2 = 1.0;
    double max_score_D3_D1 = 0.0;

    for (int face : possible_faces) {
        vector<int> D3 = {face};
        min_score_D3_D2 = min(min_score_D3_D2, score(D3, D2));
        max_score_D3_D1 = max(max_score_D3_D1, score(D3, D1));
    }

    cout << fixed << setprecision(6) << min_score_D3_D2 << " " << max_score_D3_D1 << endl;

    return 0;
}
