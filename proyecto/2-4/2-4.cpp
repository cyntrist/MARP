
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

struct Pacientes
{
	int gravedad; 
	string nombre;		
};

bool operator<(Pacientes const& a, Pacientes const& b)
{
	return b.gravedad < a.gravedad
		|| (a.gravedad == b.gravedad && b.nombre < a.nombre);
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N = -1;
	cin >> N;

	if (N == 0)
		return false;

	priority_queue<Pacientes> triaje;
	for (int i = 0; i < N; i++)
	{
		char E;
		cin >> E;
		if (E == 'I') // ingreso
 		{
			string nombre;
			long gravedad;
			cin >> nombre >> gravedad;
			triaje.push({gravedad, nombre});
		}
		else if (E == 'A')
		{
			if (!triaje.empty())
			{
				cout << triaje.top().nombre << '\n';
				triaje.pop();
				
			}
		}
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
