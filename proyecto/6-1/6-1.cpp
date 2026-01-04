/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "ConjuntosDisjuntos.h"

using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

using Mapa = vector<string>;

class Manchas
{
public:
	Manchas(Mapa const& M) 
	: F(M.size()), 
	  C(M[0].size()), 
	  manchas(F * C),
	  maxim(0)
	{
		for (int i = 0; i < F; ++i)
		{
			for (int j = 0; j < C; ++j)
				if (M[i][j] == '#')
					insertar(M, i, j);
		}
	}

	int maximo() const { return maxim; }
	void insertar(Mapa const& m, int i, int j)
	{
		int v = id(i, j);
		maxim = max(1, maxim);

		for (auto d : dirs)
		{
			int ni = i + d.first, nj = j + d.second;
			if (correcta(ni, nj) && m[ni][nj] == '#')
			{
				int w = id(ni, nj);
				manchas.unir(v, w);
				maxim = max(maxim, manchas.cardinal(v));
			}
		}
	}
private:
	int F, C;
	ConjuntosDisjuntos manchas;
	int maxim;

	bool correcta(int i, int j) const
	{
		return 0 <= i && i < F && 0 <= j && j < C;
	}

	const vector<pair<int, int>> dirs = {
		{1,0}, {0, 1}, {-1, 0}, {0, -1},
		{-1, -1}, {-1, 1}, {1, -1}, {1, 1}
	};

	int id(int f, int c) const { return f * C + c; }
};

bool resuelveCaso()
{
	int F, C;
	cin >> F >> C;

	if (!cin || F == 0 || C == 0)
		return false;

	Mapa m(F);

	for (string& linea : m)
		cin >> linea;

	Manchas man(m);
	cout << man.maximo() << ' ';

	int E;
	cin >> E;

	while (E--)
	{
		int f, c;
		cin >> f >> c;
		m[f - 1][c - 1] = '#';
		man.insertar(m, f - 1, c - 1);
		cout << man.maximo() << ' ';
	}
	cout << '\n';
	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

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