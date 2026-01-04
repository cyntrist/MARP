
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <deque>
#include <iostream>
#include <fstream>
#include "GrafoValorado.h"

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

class Trayecto
{
public:
	Trayecto(GrafoValorado<int> const& g, int origen, int destino, int umbral) : visit(g.V(), false),
		apilado(g.V(), false),
		_posible(false),
		_ciclico(false)
	{
		dfs(g, origen, destino, umbral);
	}

	bool ciclico() const { return _ciclico; }
	bool posible() const { return _posible;  }

private:
	vector<bool> visit;
	vector<bool> apilado;
	bool _ciclico;
	bool _posible;

	void dfs(GrafoValorado<int> const& g, int v, int destino, int umbral)
	{
		visit[v] = true;
		apilado[v] = true;
		if (v == destino)
			_posible = true;
		else
		{
			for (Arista<int> a : g.ady(v))
			{
				if (a.valor() < umbral) 
					continue;

				int w = a.otro(v);
				if (!visit[w]) 
					dfs(g, w, destino, umbral);
				else if (apilado[w]) 
					_ciclico = true;
			}
		}
		apilado[v] = false;
	}
};

bool resuelveCaso() {
	int V, E;
	cin >> V >> E;

	if (!std::cin)  // fin de la entrada
		return false;

	GrafoValorado<int> grafo(V);
	int u, v, valor;
	for (int i = 0; i < E; ++i)
	{
		cin >> u >> v >> valor;
		grafo.ponArista({ u - 1,v - 1, valor });
	}

	int T;
	cin >> T;

	while (T--)
	{
		int O, D, U;
		cin >> O >> D >> U;
		Trayecto t(grafo, O - 1, D - 1, U);
		cout << (t.posible() ? "SI" : "NO") << '\n';
	}

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
