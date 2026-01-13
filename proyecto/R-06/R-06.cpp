
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"
#include "IndexPQ.h"
#include "Grafo.h"
#include "DigrafoValorado.h"


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class MaximaCompConexa {
public:
	MaximaCompConexa(Grafo const& g, vector<int> const& sobornos) : visit(g.V(), false), minim(0) {
		for (int v = 0; v < g.V(); ++v) {
			if (!visit[v]) { // se recorre una nueva componente conexa
				int minimoComponente = dfs(g, v, sobornos);
				minim += minimoComponente;
			}
		}
	}

	int minimo() const { return minim; }
private:
	vector<bool> visit; // visit[v] = se ha visitado el vértice v?
	int minim; 

	int dfs(Grafo const& g, int v, vector<int> const& sobornos) {
		visit[v] = true;
		int _maxAct = sobornos[v];
		for (int w : g.ady(v)) {
			if (!visit[w])
				_maxAct = min(_maxAct, dfs(g, w, sobornos));
		}
		return _maxAct;
	}
};

bool resuelveCaso() {
	int N, M;
	cin >> N >> M;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<int> sobornos(N);
	for (int i = 0; i < N; ++i)
		cin >> sobornos[i];

	Grafo g(N);
	while (M--)
	{
		int v, w;
		cin >> v >> w;
		--v; --w;
		g.ponArista(v, w);
	}

	MaximaCompConexa m(g, sobornos);
	cout << m.minimo() << '\n';

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
