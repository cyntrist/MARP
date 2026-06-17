
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

Lo que he hecho ha sido una combinación de búsqueda de órden topológico para encontrar un camino que respete las aristas del grafo y, añadiéndole el vector apilado, una detección de ciclos por si el grafo fuera de recuerdos incompatibles. 

El grafo viene dado de esta manera: los vértices son las ciudades del album de recuerdos (V) y las aristas son los recuerdos que los relacionan (A).

De esta manera tenemos:
	la deque _camino que se va actualizando tras cada iteración del DFS con los vértices en órden válido,
	el vector visit para poder llevar a cabo el DFS de manera eficiente,
	el vector apilado para detectar ciclos apilando vectores sobre él
	y un booleano hayCiclo para poder parar el DFS si lo encuentra además de servir como getter.
Coste: El coste de un DFS por definición es O(V + A), siendo V el número de vértices y A el de aristas de un grafo.

Nuestro DFS cuenta con accesos constantes a vector y push_front por lo que no empeora el coste. Se hace un DFS por cada vértice no visitado, por lo que el coste finalen tiempo en caso peor sigue siendo O(V + A), siendo V el número de vértices del grafo y el número de ciudades y A los recuerdos y las aristas del grafo	  

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
