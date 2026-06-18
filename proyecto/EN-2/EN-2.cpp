
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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

void beneficio(int N, int K, 
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
	int N = 0, K = 0;
	std::cin >> N >> K;

	if (!std::cin)  // fin de la entrada
		return false;

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
		while (j < i && areas[i] - areas[j] >= K) ++j;
		prev[i] = j - 1;
	}

	// prog dinam
	beneficio(N, K, m, beneficios, prev);

	// escribir la solución
	std::cout << m[N] << '\n';
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

	std::reverse(sol.begin(), sol.end());
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

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//std::cout << "Pulsa Intro para salir..." << std::flush;
	//std::cin.get();
#endif
	return 0;
}
