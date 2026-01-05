
/*@ <authors>
 *
 * Cynthia Tristán Álvarez
 * MARP62
 *
 *@ </authors> */

#include <deque>
#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <limits>
using namespace std;

/*@ <answer>

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

template <typename Valor>
class N_Dikjstras
{
public:
    N_Dikjstras(DigrafoValorado<Valor> const& g, int o) 
	    : dist(g.V(), INF), ulti(g.V()), origen(o), pq(g.V()), n_caminos(g.V(), 0)
    {
        dist[origen] = 0;
        pq.push(origen, 0);
        n_caminos[origen] = 1;
        while (!pq.empty())
        {
            int v = pq.top().elem; pq.pop();
	        for (auto a : g.ady(v))
	            relajar(a);
        }
    }

    Valor distancia(int v) const { return dist[v];  }
    bool hayCamino(int v) const { return dist[v] != INF;  }
    int cuantosCaminos(int v) const { return n_caminos[v]; }
    deque<AristaDirigida<Valor>> camino(int v)
    {
        deque<AristaDirigida<Valor>> camino;
        AristaDirigida<Valor> a;
        for (a = ulti[v]; a.desde() != origen ; a = ulti[a.desde()])
            camino.push_front(a);
        camino.push_front(a);
        return camino;
    }
private:
    const Valor INF = numeric_limits<Valor>::max();
    vector<int> dist;
    vector<AristaDirigida<Valor>> ulti;
    int origen;
    IndexPQ<Valor> pq;

    vector<int> n_caminos; // n caminos minimos por nodo desde origen

    void relajar(AristaDirigida<Valor> a)
    {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor())
        {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
            n_caminos[w] = n_caminos[v];
        }
        else if (dist[w] == dist[v] + a.valor()) 
        {
            n_caminos[w] += n_caminos[v];
        }
    }
};


bool resuelveCaso()
{
    int N, C;
    cin >> N >> C;
    if (!cin)
        return false;

    DigrafoValorado<int> g(N);
    while (C--)
    {
        int v, w, p;
        cin >> v >> w >> p;
        --v; --w;
        g.ponArista({ v, w, p });
        g.ponArista({ w, v, p });
    }

    N_Dikjstras<int> d(g, 0);
    cout << d.cuantosCaminos(N - 1) << '\n';
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
