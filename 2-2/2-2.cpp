
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

struct registro
{
	int momento; // cuando le toca
	int id;		 // id único
	int periodo; // tiempo entre consultas

};

bool operator<(registro const& a, registro const& b) 
{
	return b.momento < a.momento || (a.momento == b.momento && b.id < a.id);
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;

	if (N == 0)
		return false;

	priority_queue<registro> cola;
	for (int i = 0; i < N; i++)
	{
		int id, periodo;
		cin >> id >> periodo;
		cola.push({ periodo, id, periodo });
	}

	int envios;
	cin >> envios;

	while (envios--)
	{
		auto e = cola.top(); cola.pop();
		cout << e.id << '\n';
		e.momento += e.periodo;
		cola.push(e);
	}

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
