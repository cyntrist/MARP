
/*@ <authors>
 *
 * Cynthia Tristán Álvarez
 * MARP62
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

/*@ <answer>



 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Comic {
	int id; // identificador
	int pos; // posición en su pila
};

bool operator>(Comic const& a, Comic const& b) {
	return b.pos > a.pos ||
		(a.pos == b.pos && b.id > a.id);
};

int resuelve(priority_queue<Comic, vector<Comic>, greater<Comic>> comics)
{
	return -1;
}

bool resuelveCaso() {
	// leer los datos de la entrada

	if (!std::cin)  // fin de la entrada
		return false;

	int N = -1;
	cin >> N;

	if (N == 0)
		return false;

	priority_queue<Comic, vector<Comic>, greater<Comic>> comics;
	for (int i = 0; i < N; i++) // por cada pila
	{
		int K = 0;
		cin >> K;
		for (int j = 0; j < K; j++)
		{
			int id;
			cin >> id;
			comics.push({id, K - j});
		}
	}

	cout << resuelve(comics) << endl;

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
