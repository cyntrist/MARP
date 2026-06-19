
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

#include "Matriz.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

constexpr int INF = 1000000000; // con el max real pasa overflow al hacer temp entonces da la vuelta y el minimo es otro

void Floyd(Matriz<int> const& G, Matriz<int>& C) {
	int V = G.numfils(); // número de vértices de G
	// inicialización
	C = G;

	// actualizaciones de las matrices
	for (int k = 0; k < V; ++k) {
		for (int i = 0; i < V; ++i) {
			for (int j = 0; j < V; ++j) {
				auto temp = C[i][k] + C[k][j];
				C[i][j] = std::min(temp, C[i][j]); // es mejor pasar por k
			}
		}
	}
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N = 0;
	std::cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	Matriz G(N, N, INF);
	for (int i = 0; i < N; ++i)
		G[i][i] = 0;

	for (int i = 0; i < N - 1; ++i)
		for (int j = i + 1; j < N; ++j)
			std::cin >> G[i][j];

	// escribir la solución
	Matriz<int> C(N, N);
	Floyd(G, C);
	for (int i = 0; i < N - 1; ++i)
	{
		for (int j = i + 1; j < N; ++j)
			std::cout << C[i][j] << ' ';
		std::cout << '\n';
	}

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
	//std::cout << "Pulsa Intro para salir..." << std::flush;
	//std::cin.get();
#endif
	return 0;
}
