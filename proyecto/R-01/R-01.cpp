
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <deque>
#include <iostream>
#include <fstream>
#include <limits>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"
#include "IndexPQ.h"

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

template <typename Valor>
class Dijkstra {
public:
	Dijkstra(GrafoValorado<Valor> const& g, int orig) : origen(orig),
		_max(g.V(), INF), ulti(g.V()), pq(g.V()) {
		_max[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a, v);
		}
	}
	bool hayCamino(int v) const { return _max[v] != INF; }
	Valor maximo(int v) const { return _max[v]; }
private:
	const Valor INF = std::numeric_limits<Valor>::max();
	int origen;
	std::vector<Valor> _max;
	std::vector<Arista<Valor>> ulti;
	IndexPQ<Valor> pq;

	void relajar(Arista<Valor> a, int v) {
		int w = a.otro(v);
		Valor nuevo = max(_max[v], a.valor());
		if (nuevo < _max[w]) {
			_max[w] = nuevo;
			pq.update(w, _max[w]);
		}
	}
};



template <typename Valor>
class ARM_Kruskal {
	ConjuntosDisjuntos cjtos;
	Valor _maximo;
public:
	Valor maximo() const { return _maximo;  }
	bool unidos(int v, int w) const { return cjtos.unidos(v, w); }
	ARM_Kruskal(GrafoValorado<Valor> const& g, int P, int T) : cjtos(g.V()), _maximo(0) {
		if (P == T) return; 
		PriorityQueue<Arista<Valor>> pq(g.aristas());
		while (!pq.empty()) {
			auto a = pq.top(); pq.pop();
			int v = a.uno(), w = a.otro(v);
			if (!cjtos.unidos(v, w)) {
				cjtos.unir(v, w);
				if (cjtos.unidos(P, T))
				{
					_maximo = a.valor(); // por definicion de kruskal voraz, si es la primera en unirles es la de mayor valor posible
					break;
				}
			}
		}
	}
};

bool resuelveCaso() {
	int N, M;
	cin >> N >> M;

	if (!std::cin)  // fin de la entrada
		return false;

	GrafoValorado<int> g(N);
	while (M--)
	{
		int v, w, p;
		cin >> v >> w >> p;
		--v; --w;
		g.ponArista({v, w, p});
	}

	int P, T;
	cin >> P >> T;
	--P; --T;


	ARM_Kruskal k(g, P, T);
	if (k.unidos(P, T))
	{
		cout << k.maximo() << '\n';
	}
	else
	{
		cout << "IMPOSIBLE\n";
	}
	//Dijkstra d(g, P);
	//if (d.hayCamino(T))
	//{
	//	cout << d.maximo(T) << '\n';
	//}
	//else
	//{
	//	cout << "IMPOSIBLE\n";
	//}
	//cout << "---\n";

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
