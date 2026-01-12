
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
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

struct Tesoro { int profundidad, valor; };

double mochila_rec(vector<Tesoro> const& obj, int i, int j,
	Matriz<double>& mochila) {
	if (mochila[i][j] != -1) // subproblema ya resuelto
		return mochila[i][j];
	if (i == 0 || j == 0) mochila[i][j] = 0;
	else if (obj[i - 1].profundidad * 3 > j)
		mochila[i][j] = mochila_rec(obj, i - 1, j, mochila);
	else
		mochila[i][j] = max(mochila_rec(obj, i - 1, j, mochila),
			mochila_rec(obj, i - 1, j - obj[i - 1].profundidad * 3, mochila)
			+ obj[i - 1].valor);
	return mochila[i][j];
}

double mochila(vector<Tesoro> const& tesoros, int M, vector<Tesoro>& sol) {
	int n = tesoros.size();
	Matriz<double> mochila(n + 1, M + 1, -1);
	double valor = mochila_rec(tesoros, n, M, mochila);
	// cálculo de los objetos
	int i = n, j = M;
	sol = vector<Tesoro>();
	while (i > 0 && j > 0) {
		if (mochila[i][j] != mochila[i - 1][j]) {
			sol.push_back(tesoros[i - 1]);
			j = j - tesoros[i - 1].profundidad * 3;
		}
		--i;
	}

	return valor;
}

bool resuelveCaso() {
	int P, N;
	cin >> P >> N;
	if (!std::cin)  // fin de la entrada
		return false;

	vector<Tesoro> tesoros(N);
	for (int i = 0; i < N; ++i)
	{
		int profundidad, valor;
		cin >> profundidad >> valor;
		tesoros[i] = { profundidad, valor };
	}

	vector<Tesoro> solucion;
	cout << mochila(tesoros, P, solucion) << '\n';

	cout << solucion.size() << '\n';
	for (auto r : solucion)
		cout << r.profundidad << " " << r.valor << '\n';
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
