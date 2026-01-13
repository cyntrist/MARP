
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include "Matriz.h"
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
constexpr int INF = std::numeric_limits<int>::max();

int unir_pdfs(vector<int> const& pdfs) { 
	int n = pdfs.size();

	vector pref(n + 1, 0);
	for (int i = 1; i <= n; ++i)
		pref[i] = pref[i - 1] + pdfs[i - 1];

	Matriz m(n + 1, n + 1, 0); 
	for (int len = 1; len < n; ++len) // recorre diagonales
	{
		for (int i = 1; i + len <= n; ++i) { // recorre elementos de diagonal
			int j = i + len;
			m[i][j] = INF;
			for (int k = i; k <= j - 1; ++k) {
				m[i][j] = std::min(
					m[i][k] + m[k + 1][j] + pref[j] - pref[i - 1],
					m[i][j]
				);
			}
		}
	}
	return m[1][n];
}

bool resuelveCaso() {
	int N;
	cin >> N;	
	if (N == 0)  // fin de la entrada
		return false;
	vector<int> pdfs(N);
	for (int i = 0; i < N; ++i)
		cin >> pdfs[i];

	cout << unir_pdfs(pdfs) << '\n';

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	if (!in.is_open())
		std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif
	return 0;
}
