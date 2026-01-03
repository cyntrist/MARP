
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
#include "Digrafo.h"

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

//class OrdenTopologico
//{
//public:
//	// g es DAG
//	OrdenTopologico(Digrafo const& g) : visit(g.V(), false)
//	{
//		for (int v = 0; v < g.V(); ++v)
//		{
//			if (!visit[v])
//				dfs(g, v);
//		}
//	}
//
//	deque<int> const& orden()
//	{
//		return _orden;
//	}
//
//private:
//	vector<bool> visit;
//	deque<int> _orden;
//
//	void dfs(Digrafo const& g, int v)
//	{
//		visit[v] = true;
//		for (auto w : g.ady(v))
//		{
//			if (!visit[w])
//				dfs(g, w);
//		}
//		_orden.push_front(v);
//	}
//};
//
//using Camino = deque<int>; // para representar caminos
//class CicloDirigido
//{
//public:
//	CicloDirigido(Digrafo const& g) : visit(g.V(), false), apilado(g.V(), false),
//		ant(g.V()), hayciclo(false)
//	{
//		for (int v = 0; v < g.V(); ++v)
//		{
//			if (!visit[v])
//				dfs(g, v);
//		}
//	}
//
//	bool hayCiclo() const { return hayciclo; }
//
//	Camino const& ciclo() { return _ciclo; }
//
//private:
//	vector<bool> visit;
//	vector<bool> apilado;
//	vector<int> ant;
//	Camino _ciclo;
//	bool hayciclo;
//
//	void dfs(Digrafo const& g, int v)
//	{
//		apilado[v] = true;
//		visit[v] = true;
//		for (auto w : g.ady(v))
//		{
//			if (hayciclo) return;
//			if (!visit[w])
//			{
//				ant[w] = v;
//				dfs(g, w);
//			}
//			else if (apilado[w])
//			{
//				hayciclo = true;
//				for (int x = v; x != w; x = ant[x])
//				{
//					_ciclo.push_front(x);
//				}
//				_ciclo.push_front(w);
//				_ciclo.push_front(v);
//			}
//		}
//		apilado[v] = false;
//	}
//};

class Necronomicon
{
public:
	Necronomicon(Digrafo const& g) 
	: visit(g.V(), false),
	  apilado(g.V(), false),
	  _ciclico(false), _acaba(false)
	{
		dfs(g, 0);
	}
	bool acaba() const { return _acaba;  }
	bool ciclico() const { return _ciclico; }

private:
	vector<bool> visit;
	vector<bool> apilado;
	bool _ciclico;
	bool _acaba;

	void dfs(Digrafo const& g, int v)
	{
		visit[v] = true;
		apilado[v] = true;
		if (v == g.V() - 1)
			_acaba = true;
		for (int w : g.ady(v))
		{
			if (!visit[w]) dfs(g, w);
			else if (apilado[w]) _ciclico = true;
		}
		apilado[v] = false;
	}
};

bool resuelveCaso() {
	int n_instrucciones;
	cin >> n_instrucciones;

	if (!std::cin)  // fin de la entrada
		return false;

	Digrafo g(n_instrucciones + 1);
	int i = 0;
	while (n_instrucciones--)
	{
		char instruccion;
		cin >> instruccion;
		
		if (instruccion == 'A')
		{
			g.ponArista(i, i + 1);
		}
		else if (instruccion == 'J')
		{
			int salto;
			cin >> salto;
			g.ponArista(i, salto);
		}
		else if (instruccion == 'C')
		{
			int salto;
			cin >> salto;
			g.ponArista(i, i + 1);
			g.ponArista(i, salto);
		}
		i++;
	}

	Necronomicon n(g);

	if (!n.ciclico() && n.acaba())
		cout << "SIEMPRE\n";
	else if (n.ciclico() && n.acaba())
		cout << "A VECES\n";
	else if (n.ciclico() && !n.acaba())
		cout << "NUNCA\n";
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


