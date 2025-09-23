
/*@ <authors>
 *
 * Cynthia Tristán Álvarez
 * MARP62
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
//#include <limits>
#include <algorithm> 
#include <cstdlib>   
#include "bintree.h"

using namespace std;

/*@ <answer>

Mi solución consiste en usar recursión binaria simultáneamente mirando
tanto si es ABB como AVL comprobando las dos condiciones para ello
de abajo hacia arriba:

ABB: max⁡(izq) < valor del nodo < min⁡(der)
AVL: |altura(izq) − altura(der)| <= 1

Coste temporal: O(n) siendo n el número de elementos del árbol ya que acaba
pasando una y solo una vez por cada uno de los nodos.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


/// ABB: max⁡(izq) < valor del nodo < min⁡(der)
// Este método lo he hecho para practicar inicialmente pero no forma parte de la solución
/// https://www.geeksforgeeks.org/dsa/a-program-to-check-if-a-binary-tree-is-bst-or-not/
//template <typename T>
//bool esABB(const BinTree<T>& tree, const T& min, const T& max) {
//	// casos base
//	if (tree.empty()) return true; // el arbol vacío es AAB
//
//	// todos los valores de la izq tienen que ser menores que la raíz
//	// y todos los valores de la der tienen que ser mayores que la raíz
//	// si esto no se cumple no es ABB
//	if (tree.root() < min || tree.root() > max) return false; 
//
//	return esABB(tree.left(), min, tree.root()) && 
//		   esABB(tree.right(), tree.root(), max);
//}

/// AVL: |altura(izq) − altura(der)| <= 1
// objetivo, determinar primero si es un ABB y luego un AVL
// https://www.geeksforgeeks.org/dsa/how-to-determine-if-a-binary-tree-is-balanced/
template <typename T>
int esAVL(const BinTree<T>& tree, T& minV, T& maxV) 
{
	// caso base
	if (tree.empty()) 
		return 0;

	// creamos maximos minimos laterales y altura
	T elem = tree.root(),
	  minL, maxL,
	  minR, maxR;
	// inicializamos rango para evitar tener que pasarlo,
	minV = elem;
	maxV = elem;
	int lHeight = 0, rHeight = 0;

	// alturas si existen de izq y der
	// actualizar referencias a valores minmax
	if (!tree.left().empty())
	{
		lHeight = esAVL(tree.left(), minL, maxL);
		if (maxL >= elem) return -1; // comprobación de ABB
		minV = minL;
	}
	if (!tree.right().empty())
	{
		rHeight = esAVL(tree.right(), minR, maxR);
		if (minR <= elem) return -1; // comprobación de ABB
		maxV = maxR;
	}

	// si alguno no esta balanceado de por si o si justo este nodo lo está,
	// porque la diferencia de alturas entre izq y der es mayor que uno,
	// el árbol entero está desbalanceado
	if (lHeight == -1 || rHeight == -1 || abs(lHeight - rHeight) > 1)
		return -1;

	// devolvemos su altura contando el nodo raíz
	// importante para que justo lo que acabamos de comprobar tenga sentido
	return max(lHeight, rHeight) + 1;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	char modo;
	cin >> modo;

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	if (tolower(modo) == 'n') 
	{
		//cout << "enteros" << endl;
		BinTree<int> tree = read_tree<int>(cin);
		//int minV = std::numeric_limits<int>::lowest(),
		//	maxV = std::numeric_limits<int>::max();
		//cout << (esABB(tree, min, max) ? "SI\n" : "NO\n");

		int minV, maxV;
		const int h = esAVL(tree, minV, maxV);
		cout << (h != -1 ? "SI\n" : "NO\n");
	}
	else 
	{
		//std::cout << "palabras" << endl;
		BinTree<string> tree = read_tree<string>(cin);
		//string minV = std::numeric_limits<string>::lowest(),
		//	   maxV = std::numeric_limits<string>::max();

		string minV, maxV;
		const int h = esAVL(tree, minV, maxV);
		cout << (h != -1 ? "SI\n" : "NO\n");
	}

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("input.txt");
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
