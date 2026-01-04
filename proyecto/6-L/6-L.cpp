
/*@ <authors>
 *
 * Cynthia Tristán Álvarez
 * MARP62
 *
 *@ </authors> */

#include <deque>
#include <iostream>
#include <fstream>
#include <queue>
#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"
using namespace std;

/*@ <answer>

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

template <typename Valor>
class ARM_Kruskal {
public:
	ARM_Kruskal(GrafoValorado<Valor> const& g) : _coste(0), _ctos(g.V())
	{
		PriorityQueue<Arista<Valor>> pq(g.aristas());

		while (!pq.empty())
		{
			Arista<Valor> a = pq.top(); pq.pop();
			int v = a.uno(), w = a.otro(v);
			if (!_ctos.unidos(v, w))
			{
				_ctos.unir(v, w);
				_ARM.push_back(a);
				_coste += a.valor();
				if (_ARM.size() == g.V() - 1) break;
			}
		}
	}

	Valor coste() const { return _coste;  }
	int num_cmptes() const { return _ctos.num_cjtos(); }
private:
	vector<Arista<Valor>> _ARM;
	Valor _coste;
	ConjuntosDisjuntos _ctos;
};


bool resuelveCaso()
{
	int N, M, A;
	cin >> N >> M >> A;
	if (!cin)
	return false;

	int X, Y, C;
	GrafoValorado<int> g(N);

	for (int i = 0; i < M; i++) 
	{
		cin >> X >> Y >> C;
		if (C < A) 
			g.ponArista(Arista <int>(X - 1, Y - 1, C));
	}

	ARM_Kruskal<int> k(g);
	int coste = A * k.num_cmptes() + k.coste();
	cout << coste << " " << k.num_cmptes() << '\n';

	return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos.txt");
	if (!in.is_open())
		cout << "Error: no se ha podido abrir el archivo de entrada." << endl;
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	cout << "Pulsa Intro para salir..." << flush;
	cin.get();
#endif
	return 0;
}
