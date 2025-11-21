/*@ <authors>
 *
 * MARP86 Alberto Verdejo
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

/*@ <answer>
 
 Solución por programación dinámica basada en la siguiente recurrencia
 (llamo "monedas" tanto a las monedas como a los billetes y las considero
 numeradas de 1 a N):
 
 mon(i, j) = mínimo nº de monedas necesario para pagar j de forma exacta
 cuando podemos usar las monedas de la 1 a la i
 
 Es decir, es la misma función del problema del cambio visto en clase pero
 donde ahora no tenemos tipos de monedas (con cantidad ilimitada), sino
 monedas unitarias.
 
 Los casos básicos son:
 mon(i, 0) = 0  // no se usan monedas
 mon(0, j) = INF si j > 0 // no hay solución, no se puede pagar j
 
 En los casos recursivos distinguimos según la moneda i se pueda utilizar
 o no, y en el caso de que sí probamos las dos opciones, usarla o no
 usarla (en ambos casos la llamada recursiva se hace con i-1 porque cada
 moneda se puede utilizar como mucho una vez):
 
 mon(i, j) = mon(i-1, j) si M[i] > j
 mon(i, j) = min(mon(i-1, j), // no utilizamos la moneda i
 mon(i-1, j - M[i]) + 1) // utilizamos la moneda i
 
 Para averiguar lo que se pide en el enunciado, cuál es la cantidad mínima
 que podemos pagar mayor o igual al precio P, haríamos llamadas iniciales
 mon(N, P), mon(N, P+1), ..., hasta que una devuelva un valor distinto de INF.
 Sabemos que eso va a ocurrir porque el enunciado nos dice que la suma de
 todas las monedas, S, sí permite pagar P. Si mon(N, Q) = K es la primera
 llamada con K ≠ INF, entonces la solución pedida es Q K.
 
 En cuanto a la implementación, en principio necesitaríamos una matriz con
 N+1 filas y S+1 columnas, que podría rellenarse de arriba abajo y dentro
 de cada fila de izquierda a derecha (o al revés). Pero como para rellenar
 la fila i solamente hacen falta valores de la fila i-1 en posiciones que no
 están a la derecha, podemos utilizar solamente un vector que se actualiza
 cada vez de derecha a izquierda.
 
 Una vez hemos hecho todas las actualizaciones, buscamos en el vector
 desde la posición P hasta la posición S cuál es la primera posición que
 contiene un valor distinto de INF.
 
 El coste es O(N * S) en tiempo, porque rellenamos una matriz de tamaño
 (N+1)*(S+1) y calcular el valor de cada posición requiere un tiempo constante
 y O(S) en espacio adicional porque de la matriz solamente almacenamos una fila.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

const int INF = 1000000000;

bool resuelve() {
  int P, N;
  cin >> P >> N;
  
  if (!cin)
    return false;
  
  vector<int> moneda(N);
  int S = 0;
  for (int i = 0; i < N; ++i) {
    cin >> moneda[i];
    S += moneda[i];
  }
  
  vector<int> mon(S + 1, INF);
  mon[0] = 0;
  
  for (int i = 0; i < N; ++i) {
    for (int j = S; j >= moneda[i]; --j) {
      mon[j] = min(mon[j], mon[j - moneda[i]] + 1);
    }
  }
  
  // buscar la mínima cantidad ≥ P que pueda pagarse
  for (int monto = P; monto <= S; ++monto) {
    if (mon[monto] != INF) {
      cout << monto << " " << mon[monto] << "\n";
      break;
    }
  }
  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  ifstream in("casos.txt");
  if (!in.is_open())
    cout << "Error: no se ha podido abrir el archivo de entrada." << endl;
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
