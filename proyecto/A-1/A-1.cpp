
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "EnterosInf.h"

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

// número total de maneras de conseguir esa cuerda, 
int total(vector<int> const& longs, int N, int L)
{
	
} 

// mínimo número posible de cuerdas a utilizar
int minimo(vector<int> const& longs, int N, int L)
{

}

// mínimo coste necesario
int coste(vector<int> const& longs, vector<int> const& costs, int N, int L)
{

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

	int t = total(longitudes, N, L);
	if (t > 0)
	{
		int m = minimo(longitudes, N, L);
		int c = coste(longitudes, costes, N, L);
		cout << "SI " << t << " " << m << " " << c;
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
