
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
#include "ConjuntosDisjuntos.h"
using namespace std;

/*@ <answer>

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

template <typename Valor>
class ARMKruskal {
    vector<bool> visit;
    int comp;
    Valor coste;
    vector<Arista<Valor>> arm;

    void dfs(GrafoValorado<int> const& g, int v, int umbral)
	{
        visit[v] = true;
        for (auto a : g.ady(v)) 
        {
            if (a.valor() < umbral) 
            {
                int w = a.otro(v);
                if (!visit[w])
                    dfs(g, w, umbral);
            }
        }
    }
public:
    Valor costeARM() const { return coste; }
    vector<Arista<Valor>> const& ARM() const { return arm; }
    int compo() const { return comp; }

    ARMKruskal(GrafoValorado<Valor> const& g, int A)
	: visit(g.V(), false), comp(0), coste(0)
	{

    }

    int componentes(GrafoValorado<Valor> const& g, int A) {
        int i = 0, c = 0;

        while (i < g.V()) 
        {
            if (!visit[i]) 
            {
                dfs(g, i, A);
                c++;
            }
            i++;
        }
        
        return c;
    }
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

  ARMKruskal<int> k(g, A);
  int coste = A * k.compo() + k.costeARM();
  cout << coste << " " << k.compo() << '\n';
  
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
