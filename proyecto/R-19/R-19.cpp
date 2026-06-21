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

bool resuelveCaso() {
	// leer los datos de la entrada
	int N = 0;
	std::cin >> N;

	if (!std::cin) return false;

	// resolver el caso posiblemente llamando a otras funciones
	int duracion_total = 0;
	std::vector<int> duraciones(N);
	for (auto& d : duraciones)
	{
		std::cin >> d;
		duracion_total += d;
	}

	int mitad = duracion_total * 0.5f;
	vector m(mitad + 1, false);
	m[0] = true;

	for (const auto d : duraciones)
	{
		for (int j = mitad; j >= d; --j)
		{
			if (m[j - d]) m[j] = true;
		}
	}

	int mejor = 0;
	for (int j = mitad; j > 0; --j)
	{
		if (m[j])
		{
			mejor = j;
			break;
		}
	}


	// escribir la solución
	std::cout << (duracion_total - mejor) << '\n';

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
