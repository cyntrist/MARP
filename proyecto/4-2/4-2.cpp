
/*@ <authors>
 *
 * Cynthia Tristán Álvarez
 * MARP62
 *
 *@ </authors> */

#include <deque>
#include <iostream>
#include <fstream>
#include "Grafo.h"
using namespace std;

/*@ <answer>



 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

// ESTO CAYÓ EN UN EXAMEN!!!!!!!!!!!!!!!!!!
class Bipartito
{
protected:
	vector<bool> visit; // visit[v] = ¿hay camino de s a v?
	int s; // vertice origen

	// bipartito
	bool bipartito = true;
	vector<bool> color;

	void dfs(Grafo const& g, int v)
	{
		visit[v] = true;
		for (int w : g.ady(v))
		{
			if (!bipartito) return;

			if (!visit[w]) // si no se ha visitado el nodo
			{
				color[w] = !color[v];
				dfs(g, w); // adyacentes del nuevo nodo
			}
			else if (color[w] == color[v])
			{
				bipartito = false;
			}
		}
	}

public:
	Bipartito(Grafo const& g, int s) : visit(g.V(), false), s(s), color(g.V())
	{
		for (int v = 0; v < g.V() && bipartito; ++v)
		{
			if (!visit[v])
			{
				color[v] = false;
				dfs(g,v);
			}
		}

	}

	// ¿hay camino del origen a v?
	bool hayCamino(int v) const
	{
		return visit[v];
	}

	// arboles libres
	bool esBipartito() const { return bipartito; }
};

bool resuelveCaso() {
	int V, A;
	cin >> V >> A;

	if (!cin)
		return false;

	Grafo g(V);
	while (A--)
	{
		int v, w;
		cin >> v >> w;
		g.ponArista(v, w);
	}

	Bipartito a(g, 0);
	cout << (a.esBipartito() ? "SI" : "NO") << '\n';

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