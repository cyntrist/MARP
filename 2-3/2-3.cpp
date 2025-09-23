
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

struct Caja
{
	int ocupada; 
	int id;		 

};

bool operator<(Caja const& a, Caja const& b)
{
	return b.ocupada < a.ocupada || (a.ocupada == b.ocupada && b.id < a.id);
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, C, tiempo;
	cin >> N >> C;

	if (N == 0)
		return false;

	priority_queue<Caja> cajas;
	for (int i = 1; i <= N; i++)
	{
		cajas.push({0, i});
	}

	for (int i = 0; i < C; i++)
	{
		cin >> tiempo;
		auto caja = cajas.top(); cajas.pop();
		caja.ocupada += tiempo;
		cajas.push(caja);
	}

	cout << cajas.top().id << '\n';

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
