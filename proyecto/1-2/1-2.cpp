
/*@ <authors>
 *
 * Cynthia Tristán Álvarez
 * MARP62
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "TreeSet_AVL.h"
using namespace std;

/*@ <answer>

el método k_esimo implementa una búsqueda binaria en el árbol en función de k.
la verdadera dificultad del ejercicio está en implementar tam_i y buscar dónde
exacto se gestiona el aumento y decremento de tam_i al insertar y rotar

los métodos nuevos están en las líneas 255 y 339 de TreeSet_AVL.h!!!

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// clase al estilo eda para implementar una función pública con la que considerar
// y llamar a la protegida
// la he abandonado porque da errores de compilación en el juez
//template <class T>
//class set_plus : public Set<T>
//{
//public:
//	T const* k_esimo(int k) const
//	{
//		if (k > this->size() || k <= 0)
//			return nullptr;
//		return &this->kesimo(this->raiz, k);
//	}
//};

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;

	if (N == 0)
		return false;

	//set_plus<int> set; // creacion de los arboles
	Set<int> set; // creacion de los arboles
	for (int i = 0; i < N; i++)
	{
		int n;
		cin >> n;
		set.insert(n);
	}

	int M; // consultas de los kesimos
	cin >> M;
	for (int i = 0; i < M; i++)
	{
		int m;
		cin >> m;
		const int* sol = set.k_esimo(m);
		if (sol == nullptr)
			cout << "??" << endl;
		else
			cout << *sol << endl;
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
