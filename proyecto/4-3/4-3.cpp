/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Grafo.h"

using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class MaximaCompConexa
{
public:
	MaximaCompConexa(const Grafo& g) : maxim(0), visit(g.V(), false)
	{
		for (int v = 0; v < g.V(); ++v)
		{
			if (!visit[v])
			{
				int tam = dfs(g, v);
				maxim = max(maxim, tam);
			}
		}
	}

	int maximo() const
	{
		return maxim;
	}

private:
	int maxim;
	vector<bool> visit;

	int dfs(const Grafo& g, int v)
	{
		visit[v] = true;
		int tam = 1;
		for (int w : g.ady(v))
		{
			if (!visit[w])
				tam += dfs(g, w);
		}
		return tam;
	}
};

void resuelveCaso()
{
	int N, M;
	cin >> N >> M;

	Grafo g(N);

	while (M--)
	{
		int v, w;
		cin >> v >> w;
		g.ponArista(v - 1, w - 1);
	}

	MaximaCompConexa mcc(g);
	cout << mcc.maximo() << '\n';
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main()
{
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	if (!in.is_open())
		std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio y parar antes de salir
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif

	return 0;
}
