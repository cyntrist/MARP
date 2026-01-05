
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

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

size_t parches(vector<int> const& agujeros, int longitud)
{
	if (agujeros.empty()) return 0;
	size_t i = 0;
	size_t parches = 1;
	int ini_pos = agujeros[0];
	while (i < agujeros.size())
	{
		if (agujeros[i] > ini_pos + longitud)
		{
			ini_pos = agujeros[i];
			++parches;
		}
		++i;
	}
	return parches;
}

bool resuelveCaso() {
	int N, L;
	cin >> N >> L;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<int> agujeros(N);
	int i = 0;
	while (i < N)
	{
		cin >> agujeros[i];
		++i;
	}

	cout << parches(agujeros, L) << '\n';

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
