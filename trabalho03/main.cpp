#include <fstream>
using std::ifstream;
#include <iostream>
using std::cin;  using std::cout; using std::endl;
#include <map>
using std::map;
#include <string>
using std::string;
//#include "heap.hpp"
#include "huff.hpp"



/*

	A FAZER

	0) Estrutura da árvore de Huffman
	
	Vetor de HuffmanNodes. 

	Cada HuffMan nodes contém um código, o índice do filho esquerdo no vetor e o índice do filho
	direito. 

	Para ter acesso constante aos filhos, vamos manter um map<string codigo, int> 

	1) Implementar função construir_huffman(Heap), que implementa o algoritmo de Huffman
	e retorna a árvore de huffman

	1.5) Construir função construir_codificação(arvore_de_huffman), que atribui, para
	cada caractere, a codifição alcançada na árvore de huffman. 

	2) Implementar função que faz a compressão em si. 
	Essa função lerá o arquivo caractere a caractere, consultando a tabela de codificação para cada um. Cada caractere
	será substituído por sua codificação correspondente. 

	Como só podemos escrever um byte de cada vez, vamos alocar um buffer, que será descarregado no arquivo de saída toda vez
	que:
		a) o buffer estiver cheio; ou
		b) o buffer não estiver vazio e todos os caracteres já tiverem sido lidos. 

	Na realidade, o buffer nada mais é do que um variável do tipo char. Para ir colocando cada bit da codificação, 
	usaremos os operadores de manipulação de bits. 


	

*/








int main(int argc, char const *argv[])
{
	
	tabela freqs;

	freqs = contar_caracteres("teste.txt");
	Heap h = transformar_em_heap(freqs);
	HuffTree hf;

	cout << h << endl;

	
	return 0;
}