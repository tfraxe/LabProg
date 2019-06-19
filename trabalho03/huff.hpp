#ifndef HUFF_HPP
#define HUFF_HPP

#include "heap.hpp"

#include <vector>
using std::vector;
#include <map>
using std::map;
#include <string>
using std::string;

typedef struct hnode
{
	string dado;
	int peso;
	int esq; // índice na HuffTree em que se encontra o filho esquerdo
	int dir; // índice na HuffTree em que se encontra o filho direito

} HuffNode;

inline ostream& operator << (ostream& out, const HuffNode& hn)
{
	return out << "[" << "\\" + hn.dado << "|" << hn.peso << "|" << hn.esq << "|" << hn.dir << "]";
}



typedef vector<HuffNode> HuffTree; 

void print_huffTree(HuffTree& hf);

typedef map<string, int> FastIndex; //Será usado para facilitar o encontro dos índices na HuffTree.

typedef map<char, int> tabela; // Será usado para guardar as frequências de cada caractere que ocorre no text.

typedef map<char, string> codificacao;

tabela contar_caracteres(string nome_arquivo);

Heap transformar_em_heap(tabela frequencias);

HuffTree construir_HuffTree(Heap&, tabela& );


codificacao construir_codificacao(HuffTree&);

void criar_compactado(codificacao&, string arquivo_origem); 

/*
	Construir função de compactação. 
	1) Passar como argumento codificação obtida na função anterior e arquivo a ser compactado
	2) Ler cada caractere e:
		2.1) Para cada caractere, acessar codificação na tabela
		2.2) Concatenar codificação ao buffer
		2;3) Se tamanho do buffer + tamanho da codificação = 8, escrever no arquivo compactado. A escrita será feita
		lendo cada bit da string e adicionando a um char. O char então será escrito no arquivo compactado.
		2.4) Se o tamanho do buffer + tamanho da codificação > 8, concatenar parte da codificação cuja soma com buffer dá 8. Escrever no 
		arquivo como da maneira anterior. Escrever parte restante no buffer. Continuar iteração.
		2.5) Se o tamanho for menor, concatenar no buffer e continuar iteração. 
	3) É necessário adicionar um cabeçalho com a árvore de huffman. 


*/

#endif
