
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
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

vector<int> minimo(vector<int> const& sectores, int P)
{
	int N = sectores.size();
	Matriz<int> dardos(N + 1,P + 1, 1e6);
	dardos[0][0] = 0;
	for (int i = 1; i <= N; ++i)
	{
		dardos[i][0] = 0;
		for (int j = 1; j <= P; ++j)
		{
			if (sectores[i - 1] > j)
			{
				dardos[i][j] = dardos[i - 1][j];
			}
			else
				dardos[i][j] = std::min(
					dardos[i - 1][j],
					dardos[i][j - sectores[i - 1]] + 1
				);
		}
	}

	vector<int> sol;
	if (dardos[N][P] != 1e6)
	{
		int i = N, j = P;
		while (j > 0 && i > 0)
		{ 
			// caso 1: se ha usado el sector i
			// condiciones: que la puntuación del sector i no se pase de la cantidad restante j y el valor de la casilla coincida con la suma (eso es que se cogió en su momento)
			if (sectores[i - 1] <= j && dardos[i][j] == dardos[i][j - sectores[i - 1]] + 1)
			{
				sol.push_back(sectores[i - 1]);
				j -= sectores[i - 1];
			}
			else // caso dos: no se uso el sector i, no cumple alguna de las condiciones del caso anterior
			{
				--i;
			}
		}
	}
	return sol;
}

vector<int> minimo_optimizado(vector<int> const& sectores, int P)
{
	int N = sectores.size();
	vector<int> dardos(P + 1, 1e6);
	dardos[0] = 0;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = sectores[i - 1]; j <= P; ++j)
		{
			dardos[j] = std::min(
				dardos[j - sectores[i - 1]] + 1,
				dardos[j]
			);
		}
	}

	vector<int> sol;
	if (dardos[P] != 1e6)
	{
		int i = N, j = P;
		while (j > 0 && i > 0)
		{
			if (sectores[i - 1] <= j && dardos[j] == dardos[j - sectores[i - 1]] + 1)
			{
				sol.push_back(sectores[i - 1]);
				j -= sectores[i - 1];
			}
			else --i;
		}
	}
	return sol;
}

bool resuelveCaso() {
	int P, N;
	cin >> P >> N;
	if (!std::cin)  // fin de la entrada
		return false;

	vector<int> sectores(N);
	for (int i = 0; i < N; ++i)
	{
		int sector;
		cin >> sector;
		sectores[i] = sector;
	}

	vector<int> resultado = minimo_optimizado(sectores, P);
	if (resultado.empty())
	{
		cout << "Imposible";
	}
	else
	{
		cout << resultado.size() << ": ";
		for (auto r : resultado)
			cout << r << " ";
	}
	cout << '\n';

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
