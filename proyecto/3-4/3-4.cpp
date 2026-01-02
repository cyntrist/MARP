
/*@ <authors>
 *
 * Cynthia Tristán Álvarez
 * MARP62
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

#include "IndexPQ.h"
using namespace std;

/*@ <answer>



 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Dron { int a, b; };

bool resuelveCaso() {
	int N, A, B;
	cin >> N >> A >> B;

	if (!cin || N <= 0)
		return false;

	int priority = 0;
	//priority_queue<int> colaA;
	IndexPQ<int, int, std::greater<int>> colaA;
	for (int i = 0; i < A; i++)
	{
		cin >> priority;
		//colaA.push(priority);
		colaA.push(i, priority);
	}

	//priority_queue<int> colaB;
	IndexPQ<int, int, std::greater<int>> colaB;
	for (int i = 0; i < B; i++)
	{
		cin >> priority;
		//colaB.push(priority);
		colaB.push(i, priority);
	}

	vector<int> horasTotales;
	while (!colaB.empty() && !colaA.empty())
	{
		int horas = 0;
		int i = 0;

		vector<IndexPQ<int, int, std::greater<int>>::Par> restosA;
		vector<IndexPQ<int, int, std::greater<int>>::Par> restosB;

		while (i < N && !colaB.empty() && !colaA.empty())
		{
			IndexPQ<int, int, std::greater<int>>::Par a = colaA.top(); colaA.pop();
			IndexPQ<int, int, std::greater<int>>::Par b = colaB.top(); colaB.pop();

			int vuelo = min(a.prioridad, b.prioridad);
			horas += vuelo;

			if (a.prioridad > b.prioridad)
				restosA.push_back({ a.elem, a.prioridad - b.prioridad });
			if (b.prioridad > a.prioridad)
				restosB.push_back({ b.elem, b.prioridad - a.prioridad });
			i++;
		}

		for (auto pila : restosA)
			colaA.push(pila.elem, pila.prioridad);
		for (auto pila : restosB)
			colaB.push(pila.elem, pila.prioridad);

		horasTotales.push_back(horas);
	}

	for (int tiempo : horasTotales)
		cout << tiempo << " ";

	cout << "\n";
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