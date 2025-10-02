
/*@ <authors>
 *
 * Cynthia Tristán Álvarez
 * MARP62
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "IndexPQ.h"
#include <string>
using namespace std;

/*@ <answer>



 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Pajaro {
	long edad;
};

bool operator>(const Pajaro& a, const Pajaro& b) {

	return a.edad > b.edad;
}

bool operator<(const Pajaro& a, const Pajaro& b) {

	return a.edad < b.edad;
}

bool resuelveCaso() {
	int N; 
	long primero;
	cin >> primero >> N;

	if (primero == 0 || N == 0)  
		return false;

	IndexPQ<int, Pajaro> cola;
	for (int i = 0; i < N; i++)
	{
		long edad;
		cin >> edad;
		cola.push(i, {edad});
		cout << cola.priority(cola.size()/2 + 1).edad << endl;
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