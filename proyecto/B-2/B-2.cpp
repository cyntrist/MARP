
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
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

// DESCENDENTE
int min_ins_desc_rec(string& s, int l, int h, Matriz<int>& memo) 
{

	// Base case
	if (l >= h) return 0;

	// If value is memoized 
	if (memo[l][h] != -1) return memo[l][h];

	// if first and last char are same 
	// then no need to insert element
	if (s[l] == s[h]) {
		return memo[l][h] = min_ins_desc_rec(s, l + 1, h - 1, memo);
	}

	// Insert at begining or insert at end
	return memo[l][h] = min(min_ins_desc_rec(s, l + 1, h, memo),
		min_ins_desc_rec(s, l, h - 1, memo)) + 1;
}

int min_ins_desc(string& s) 
{
	int n = s.length();
	Matriz<int> memo(n, n, -1);

	return min_ins_desc_rec(s, 0, n - 1, memo);
}

// ASCENDENTE
int min_ins_asc(string& s, Matriz<int>& dp)
{
	int n = s.size();

	// dp[i][j] will store the minimum number of insertions needed
	// to convert str[i..j] into a palindrome

	// len is the length of the substring
	for (int len = 2; len <= n; len++) {
		for (int l = 0; l <= n - len; l++) {

			// ending index of the current substring
			int h = l + len - 1;

			// If the characters at both ends are 
			// equal, no new insertions needed
			if (s[l] == s[h]) {
				dp[l][h] = dp[l + 1][h - 1];
			}
			else {

				// Insert at the beginning or at the end
				dp[l][h] = min(dp[l + 1][h], dp[l][h - 1]) + 1;
			}
		}
	}

	// The result is in dp[0][n-1] which 
	// represents the entire string
	return dp[0][n - 1];
}

string reconstruir_palindromo(string const& s, Matriz<int> const& dp)
{
	int l = 0, h = s.size() - 1;
	string left = "", right = "";

	while (l <= h) {
		if (l == h) {
			left += s[l];   // carácter central
			break;
		}

		if (s[l] == s[h]) {
			left += s[l];
			right = s[h] + right;
			l++;
			h--;
		}
		else if (dp[l + 1][h] <= dp[l][h - 1]) {
			// insertamos s[l] al final
			left += s[l];
			right = s[l] + right;
			l++;
		}
		else {
			// insertamos s[h] al principio
			left += s[h];
			right = s[h] + right;
			h--;
		}
	}

	return left + right;
}

// OPTIMIZADA ASCENDENTE
int min_ins_asc_opt(string& s) {
	int n = s.size();
	vector<int> dp(n, 0);

	// Iterate over each character from right to left
	for (int l = n - 2; l >= 0; l--) {

		// This represents dp[l+1][h-1] from the previous row
		int prev = 0;
		for (int h = l + 1; h < n; h++) {

			// Save current dp[h] before overwriting
			int temp = dp[h];

			if (s[l] == s[h]) {

				// No new insertion needed if characters match
				dp[h] = prev;
			}
			else {

				// Take min of two cases + 1
				dp[h] = min(dp[h], dp[h - 1]) + 1;
			}

			// Update prev for the next column
			prev = temp;
		}
	}

	return dp[n - 1];
}


bool resuelveCaso() {
	string entrada;
	cin >> entrada;
	if (!std::cin)  // fin de la entrada
		return false;

	int n = entrada.size();
	Matriz<int> m(n, n, 0);
	cout << min_ins_asc(entrada, m) << " " << reconstruir_palindromo(entrada, m) << '\n';

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
