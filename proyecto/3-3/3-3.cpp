
/*@ <authors>
 *
 * Cynthia Tristán Álvarez
 * MARP62
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

/*@ <answer>



 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Tarea
{
	bool periodica;
	int ini, fin, intervalo;
};

bool operator<(Tarea const& a, Tarea const& b)
{
	return b.ini < a.ini;
}

bool resuelveCaso() {
	int N, M, T;
	cin >> N >> M >> T;

	if (!cin)  
		return false;

	priority_queue<Tarea> cola;
	int ini, fin, intervalo;
	for (int i = 0; i < N; ++i)
	{
		cin >> ini >> fin;
		cola.push({false, ini, fin, 0});
	}

	for (int i = 0; i < M; ++i)
	{
		cin >> ini >> fin >> intervalo;
		cola.push({true, ini, fin, intervalo});
	}

	bool conflicto = false;
	int ocupado = 0;
	while (!conflicto && !cola.empty() && cola.top().ini < T)
	{
		auto [periodica, ini, fin, intervalo]  = cola.top(); cola.pop();
		conflicto = ini < ocupado;
		ocupado = fin;
		if (periodica)
			cola.push({true, ini + intervalo, fin + intervalo, intervalo});
	}

	cout << (conflicto ? "SI" : "NO") << endl ;
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