
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
using Efectivos = priority_queue<int, vector<int>, greater<>>;
size_t victorias(Efectivos enemigos, Efectivos aliados)
{
	if (enemigos.empty() || aliados.empty()) return 0;
	size_t victorias = 0;
	while (!enemigos.empty() && !aliados.empty())
	{
		if (aliados.top() >= enemigos.top())
		{
			enemigos.pop();
			aliados.pop();
			++victorias;
		}
		else
		{
			aliados.pop();
		}
	}
	return victorias;
}

bool resuelveCaso() {
	int N;
	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	//vector<int> enemigos(N);
	//vector<int> defensas(N);
	Efectivos enemigos;
	Efectivos aliados;
	int i = 0;
	while (i < N)
	{
		//cin >> enemigos[i];
		int e; cin >> e;
		enemigos.push(e);
		++i;
	}
	i = 0;
	while (i < N)
	{
		//cin >> defensas[i];
		int d; cin >> d;
		aliados.push(d);
		++i;
	}

	cout << victorias(enemigos, aliados) << '\n';

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
