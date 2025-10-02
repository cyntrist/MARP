
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

bool resuelveCaso() {
	int N; 
	long numero;
	cin >> numero >> N;

	if (numero == 0 || N == 0)  
		return false;

	priority_queue<long, vector<long>, less<long>> izq;
	priority_queue<long, vector<long>, greater<long>> der;

	der.push(numero);
	for (int i = 0; i < N; i++)
	{
		cin >> numero;
		if (numero < der.top())
			izq.push(numero);
		else
			der.push(numero);

		if (izq.size() > der.size())
		{
			der.push(izq.top()); izq.pop();
		}
		else if (der.size() > izq.size() + 1)
		{
			izq.push(der.top()); der.pop();
		}

		cin >> numero;
		if (numero < der.top())
			izq.push(numero);
		else
			der.push(numero);

		if (izq.size() > der.size())
		{
			der.push(izq.top()); izq.pop();
		}
		else if (der.size() > izq.size() + 1)
		{
			izq.push(der.top()); der.pop();
		}


		cout << der.top() << " ";
	}
	cout << endl;
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