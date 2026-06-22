/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
 #include <algorithm>

using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase
#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int p(char c) //posicion
{
	switch (c)
	{
	case 'A': return 0;
	case 'C': return 1;
	case 'G': return 2;
	case 'T': return 3;
	default: return 4;
	}
}

// https://en.wikipedia.org/wiki/Needleman%E2%80%93Wunsch_algorithm
// https://www.geeksforgeeks.org/dsa/sequence-alignment-problem/
int needleman_wunsch(const Matriz<int>& S, const string& primero, const string& segundo)
{
	int N = primero.length(), M = segundo.length();
	Matriz<int> m(N + 1, M + 1, -1);
	m[0][0] = 0;

	for (int i = 1; i <= N; ++i)
		m[i][0] = m[i - 1][0] + S[p(primero[i - 1])][p('-')];

	for (int j = 1; j <= M; ++j)
		m[0][j] = m[0][j - 1] + S[p('-')][p(segundo[j - 1])];

	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= M; ++j)
		{
			int arriba = m[i - 1][j] + S[p(primero[i - 1])][p('-')];
			int pareja = m[i - 1][j - 1] + S[p(primero[i - 1])][p(segundo[j - 1])];
			int izquierda = m[i][j - 1] + S[p('-')][p(segundo[j - 1])];

			m[i][j] = std::max({ 
				arriba,
				pareja,
				izquierda
			});
		}
	}

	return m[N][M];
}

void resuelveCaso() {
	Matriz<int> S(5, 5);

	// 𝐴𝐶𝐺𝑇− * 𝐴𝐶𝐺𝑇−
	for (const auto i : {0, 1, 2, 3, 4})
		for (const auto j : { 0, 1, 2, 3, 4 })
			cin >> S[i][j];
	
	int N = 0;
	cin >> N;

	for (int i = 0; i < N; ++i)
	{
		string primero, segundo;
		cin >> primero >> segundo;

		cout << needleman_wunsch(S, primero, segundo) << '\n';
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
