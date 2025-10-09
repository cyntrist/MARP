
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

class CaminosDFS
{
protected:
	vector<bool> visit; // visit[v] = ¿hay camino de s a v?
	vector<int> ant; // ant[v] = último vértice antes de llegar a v
	vector<int> dist; 
	int s; // vertice origen

	void dfs(Grafo const& g)
	{
		queue<int> q;
        dist[s] = 0;
		visit[s] = true;
        q.push(s);
        while (!q.empty()) 
		{
            const int v = q.front(); q.pop();
            for (int w : g.ady(v)) 
			{
                if (!visit[w]) {
                    ant[w] = v;
                    dist[w] = dist[v] + 1;
                    visit[w] = true;
                    q.push(w);
                }
            }
        }
	}

public:
	CaminosDFS(Grafo const& g, int s) : visit(g.V(), false), ant(g.V()), s(s),
	dist(g.V(), g.V())
	{
        dfs(g);
	}

	/// Caminos
	// ¿hay camino del origen a v?
	bool hayCamino(int v) const
	{
		return visit[v];
	}

	using Camino = deque<int>; // para representar caminos
	// devuelve un camino desde el origen a v (debe existir)
	Camino camino(int v) const
	{
		if (!hayCamino(v))
			throw domain_error("No existe camino.");

		Camino cam;
		// recuperamos el camino retrocediendo
		for (int x = v; x != s; x = ant[x])
			cam.push_front(x);
		cam.push_front(s);
		return cam;
	}

	/// Problema
	int distancia(int v) const
	{
        return dist[v];
    }
};

bool resuelveCaso() {
	int N, C, A, L, T; 
	cin >> N >> C >> A >> L >> T;
    int minCoste = C;

	if (!cin)
		return false;

	Grafo g(N);
	while (C--)
	{
		int v, w;
		cin >> v >> w;
		g.ponArista(v - 1, w - 1);
	}

	const CaminosDFS a(g, A - 1);
    const CaminosDFS l(g, L - 1);
    const CaminosDFS t(g, T - 1);

    for (int i = 0; i < g.V(); i++) 
	{
        if (a.hayCamino(i) && l.hayCamino(i) && t.hayCamino(i)) 
        	minCoste = min(minCoste, a.distancia(i) + l.distancia(i) + t.distancia(i));
    }
	cout << minCoste << endl;

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