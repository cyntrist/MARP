
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

#include "PriorityQueue.h"
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
bool resuelveCaso() {
	ll N;
	cin >> N;

	if (N <= 0)
		return false;

	PriorityQueue<ll> pq;
	for (ll i = 0; i < N; ++i)
	{
		ll e;
		cin >> e;
		pq.push(e);
	}

	ll resultado = 0;
	for (ll i = 0; i < N - 1; ++i)
	{
		ll a = pq.top(); pq.pop();
		ll b = pq.top(); pq.pop();
		resultado += (a + b);
		pq.push(a + b);
	}
	cout << resultado << '\n';

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
