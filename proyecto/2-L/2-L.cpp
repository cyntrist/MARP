/*@ <authors>
 *
 * MARP62 Cynthia Tristán
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
//#include <algorithm>
//#include <limits>
#include <queue>
using namespace std;


/*@ <answer>
 
 La solución asume del enunciado un mínimo de 1 partitura por instrumento en la orquesta.

 Partiendo de esa base se forma una cola de prioridad sobre:
 la cantidad de músicos por instrumento partido de la cantidad de partituras con las que cuentan,
 que es recorrida en base a las partituras restantes en función de lo asumido anteriormente.

 A cada iteración se borra top() y se vuelve a insertar para tener en cuenta la nueva partitura.

 Una vez repartidas las partituras se accede a top()
 para ver el grupo con el mayor nº de musicos por partitura.
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

struct Instrumento
{
	long musicos; // cantidad de musicos con los que cuenta ese instrumento en la orquesta
	int id; // identificador único por instrumento
	int partituras = 1; // partituras que comparten entre ellos, minimo una por enunciado
};

//bool operator<(const Instrumento& a, const Instrumento& b)
//{
//	return b.musicos < a.musicos || (a.musicos == b.musicos && b.id < a.id);
//}

bool operator>(const Instrumento& a, const Instrumento& b)
{
	return b.musicos/b.partituras > a.musicos/a.partituras
		|| (a.musicos/a.partituras == b.musicos/b.partituras && b.id > a.id);
}


// O(n) siendo n la resta entre las partituras disponibles y el número de instrumentos
int resuelve(priority_queue<Instrumento, vector<Instrumento>, 
			greater<Instrumento>>& cola, int p)
{
	// reparto de partituras
	for (unsigned int i = 0; i < p - cola.size(); i++) // la resta debido a si toca más de una por instrumento si no es redundante
	{
		auto ins = cola.top(); cola.pop(); // se le da otra partitura a la más prioritaria
		ins.partituras++;
		cola.push(ins);
	}

	// contabilización de partituras
	auto ins = cola.top();
	int maxMus = ins.musicos/ins.partituras;
	//if (ins.musicos % ins.partituras < 1)
	//	maxMus++;

	//for (int i = 0; i < cola.size(); i++)
	//{
	//	auto ins = cola.top(); cola.pop();
	//	if (ins.musicos/ins.partituras > maxMus)
	//		maxMus = ins.musicos/ins.partituras;
	//}

	return maxMus;
}

bool resuelveCaso()
{
	// leemos la entrada
	int P, N; // p siempre será >= n
	cin >> P >> N;

	if (!cin)
		return false;

	// leer el resto del caso y resolverlo
	priority_queue<Instrumento, vector<Instrumento>, greater<Instrumento>> cola; // de máximos
	for (int i = 0; i < N; i++)
	{
		int m;
		cin >> m;
		cola.push({m, i});
	}

	cout << resuelve(cola, P) << endl;

	return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main()
{
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos.txt");
	if (!in.is_open())
		cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

	// Resolvemos
	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
#endif
	return 0;
}
