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

tabela contar_caracteres(string nome_arquivo, int&);

Heap transformar_em_heap(tabela frequencias);

HuffTree construir_HuffTree(Heap&, tabela& );


codificacao construir_codificacao(HuffTree&);

void criar_compactado(codificacao&, HuffTree&, int,  string arquivo_origem, string arquivo_saida); 

void descompactar(string, string);


#endif
