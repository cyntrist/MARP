
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

struct Pais
{
	int puntos;
	string nombre;
};

bool operator<(Pais const& a, Pais const& b)
{
	return b.puntos < a.puntos || (b.puntos == a.puntos && b.nombre > a.nombre);
}

bool resuelveCaso() {
	int N;
	cin >> N;

	if (!cin)  
		return false;

	IndexPQ<string, Pais> cola;
	for (int i = 0; i < N; i++)
	{
		string evento;
		cin >> evento;
		if (evento == "?")
		{
			if (!cola.empty())
				cout << cola.top().elem << " " << cola.top().prioridad.puntos << endl;
		}
		else
		{
			int puntos;
			cin >> puntos;
			try
			{
				puntos += cola.priority(evento).puntos;
			}
			catch (...)
			{
				// si no existe lo añadira normal a continuacion no hace falta gestion de error
			}
			cola.update(evento, {puntos, evento});
		}
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