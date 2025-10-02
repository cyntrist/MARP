
/*@ <authors>
 *
 * Cynthia Tristán Álvarez
 * MARP62
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "IndexPQ.h"
using namespace std;

/*@ <answer>



 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Canal {
	int id; 
	int minutos; 
};

bool operator>(const Comic& a, const Comic& b) {

	return a.id > b.id;
}

bool resuelveCaso() {

	if (!std::cin)  
		return false;

	int D, C, N; // D: duración en mins, C: cantidad de canales, N: número de actualizaciones
	cin >> D >> C >> N;


	IndexPQ<int, Canal> cola;
	for (int i = 0; i < C; i++)
	{ // audiencias minuto 0 (iniciales) de cada canal
		int min0 = 0;
		cin >> min0;
		///
	}

	for (int i = 0; i < N; i++)
	{ // cada actualización
		int minAct, canal;
		cin >> minAct >> canal;

		while (canal != -1)
		{
			int mins;
			cin >> mins >> canal;
			///
		}
		///
	}


	cout << "---\n";
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