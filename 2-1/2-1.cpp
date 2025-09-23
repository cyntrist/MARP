
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

using llong = long long;
using uint = unsigned int;

llong resuelve(priority_queue<llong, vector<llong>, greater<llong>>& cola)
{
	if (cola.empty() || cola.size() == 1)
		return 0;

	llong res;
	res = 0;

	while (cola.size() >= 2)
	{
		llong a = cola.top(); cola.pop();
		llong b = cola.top(); cola.pop();
		llong suma = a + b;
		res += suma;

		cola.push(suma); // !!!!!!!!!
	}

	//if (cola.size() == 1)
	//	res += cola.top(); cola.pop();

	return res;
}

// https://learn.microsoft.com/en-us/cpp/cpp/data-type-ranges?view=msvc-170
bool resuelveCaso() {
	// leer los datos de la entrada
	uint N;
	cin >> N;

	if (N == 0)
		return false;

	priority_queue<llong, vector<llong>, greater<llong>> cola; // queremos una cola por mínimos para sumar los menores seguidos (top y pop)
	for (uint i = 0; i < N; i++)
	{
		llong n;
		cin >> n;
		cola.push(n); 
	}

	cout << resuelve(cola) << '\n';
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
