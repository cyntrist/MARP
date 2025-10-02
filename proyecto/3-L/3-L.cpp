
/*@ <authors>
 *
 * Cynthia Tristán Álvarez
 * MARP62
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "IndexPQ.h"
#include <map>
#include <string>
using namespace std;

/*@ <answer>



 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Canal {
	int id; 
	int audiencia; 
};

bool operator>(const Canal& a, const Canal& b) {

	return a.audiencia > b.audiencia || (a.audiencia == b.audiencia && a.id < b.id);
}

bool operator<(const Canal& a, const Canal& b) {

	return a.audiencia < b.audiencia || (a.audiencia == b.audiencia && a.id > b.id);
}

bool resuelveCaso() {

	int D, C, N; // D: duración en mins, C: cantidad de canales, N: número de actualizaciones
	cin >> D >> C >> N;

	if (!std::cin)  
		return false;

	IndexPQ<int, Canal, greater<Canal>> cola;
	map<int, int> mapa;

	for (int i = 0; i < C; i++)
	{ // audiencias minuto 0 (iniciales) de cada canal
		int audienciaMin0 = 0;
		cin >> audienciaMin0;
		Canal c = {i + 1, audienciaMin0};
		cola.push(i, c);
		//mapa[i + 1] = 0;
	}

	int minAnt = 0;
	Canal topAnterior = cola.top().prioridad;
	for (int i = 0; i < N; i++)
	{ // cada actualización
		int minAct, canal;
		cin >> minAct >> canal;

		int mins = minAct - minAnt;
		mapa[topAnterior.id - 1] += mins;
		minAnt = minAct;

		while (canal != -1)
		{
			int audiencia;
			cin >> audiencia;
			cola.update(canal - 1, {canal, audiencia});
			topAnterior = cola.top().prioridad;
			cin >> canal;
		}
	}

	for (const auto& canal : mapa)
	{
		cout << to_string(canal.first + 1) << " " << canal.second << endl;
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