
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
using namespace std;

/*@ <answer>

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

template <typename Valor>
using Camino = deque<Valor>; // para representar caminos
template <typename Valor>
class Dijkstra
{
public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
        dist(g.V(), INF), ulti(g.V()), pq(g.V())
    {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty())
        {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    bool hayCamino(int v) const { return dist[v] != INF; }

    Valor distancia(int v) const { return dist[v]; }
    Camino<Valor> camino(int v) const
	{
        Camino<Valor> cam;
        // recuperamos el camino retrocediendo
        AristaDirigida<Valor> a;
        for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
            cam.push_front(a);
        cam.push_front(a);
        return cam;
    }

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    vector<Valor> dist;
    vector<AristaDirigida<Valor>> ulti;
    IndexPQ<int, Valor> pq;
    void relajar(AristaDirigida<Valor> a)
	{
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) 
        {
            dist[w] = dist[v] + a.valor(); ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
};

bool resuelveCaso()
{
    int N, C;
    cin >> N >> C;
    if (!cin)
        return false;

    DigrafoValorado<int> dg(N);
    for (int i = 0; i < C; i++)
    {
        int v, w, d;
        cin >> v >> w >> d;
        dg.ponArista(AristaDirigida<int>(v - 1, w - 1, d));
    }

    int P;
    cin >> P;

    for (int i = 0; i < P; i++)
    {
        int v, w;
        cin >> v >> w;
    }

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
