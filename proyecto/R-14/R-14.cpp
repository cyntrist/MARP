/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//#include <...>

using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el costes de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

constexpr int INF = 1000000000; // con el max real pasa overflow al hacer temp entonces da la vuelta y el minimo es otro

void beneficio(int N,
	std::vector<int>& m, const std::vector<int>& beneficios,
	const std::vector<int>& prev)
{
	for (int i = 1; i <= N; ++i)
	{
		int ir = i - 1; // indice real del area
		int no_coger = m[i - 1]; // beneficio anterior
		int coger = beneficios[ir] + m[prev[ir] + 1]; // beneficio de este area
		m[i] = std::max(coger, no_coger);
	}
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N = 0, S = 0;
	std::cin >> N >> S;

	if (!std::cin) return false;

	// resolver el caso posiblemente llamando a otras funciones
	std::vector<int> areas(N);
	for (auto& k : areas)
		std::cin >> k;

	std::vector<int> beneficios(N);
	for (auto& b : beneficios)
		std::cin >> b;

	std::vector<int> m(N + 1, 0); // maximo beneficio obtenible hasta el area i
	std::vector<int> prev(N, -1); // para el área de índice i, prev[i] = índice j < i del área más cercana compatible con la restricción de distancia, es decir: pos[i] - pos[j] >= K

	// calculo del area previa
	int j = 0;
	for (int i = 0; i < N; ++i)
	{
		while (j < i && areas[i] - areas[j] >= S) ++j;
		prev[i] = j - 1;
	}

	// prog dinam
	beneficio(N, m, beneficios, prev);

	// escribir la solución
	std::cout << m[N] << ": ";
	// reconstrucción
	int i = N;
	std::vector<int> sol;
	while (i > 0)
	{
		int ir = i - 1;
		if (m[i] != m[i - 1]) // ese area fue usada
		{
			sol.push_back(areas[ir]);
			i = prev[ir] + 1;
		}
		else
		{
			--i;
		}
	}

	std::ranges::reverse(sol);
	for (const auto s : sol)
		std::cout << s << ' ';
	std::cout << '\n';

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
