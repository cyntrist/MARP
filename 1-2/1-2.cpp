
/*@ <authors>
 *
 * Cynthia Tristán Álvarez
 * MARP62
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
 //#include <limits>
#include <algorithm> 
#include <cstdlib>   
#include "bintree.h"
#include "TreeSet_AVL.h"

using namespace std;

/*@ <answer>



 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <class T>
class set_plus : public Set<T>
{
	using Nodo = typename Set<T>::Nodo;
public:
	T const& kesimo(int k) const 
	{
	
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	char modo;
	cin >> modo;

	if (!std::cin)  // fin de la entrada
		return false;


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
