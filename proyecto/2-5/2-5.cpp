
/*@ <authors>
 *
 * Cynthia Tristán Álvarez
 * MARP62
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;

/*@ <answer>



 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Comic {
	int id; // identificador
	int pila; // numero de su pila
};

bool operator>(const Comic& a, const Comic& b) {

	return a.id > b.id;
}

bool resuelveCaso() {

	int N;
	cin >> N;

	if (!std::cin)  
		return false;

	vector<stack<Comic>> pilas;
	priority_queue<Comic, vector<Comic>, greater<Comic>> disponibles;
	int minimo = -1;

	for (int i = 0; i < N; i++) {
		int K;
		cin >> K;

		stack<Comic> pila;
		for (int j = 0; j < K; j++) {
			int num;
			cin >> num;
			if (num < minimo || minimo == -1)
				minimo = num;
			pila.push({ num, i });
		}
		pilas.push_back(pila);
	}

	for (auto& pila : pilas)
	{
		disponibles.push(pila.top());
		pila.pop();

	}

	int puesto = 1;
	Comic mejor = disponibles.top();
	while (mejor.id != minimo) 
	{
		auto& pila = pilas[mejor.pila];
		disponibles.pop(); // vendido!
		if (!pila.empty()) 
		{	
			disponibles.push(pila.top());
			pila.pop();
		}
		mejor = disponibles.top();
		puesto++;
	}

	cout << puesto << '\n';

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