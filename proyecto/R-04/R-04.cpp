/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "ConjuntosDisjuntos.h"  // propios o los de las estructuras de datos de clase
#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

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
class ARM_Kruskal {
private:
	Valor _maximo;
	ConjuntosDisjuntos cjtos;
public:
	Valor maximo() const { return _maximo; }
	bool conexo() const { return cjtos.num_cjtos() == 1; }
	ARM_Kruskal(GrafoValorado<Valor> const& g) : _maximo(0), cjtos(g.V()) {
		PriorityQueue<Arista<Valor>> pq(g.aristas());
		while (!pq.empty()) {
			auto a = pq.top(); pq.pop();
			int v = a.uno(), w = a.otro(v);
			if (!cjtos.unidos(v, w)) {
				cjtos.unir(v, w);
				_maximo = max(_maximo, a.valor());
			}
		}
	}
};

void resuelveCaso() {
	int N, M;
	cin >> N >> M;

	GrafoValorado<int> g(N);
	while (M--)
	{
		int v, w, p;
		cin >> v >> w >> p;
		--v; --w;
		g.ponArista({ v, w, p });
	}

	ARM_Kruskal k(g);
	if (k.conexo())
	{
		cout << k.maximo() << '\n'; 
	}
	else
	{
		cout << "Imposible\n";
	}
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

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio y parar antes de salir
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif

	return 0;
}
