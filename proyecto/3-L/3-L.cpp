
/*@ <authors>
 *
 * Cynthia Tristán Álvarez
 * MARP62
 *
 *@ </authors> */

#include <algorithm>
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

bool resuelveCaso() {

	int D, C, N; // D: duración en mins, C: cantidad de canales, N: número de actualizaciones
	cin >> D >> C >> N;

	if (!cin)  
		return false;

	//IndexPQ<int, Canal, greater<>> cola;
	IndexPQ<int, int, greater<>> espectadores;
	//map<int, int> mapa;
	unordered_map<int, int> minutos;

	for (int i = 0; i < C; ++i)
	{ // audiencias minuto 0 (iniciales) de cada canal
		int esp; cin >> esp;
		//Canal c = {i + 1, esp};
		espectadores.update(i, esp);
	}

	int minAnt = 0;
	for (int i = 0; i < N; ++i)
	{ // cada actualización
		int minAct, canal;
		cin >> minAct >> canal;
		minutos[espectadores.top().elem] += minAct - minAnt;

		//int mins = minAct - minAnt;
		//mapa[topAnterior.id - 1] += mins;
		//minAnt = minAct;

		while (canal != -1)
		{
			//int audiencia;
			//cin >> audiencia;
			//espectadores.update(canal - 1, {canal, audiencia});
			//topAnterior = espectadores.top().prioridad;
			//cin >> canal;

			int esp; cin >> esp;
			espectadores.update(canal - 1, esp);
			cin >> canal;
		}

		minAnt = minAct;
	}

	// actualización final
	int mins = D - minAnt;
	minutos[espectadores.top().elem] += mins;

	// salida
	//for (const auto& canal : espectadores)
	//	cout << to_string(canal.first + 1) << " " << canal.second << endl;

	vector<pair<int,int>> sol;
	for (auto p : minutos)
		sol.emplace_back(p.first, p.second);

	sort(sol.begin(), sol.end(), 
		[](pair<int, int> a, pair<int,int> b)
		{
			return a.second > b.second || (a.second == b.second && a.first < b.first);
		}
	);

	for (auto p : sol)
	{
		cout << (p.first + 1) << ' ' << p.second << endl;
	}

	// zzz
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