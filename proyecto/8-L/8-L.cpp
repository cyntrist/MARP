
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


//vector<int> salas(vector<Conferencia> const& conferencias)
//{
//	if (conferencias.empty()) return {};
//	if (conferencias.size() == 1) return { 1 };
//
//	int i = 0;
//	auto conf = conferencias[i];
//	int ultimo = conf.fin;
//	vector<int> salas;
//	while (i < conferencias.size() && conferencias[i].inicio < ultimo)
//	{
//		salas.push_back(i);
//		ultimo = conferencias[i].fin;
//		i++;
//	}
//	return salas;
//}

//vector<int> salas(vector<Conferencia> const& conferencias) // XDDDDDDDDDDDDDDDDDDDDDDDDD N^2
//{
//	if (conferencias.empty()) return {};
//	vector<int> s_c(conferencias.size(), -1); // la conferencia i se da en la sala k
//	vector<int> s_f(0); // fin[i] = k -> la sala i acaba a la hora k
//
//	for (auto const& c : conferencias)
//	{
//		int i = 0;
//		while (i < s_f.size())
//		{
//			if (s_f[i] <= c.inicio)
//			{
//				s_c[c.id] = i;
//				s_f[i] = c.fin;
//				i = s_f.size() + 1;
//			}
//			++i;
//		}
//		if (i == s_f.size())
//		{
//			s_f.push_back(c.fin);
//			s_c[c.id] = s_f.size() - 1;
//		}
//	}
//
//	return s_c;
//}

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
				pq.push({conf.fin, sala.id});
			}
			else
			{ // nueva sala
				++_h;
				_asignadas[conf.id] = _h;
				pq.push({conf.fin, _h});
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
	cout << s.h() << '\n';
	for (auto const& r : s.salas())
		cout << r << ' ';
	cout << '\n';
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
