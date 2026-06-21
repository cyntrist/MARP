
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Matriz.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool dia_bueno(std::vector<int> const& frutas, int i, int j)
{
	return frutas[i] != 0 && frutas[i] == frutas[j];
}

int veces_descendente(std::vector<int> const& frutas, int i, int j, Matriz<int>& veces) {
	if (i >= veces.numfils() || j >= veces.numcols() || i < 0 || j < 0) return 0;

	int& res = veces[i][j];
	if (res == -1) {
		if (i > j) res = 0; // si el trozo es inverso
		else if (i == j) res = 0; // si el trozo es de tamaño 1
		else
		{
			int o1 = veces_descendente(frutas, i + 2, j, veces) + dia_bueno(frutas, i, i + 1);
			int o2 = veces_descendente(frutas, i + 1, j - 1, veces) + dia_bueno(frutas, i, j);
			int o3 = veces_descendente(frutas, i, j - 2, veces) + dia_bueno(frutas, j - 1, j);

			res = std::max(o1, std::max(o2, o3));
		}
	}
	return res;
}

int veces_ascendente(std::vector<int> const& frutas, int I, int J)
{
	Matriz<int> veces(I + 1, J + 1, 0);
	for (int i = 0; i <= I; ++i)
	{
		for (int j = 0; j <= J; ++j)
		{
			
		}
	}
	return veces[I][J];
}

bool resuelveCaso() {
	int N = 0;
	std::cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<int> frutas(N);
	for (auto& n : frutas)
		std::cin >> n;

	Matriz veces(N, N, -1);
	cout << veces_descendente(frutas, 0, N - 1, veces) << '\n'; 
	//cout << veces_ascendente(frutas, 0, N - 1) << '\n';

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
