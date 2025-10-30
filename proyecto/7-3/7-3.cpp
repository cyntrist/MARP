
/*@ <authors>
 *
 * Cynthia Tristán Álvarez
 * MARP62
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
using namespace std;

/*@ <answer>

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

class CaminosMin
{
public:
    CaminosMin(DigrafoValorado<int> const& g, int orig) :
        origen(orig), dist(g.V(), INF), ulti(g.V()), pq(g.V()), caminos(g.V(), 0) {
        dist[origen] = 0;
        caminos[origen] = 1;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    int64_t calculaNCaminos(DigrafoValorado<int> const& g, int v) {
        if (!hayCamino(v)) return 0;

        if (caminos[v] == 0) {
            int64_t min = distancia(v);
            for (auto a : g.ady(v)) {
                int w = a.hasta();
                if (dist[w] + a.valor() <= min) {
                    caminos[v] += calculaNCaminos(g, w);
                }
            }
        }
        return caminos[v];
    }

    bool hayCamino(int v) const { return dist[v] != INF; }
    int64_t distancia(int v) const { return dist[v]; }
    int64_t nCaminos(int v) const { return caminos[v]; }

private:
    const int INF = 1000000000;
    int origen;
    std::vector<int64_t> dist;
    std::vector<int64_t> caminos; //Caminos minimos a cada indice
    std::vector<AristaDirigida<int>> ulti;
    IndexPQ<int64_t> pq;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
};


bool resuelveCaso()
{
    int N, M, A;
    cin >> N >> M >> A;
    if (!cin)
        return false;

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
