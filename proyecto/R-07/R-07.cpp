
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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


// m[i][j] = número de combinaciones para llegar a la casilla i, j desde la casilla 1, 1
int combinaciones(const Matriz<int>& M)
{
	const int F = M.numfils(), C = M.numcols();
	Matriz m(F + 1, C + 1, 0);

	m[1][1] = 1;

	for (int i = 0; i <= F; ++i)
	{
		for (int j = 0; j <= C; ++j)
		{
			int formas = m[i][j];

			if (formas > 0) // si se puede llegar siquiera a esta casilla
			{
				int valor = M[i - 1][j - 1];
				
				if (i + valor <= F) // para no salirse
					m[i + valor][j] += formas;
				if (j + valor <= C)
					m[i][j + valor] += formas;
			}
		}
	}

	return m[F][C];
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int n = 0, m = 0;
	std::cin >> n >> m;

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	Matriz<int> M(n, m);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			std::cin >> M[i][j];

	// escribir la solución
	std::cout << combinaciones(M) << '\n';

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
	//std::cout << "Pulsa Intro para salir..." << std::flush;
	//std::cin.get();
#endif
	return 0;
}
