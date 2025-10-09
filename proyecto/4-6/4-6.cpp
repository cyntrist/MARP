
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

#include "Grafo.h"
using namespace std;

/*@ <answer>



 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class ComponentesConexas
{
public:
	ComponentesConexas(Grafo const& G) : visit(G.V(), false), componente(G.V())
	{
		for (auto v = 0; v < G.V(); ++v) // O(V + A)	
		{
			if (!visit[v]) // se recorre una nueva componente conexa
			{
				int tam = dfs(G, v); 
				tam_comp.push_back(tam);
			}
		}
	}

	int tam_comp_v(int v) // tamaño de la componente a la que pertenece v
	{
		return tam_comp[componente[v]];
	}

private:
	vector<bool> visit;
	vector<int> componente; // nº de componente al que pertenece v
	vector<int> tam_comp; // tamaño de la componente conexa nº i

	// recorrido en profundidad de la componente de v
	int dfs(Grafo const& G, int v)
	{
		visit[v] = true;
		componente[v] = tam_comp.size();
		int tam = 1;
		for (int w : G.ady(v))
		{
			if (!visit[w])
			{
				tam += dfs(G, w);
			}
		}
		return tam;
	}
};

bool resuelveCaso() {
	int N, M;
	cin >> N >> M;
	if (!cin)
		return false;

	Grafo G(N);
	for (int i = 0; i < M; ++i)
	{
		int T;
		cin >> T;
		if (T > 0)
		{
			int uno;
			cin >> uno;
			int otro;
			for (int j = 1; j < T; ++j)
			{
				cin >> otro;
				G.ponArista(uno - 1, otro - 1);
				uno = otro;
			}
		}
	}

	ComponentesConexas CC(G); // O (N + sum(T_i))
	cout << CC.tam_comp_v(0);
	for (int i = 1; i < N; ++i)
	{
		cout << ' ' <<	CC.tam_comp_v(i);
	}
	cout << '\n';

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