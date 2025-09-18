
/*@ <authors>
 *
 * Cynthia Tristán Álvarez
 * MARP62
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "TreeSet_AVL.h"
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

template <class T>
class set_plus : public Set<T>
{
public:
	T const& kesimo(int k) const 
	{
		return 1;
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;

	if (N == 0)
		return false;

	set_plus<int> set;
	for (int i = 0; i < N; i++)
	{
		int n;
		cin >> n;
		set.insert(n);
	}

	int M;
	cin >> M;
	for (int i = 0; i < M; i++)
	{
		int m;
		cin >> m;
		cout << set.kesimo(m) << endl;
	}

	cout << "---\n";
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
