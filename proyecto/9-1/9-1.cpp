
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

struct Edificio
{
	int izq, der;
};

bool operator<(Edificio const& a, Edificio const& b)
{
	return a.der > b.der;
}

using Edificios = priority_queue<Edificio>;
int pasadizos(Edificios edificios)
{
	if (edificios.empty()) return 0;
	int ultimo = -1;
	int pasadizos = 0;
	while (!edificios.empty())
	{
		auto este = edificios.top(); edificios.pop();
		if (ultimo < este.izq)
		{
			ultimo = este.der - 1;
			++pasadizos;
		}
	}
	return pasadizos;
}

bool resuelveCaso() {
	int N;
	cin >> N;

	if (N == 0)  // fin de la entrada
		return false;

	//vector<Edificio> edificios;
	Edificios edificios;
	for (int i = 0; i < N; i++)
	{
		int ini, fin;
		cin >> ini >> fin;
		//edificios.push_back({ ini, fin });
		edificios.push({ ini,fin });
	}

	cout << pasadizos(edificios) << '\n';

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
