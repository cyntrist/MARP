/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

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

// m[i][j] = combinaciones posibles de conseguir el número j con números hasta el i
int combinaciones(int k, int s)
{
	//Matriz m(k + 1, s + 1, 0);
	std::vector<int> m(s + 1, 0);

	m[0] = 1; // solo 1 unica manera de conseguir 0

	for (int i = 1; i <= k; ++i)
	{
		for (int j = i; j <= s; ++j)
		{
			m[j] += m[j - i];
		}
	}

	return m[s];
}

void resuelveCaso() {
	// leer los datos de la entrada
	int k = 0, s = 0;
	std::cin >> k >> s;

	// resolver el caso posiblemente llamando a otras funciones

	// escribir la solución
	std::cout << combinaciones(k, s) << '\n';
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

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio y parar antes de salir
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif

	return 0;
}
