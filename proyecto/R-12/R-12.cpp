
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "IndexPQ.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Bateria
{
	int carga;
	int tope;
};

bool resuelveCaso() {
	int B = 0;
	std::cin >> B;

	if (!std::cin)  // fin de la entrada
		return false;

	IndexPQ<int, int, std::greater<int>> pq();

	std::vector<int> duraciones(B);
	for (auto& d : duraciones)
		std::cin >> d;

	int R = 0;
	std::cin >> R;

	std::vector<int> repuestos(R);
	for (auto& r : repuestos)
		std::cin >> r;

	int Z = 0, T = 0;
	std::cin >> Z >> T;

	while (T--)
	{
		
	}

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
