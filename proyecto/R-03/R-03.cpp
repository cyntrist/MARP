
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

struct Chorizo
{
	int gramos_disponibles;
	int gramos_necesarios;
	int masa_necesaria;
	int valor;
	int bollos_posibles;
};

// i = tipo de chorizo
// j = gramos de masa disponibles
// m[i][j] = maximo beneficio reportable usando los primeros i tipos de chorizos con j gramos de masa

// coste temporal: N* masa * k
// coste espacial: N * masa
int bollos_rec(vector<Chorizo> const& obj, int i, int j,
	Matriz<int>& mochila) {
	if (mochila[i][j] != -1) // subproblema ya resuelto
		return mochila[i][j];
	if (i == 0 || j == 0) mochila[i][j] = 0;
	else
	{
		Chorizo chorizo = obj[i - 1];
		int k_max = std::min(chorizo.bollos_posibles, j / chorizo.masa_necesaria); // maximo numero de bollos realmente posibles 

		int mejor = 0;
		for (int k = 0; k <= k_max; ++k)
		{
			int masa_usada = k * chorizo.masa_necesaria;
			int benef_act = k * chorizo.valor;

			mejor = std::max(mejor, bollos_rec(obj, i - 1, j - masa_usada, mochila) + benef_act);
		}
		mochila[i][j] = mejor;
	}
	return mochila[i][j];
}

int bollos(vector<Chorizo> const& objetos, int M) {
	int n = objetos.size();
	Matriz<int> mochila(n + 1, M + 1, -1);
	return bollos_rec(objetos, n, M, mochila);
}

// i = tipo de chorizo
// j = gramos de masa disponibles
// m[i][j] = maximo beneficio reportable usando los primeros i tipos de chorizos con j gramos de masa

// coste temporal: N * masa * k
// coste espacial: N * masa
int bollos_asc(vector<Chorizo> const& obj, int N, int masa)
{
	Matriz m(N + 1, masa + 1, 0);

	for (int i = 1; i <= N; ++i)
	{
		Chorizo c = obj[i - 1];

		for (int j = 0; j <= masa; ++j)
		{
			m[i][j] = m[i - 1][j];

			int k_max = std::min(c.bollos_posibles, j / c.masa_necesaria);

			for (int k = 0; k <= k_max; ++k)
			{
				int masa_usada = k * c.masa_necesaria;

				if (masa_usada <= j)
				{
					m[i][j] = std::max(m[i][j], m[i - 1][j - masa_usada] + k * c.valor);
				}

			}
		}
	}

	return m[N][masa];
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N = 0, masa = 0;
	std::cin >> N >> masa;

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	std::vector<Chorizo> chorizos(N);
	for (auto& c : chorizos)
	{
		std::cin >> c.gramos_disponibles >> c.gramos_necesarios >> c.masa_necesaria >> c.valor;
		c.bollos_posibles = c.gramos_disponibles / c.gramos_necesarios;
	}

	// escribir la solución
	std::cout << bollos_asc(chorizos, N, masa) << '\n';

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
