
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

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

struct Bateria
{
	int id;
	int capacidad;
	int fin;
};

bool operator>(const Bateria& a, const Bateria& b)
{
	if (a.fin == b.fin) return a.id > b.id;
	return a.fin > b.fin;
}

bool resuelveCaso() {
	int B = 0;
	std::cin >> B;

	if (!std::cin)  // fin de la entrada
		return false;

	std::vector<int> duraciones(B);
	for (auto& d : duraciones)
		std::cin >> d;

	int R = 0;
	std::cin >> R;

	std::vector<int> repuestos(R);
	for (auto& r : repuestos)
		std::cin >> r;

	int Z = 0, T = 0;
	std::cin >> Z >> T;

	priority_queue<Bateria, vector<Bateria>, greater<Bateria>> pq;
	for (int i = 0; i < B; ++i)
		pq.emplace(i + 1, duraciones[i], duraciones[i]);
	int repuesto = 0;

	while (!pq.empty() && pq.top().fin <= T)
	{
		auto pila = pq.top(); pq.pop();
		pila.capacidad -= Z;

		if (pila.capacidad > 0)
		{ // recarga instantanea
			pila.fin = pila.fin + pila.capacidad;
			pq.push(pila);
		}
		else
		{ // reemplazo
			if (repuesto < R)
				pq.emplace(B + repuesto + 1, repuestos[repuesto], repuestos[repuesto] + pila.fin);
			repuesto++;
		}
	}

	int finales = pq.size();

	if (finales > 0)
	{
		if (finales >= B) cout << "CORRECTO\n";
		else cout << "FALLO EN EL SISTEMA\n";

		while (!pq.empty())
		{
			std::cout << pq.top().id << ' ' << pq.top().fin << '\n';
			pq.pop();
		}
	}
	else cout << "ABANDONEN INMEDIATAMENTE LA BASE\n";

	
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
