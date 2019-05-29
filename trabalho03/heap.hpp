#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <iostream>
using std::vector; using std::ostream;

typedef struct node
{
	char dado;
	int peso;
} HeapNode;


class Heap
{
private:
	vector<HeapNode> nodes;

	unsigned int tam_heap;

	unsigned int esq(unsigned int index) {return 2*index + 1;}
	unsigned int dir(unsigned int index) {return 2*index + 2;}

	void min_heapify(unsigned int index); // Supõe que árvores enraizadas em esq(index) e dir(index) são min-heaps e "corrige" nó no índice i caso ele não satisfaça propriedade da min-heap
public:

	Heap(vector<HeapNode>);

	friend std::ostream& operator << (std::ostream& out, const Heap h)
	{
		for (auto n : h.nodes)
		{
			out << n.peso << " ";
		}

		return out;
	}

	HeapNode peek_minimum(); // Retorna o menor (primeiro) nó da heap, sem excluí-lo.
	HeapNode extract_minimum(); // Retorna o menor (primeiro) nó da heap, removendo-o. 
	void diminuir_peso(unsigned int pos, int novo_peso); // Diminui o peso do nó na posição pos da heap.
	void inserir(HeapNode new_node); 


};

#endif