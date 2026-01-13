
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <deque>
#include <iostream>
#include <fstream>
#include "Grafo.h"

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

class Bipartito {
private:
	vector<bool> visit; // visit[v] = ¿hay camino de s a v?
	vector<int> ant; // ant[v] = último vértice antes de llegar a v

	vector<bool> equipos;
	bool _bipartito;
	void dfs(Grafo const& G, int v) {
		visit[v] = true;
		for (int w : G.ady(v)) {
			if (!_bipartito) return;

			if (!visit[w]) {
				ant[w] = v;
				equipos[w] = !equipos[v];
				dfs(G, w);
			}
			else if (equipos[w] == equipos[v])
			{
				_bipartito = false; return;
			}
		}
	}
public:
	Bipartito(Grafo const& g) : visit(g.V(), false), _bipartito(true),
		ant(g.V()), equipos(g.V(), false) {
		for (int v = 0; v < g.V(); ++v)
		{
			if (!visit[v])
			{
				dfs(g, v);
				if (!_bipartito) break;
			}
		}
	}
	bool es() const { return _bipartito; }
};

bool resuelveCaso() {
	int N, M;
	cin >> N >> M;

	if (!std::cin)  // fin de la entrada
		return false;
	Grafo g(N);
	while (M--)
	{
		int v, w;
		cin >> v >> w;
		--v; --w;
		g.ponArista(v, w);
	}

	Bipartito b(g);
	cout << (b.es() ? "SI" : "NO") << '\n'; 

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
