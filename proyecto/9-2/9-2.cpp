
	/*@ <authors>
	 *
	 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
	 *
	 *@ </authors> */

#include <algorithm>
	#include <iostream>
	#include <fstream>
	#include <queue>
	#include <string>
	#include <vector>

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

	struct Trabajo
	{
		int ini, fin;
	};

	bool operator<(Trabajo const& a, Trabajo const& b)
	{
		return a.ini >= b.ini;
	}

	using Trabajos = vector<Trabajo>;
	int minimo(Trabajos const& trabajos, int C, int F)
	{
		if (trabajos.empty()) return 0;
		int i = 0;
		int actual = C;
		int n_trabajos = 0;
		while (actual < F)
		{
			int mejor = actual;
			while (i < trabajos.size() && trabajos[i].ini <= actual)
			{
				mejor = max(mejor, trabajos[i].fin);
				++i;
			}
			if (mejor == actual) return -1;
			actual = mejor;
			++n_trabajos;
		}
		return n_trabajos;
	}

	bool resuelveCaso() {
		int C, F, N;
		cin >> C >> F >> N;

		if (C == 0 && F == 0 && N == 0)  // fin de la entrada
			return false;

		Trabajos trabajos;
		for (int i = 0; i < N; i++)
		{
			int ini, fin;
			cin >> ini >> fin;
			trabajos.push_back({ ini, fin });
			//trabajos.push({ ini,fin });
		}

		sort(trabajos.begin(), trabajos.end(),
			[](auto const& a, auto const& b) {
				return a.ini < b.ini;
			});
		int min = minimo(trabajos, C, F);
		cout << (min <= 0 ? "IMPOSIBLE" : to_string(min)) << '\n';

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
