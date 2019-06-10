#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <iostream>
using std::vector; using std::ostream;
#include <string>
using std::string;



typedef struct node
{
	string dado;
	int peso;
} HeapNode;

inline bool operator < (const HeapNode& hn1, const HeapNode& hn2) { return hn1.peso < hn2.peso; }
inline bool operator > (const HeapNode& hn1, const HeapNode& hn2) { return hn1.peso > hn2.peso; }

inline ostream& operator << (ostream& out, const HeapNode hn)
{
	return out << "[" << hn.dado << "|" << hn.peso << "]";
}

class Heap
{
private:
	vector<HeapNode> nodes;

	int tam_heap;

	int esq(int index) {return 2*index + 1;}
	int dir(int index) {return 2*index + 2;}
	int pai(int index) {return (index - 1)/2;}

	void min_heapify(int index); // Supõe que árvores enraizadas em esq(index) e dir(index) são min-heaps e "corrige" nó no índice i caso ele não satisfaça propriedade da min-heap
public:

	Heap(vector<HeapNode>);

	friend std::ostream& operator << (std::ostream& out, const Heap h)
	{
		for (auto n : h.nodes)
		{
			out << n << " ";
		}

		return out;
	}


	unsigned int get_tamanho() {return tam_heap;}

	HeapNode peek_minimum(); // Retorna o menor (primeiro) nó da heap, sem excluí-lo.
	HeapNode extract_minimum(); // Retorna o menor (primeiro) nó da heap, removendo-o. 
	void diminuir_peso(int pos, HeapNode hn); // Diminui o peso do nó na posição pos da heap.
	void inserir(HeapNode new_node); 


};

#endif