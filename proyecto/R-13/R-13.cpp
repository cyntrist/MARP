/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Matriz.h"
 //#include <...>

using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

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

struct Bombilla
{
	int potencia;
	int coste;
};

// mochila no acotada ascendete
// m[i][j] = coste mínimo de conseguir la potencia j con bombillas hasta i
int coste(int N, int M, const std::vector<Bombilla>& bombillas)
{
	Matriz m(N + 1, M + 1, INF);

	for (int i = 0; i <= N; ++i)
		m[i][0] = 1;

	for (int i = 1; i <= N; ++i)
	{
		const auto& b = bombillas[i - 1];
		for (int j = 1; j <= M; ++j)
		{
			// no usar esa bombilla
			m[i][j] = m[i - 1][j];

			if (j >= b.potencia && m[i][j - b.potencia] != INF)
				m[i][j] = std::min(m[i][j], m[i][j - b.potencia] + b.coste);
		}
	}

	return m[N][M];
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N = 0, PMax = 0, PMin = 0;
	std::cin >> N >> PMax >> PMin;

	if (!std::cin) return false;

	// resolver el caso posiblemente llamando a otras funciones
	std::vector<Bombilla> bombillas(N);

	for (auto& b : bombillas)
		std::cin >> b.potencia;

	for (auto& b : bombillas)
		std::cin >> b.coste;

	// escribir la solución
	auto c = coste(N, PMax, bombillas);
	std::cout << (c != INF ? std::to_string(c) : "IMPOSIBLE") << '\n';

	// reconstruccion

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

	// para dejar todo como estaba al principio y parar antes de salir
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif

	return 0;
}
