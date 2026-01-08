
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Matriz.h"
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

using ll = long long;
// número total de maneras de conseguir esa cuerda, 
ll total(vector<int> const& longs, int const L)
{
	int N = longs.size();
	Matriz<ll> cuerdas(N + 1, L + 1, 0);
	cuerdas[0][0] = 1;
	for (int i = 1; i <= N; ++i)
	{
		cuerdas[i][0] = 1;
		for (int j = 1; j <= L; ++j)
		{
			if (j < longs[i - 1])
				cuerdas[i][j] = cuerdas[i - 1][j];
			else
				cuerdas[i][j] = cuerdas[i - 1][j] + cuerdas[i - 1][j - longs[i - 1]];
		}
	}
	return cuerdas[N][L];
} 

// mínimo número posible de cuerdas a utilizar
ll minimo(vector<int> const& longs, int const L)
{
	int N = longs.size();
	Matriz<ll> cuerdas(N + 1, L + 1, 1e9);
	cuerdas[0][0] = 0;
	for (int i = 1; i <= N; ++i)
	{
		cuerdas[i][0] = 0;
		for (int j = 1; j <= L; ++j)
		{
			if (longs[i - 1] > j)
				cuerdas[i][j] = cuerdas[i - 1][j];
			else
				cuerdas[i][j] = std::min(
					cuerdas[i - 1][j], 
					cuerdas[i - 1][j - longs[i - 1]] + 1
				);
		}
	}
	return cuerdas[N][L];
}

// mínimo coste necesario
ll coste(vector<int> const& longs, vector<int> const& costs, int const L)
{
	int N = longs.size();
	Matriz<ll> cuerdas(N + 1, L + 1, 1e9);
	cuerdas[0][0] = 0;
	for (int i = 1; i <= N; ++i)
	{
		cuerdas[i][0] = 0;
		for (int j = 1; j <= L; ++j)
		{
			if (longs[i - 1] > j)
				cuerdas[i][j] = cuerdas[i - 1][j];
			else
				cuerdas[i][j] = std::min(
					cuerdas[i - 1][j - longs[i - 1]] + costs[i - 1],
					cuerdas[i - 1][j]
				);
		}
	}
	return cuerdas[N][L];
}

// hacer J decreciente (de derecha a izq) significa no reusar la misma cuerda
// hacerlo creciente significaría usar la misma cuerda recursivamente pq:
// [ j++ -> fila i   |   fila i - 1 <- --j ] 
// el vector (creo que) en la matriz representa esencialmente:
// fila i - 1:			[-------]
// fila i    :  [------]

ll total_optimizado(vector<int> const& longs, int const L)
{
	int N = longs.size();
	vector<ll> cuerdas(L + 1, 0);
	cuerdas[0] = 1;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = L; j >= longs[i - 1]; --j)
		{
			cuerdas[j] = cuerdas[j] + cuerdas[j - longs[i - 1]];
		}
	}
	return cuerdas[L];
}

ll minimo_optimizado(vector<int> const& longs, int const L)
{
	int N = longs.size();
	vector<ll> cuerdas(L + 1, 1e9);
	cuerdas[0] = 0;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = L; j >= longs[i - 1]; --j)
		{
			cuerdas[j] = std::min(
				cuerdas[j], 
				cuerdas[j - longs[i - 1]] + 1
			);
		}
	}
	return cuerdas[L];
}

ll coste_optimizado(vector<int> const& longs, vector<int> const& costs, int const L)
{
	int N = longs.size();
	vector<int> cuerdas(L + 1, 1e9);
	cuerdas[0] = 0;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = L; j >= longs[i - 1]; --j) 
		{ 
			cuerdas[j] = std::min(
					cuerdas[j - longs[i - 1]] + costs[i - 1],
					cuerdas[j]
				);
		}
	}
	return cuerdas[L];
}

bool resuelveCaso() {
	int N, L;
	cin >> N >> L;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<int> longitudes(N);
	vector<int> costes(N);
	for (int i = 0; i < N; ++i)
	{
		int lon, cost;
		cin >> lon >> cost;
		longitudes[i] = lon;
		costes[i] = cost;
	}

	ll t = total_optimizado(longitudes, L);
	if (t > 0)
	{
		ll m = minimo_optimizado(longitudes, L);
		ll c = coste_optimizado(longitudes, costes, L);
		cout << "SI " << t << " " << m << " " << c << '\n';
	}
	else cout << "NO\n";

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
