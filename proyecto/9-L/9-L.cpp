
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <deque>
#include <iostream>
#include <fstream>
#include <limits>

#include "IndexPQ.h"
#include "DigrafoValorado.h"

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
class Dijkstra
{
public:
	Dijkstra(DigrafoValorado<Valor> const& g, int o) : dist(g.V(), INF), ulti(g.V()), pq(g.V())
	, origen(o)
	{
		dist[origen] = 0;
		pq.push(origen, dist[origen]);
		while (!pq.empty())
		{
			auto v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	Valor distancia(int v) const { return dist[v]; }
	deque<AristaDirigida<Valor>> camino(int v)
	{
		deque<AristaDirigida<Valor>> camino;
		AristaDirigida<Valor> a;
		for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
			camino.push_front(a);
		camino.push_front(a);
		return camino;
	}
private:
	vector<Valor> dist;
	vector<AristaDirigida<Valor>> ulti;
	IndexPQ<Valor> pq;

	int origen;
	const int INF = numeric_limits<Valor>::max();

	void relajar(AristaDirigida<Valor> a)
	{
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor())
		{
			dist[w] = dist[v] + a.valor();
			ulti[w] = a;
			pq.update(w, dist[w]);
		}
	}
};

bool resuelveCaso() {
	int N, M;
	cin >> N >> M;

	if (!std::cin)  // fin de la entrada
		return false;

	DigrafoValorado<int> g(N);
	while (M--)
	{
		int v, w, p;
		cin >> v >> w >> p;
		--v; --w;
		g.ponArista({v, w, p});
		g.ponArista({w, v, p});
	}

	Dijkstra dN(g, 0);
	Dijkstra dS(g, N - 1);

	vector<int> deltas(N);
	int coste = 0;
	for (int i = 1; i < N - 1; ++i)
	{
		cout << dN.distancia(i);
		int dif = dN.distancia(i) - dS.distancia(i);
		if (dif < 0)
		{
			coste += dS.distancia(i);
		}
		else
		{
			coste += dN.distancia(i);
		}
		//deltas.push_back();
	}

	cout << coste << '\n';

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
