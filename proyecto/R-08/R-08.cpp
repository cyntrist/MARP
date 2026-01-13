
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
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

struct Conferencia
{
	int ini, fin, id;

	bool operator<(const Conferencia& otro) const {
		return ini < otro.ini;
	}
};

struct Sala
{
	int fin, id;

	bool operator<(const Sala& otro) const {
		return fin > otro.fin;
	}
};

class Solucion
{
public:
	Solucion(vector<Conferencia> const& conferencias) : _asignadas(conferencias.size(), -1)
	{
		priority_queue<Sala> pq;
		for (auto const& conf : conferencias)
		{
			if (!pq.empty() && pq.top().fin <= conf.ini)
			{ // reusar sala
				auto sala = pq.top(); pq.pop();
				_asignadas[conf.id] = sala.id;
				pq.push({ conf.fin, sala.id });
			}
			else
			{ // nueva sala
				++_h;
				_asignadas[conf.id] = _h;
				pq.push({ conf.fin, _h });
			}
		}

	}

	int h() const { return _h; }
	vector<int> salas() const { return _asignadas; }
private:
	int _h = 0;
	vector<int> _asignadas;
};

bool resuelveCaso() {
	int N;
	cin >> N;

	if (N == 0)  // fin de la entrada
		return false;

	vector<Conferencia> c;
	for (int i = 0; i < N; i++)
	{
		int ini, fin;
		cin >> ini >> fin;
		c.push_back({ ini, fin, i });
	}
	sort(c.begin(), c.end(), [](Conferencia const& a, Conferencia const& b)
		{
			return a.ini < b.ini;
		});

	Solucion s(c);
	cout << s.h() - 1 << '\n';
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
