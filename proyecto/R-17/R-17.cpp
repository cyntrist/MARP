// R-17.cpp : Este archivo contiene la función "main". La ejecución del programa 
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

bool resuelveCaso() {
	int N;
	cin >> N;

	if (!std::cin)
		return false;

	priority_queue<int> pq;
	for (int i = 0; i < N; ++i)
	{
		int p;
		cin >> p;
		pq.push(p);
	}

	int resultado = 0;
	int n = pq.size();
	while (pq.size() >= 3)
	{
		pq.pop();
		pq.pop();
		int c = pq.top(); pq.pop();
		resultado += c;
		n -= 3;
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
