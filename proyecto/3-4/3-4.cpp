
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
	IndexPQ<int, int> colaA;
	for (int i = 0; i < A; i++)
	{
		cin >> priority;
		//colaA.push(priority);
		colaA.push(i, priority);
	}

	//priority_queue<int> colaB;
	IndexPQ<int, int> colaB;
	for (int i = 0; i < B; i++)
	{
		cin >> priority;
		//colaB.push(priority);
		colaB.push(i, priority);
	}

	vector<int> horasTotales;
	while (!colaB.empty() && !colaA.empty())
	{
		IndexPQ<int,int>::Par a = colaA.top();
		IndexPQ<int,int>::Par b = colaB.top();

		int horas = 0;

		if (a.prioridad > b.prioridad)
		{
			int bateria = a.prioridad - b.prioridad;
			horas += b.prioridad;
			colaA.update(a.elem, bateria);
			colaB.pop();
		}
		else if (b.prioridad > a.prioridad)
		{
			int bateria = b.prioridad - a.prioridad;
			horas += a.prioridad;
			colaB.update(b.elem, bateria);
		} 
		else
		{
			horas = a.prioridad;
			colaA.pop();
			colaB.pop();
		}

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