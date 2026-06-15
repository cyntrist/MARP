
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <deque>
#include <iostream>
#include <fstream>
using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

using Camino = deque<int>; // para representar caminos
class Recuerdos {
	std::vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
	std::vector<int> ant; // ant[v] = vértice anterior en el camino a v
	std::vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
	bool hayciclo;
	std::deque<int> _orden; // ordenación topológica
public:
	Recuerdos(Digrafo const& g) : visit(g.V(), false), ant(g.V()),
		apilado(g.V(), false), hayciclo(false) {
		for (int v = 0; v < g.V(); ++v)
			if (!visit[v])
				dfs(g, v);
	}
	bool hayCiclo() const { return hayciclo; }
	void dfs(Digrafo const& g, int v) {
		apilado[v] = true;
		visit[v] = true;
		for (int w : g.ady(v)) {
			if (hayciclo) // si hemos encontrado un ciclo terminamos
				return;
			if (!visit[w]) { // encontrado un nuevo vértice, seguimos
				ant[w] = v; dfs(g, w);
			}
			else if (apilado[w]) { // hemos detectado un ciclo
				hayciclo = true;
			}
		}
		_orden.push_front(v);
		apilado[v] = false;
	}
	// devuelve la ordenación topológica
	Camino const& orden() const {
		return _orden;
	}
};


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int N = 0, M = 0;

	std::cin >> N >> M; 

	if (!cin)
		return false;
	if (N == 0 && M == 0)
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	Digrafo dg(N);
	while (M--)
	{
		int A = 0, B = 0;
		std::cin >> A >> B;
		dg.ponArista(A - 1, B - 1);
	}

	Recuerdos solucion(dg);

	// viable?
	bool valido = !solucion.hayCiclo();

	// escribir la solución
	if (valido)
	{
		std::cout << "SI ";
		Camino camino = solucion.orden();

		for (auto c : camino)
		{
			std::cout << c + 1 << " ";
		}
		std::cout << '\n';
	}
	else
	{
		std::cout << "NO\n";
	}

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
