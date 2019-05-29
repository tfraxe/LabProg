#include "heap.hpp"

void Heap::min_heapify(unsigned int index)
{
	bool continuar = true;

	while(continuar)

	{

		unsigned int l = Heap::esq(index);
		unsigned int r = Heap::dir(index);
		unsigned menor = 0;

		if ( (l <= (this->tam_heap) - 1) && ((this->nodes[l]).peso < (this->nodes[index]).peso)) menor = l;
		else menor = index;

		if ( (r <= (this->tam_heap) - 1) && ((this->nodes[r]).peso < (this->nodes[menor]).peso)) menor = r;

		if (menor != index)
		{
			HeapNode temp = this->nodes[index];
			this->nodes[index] = this->nodes[menor];
			this->nodes[menor] = temp;

			index = menor;
			continuar = true;
		}

		else continuar = false;

	}


}

Heap::Heap(vector<HeapNode> u_nodes)
{
	this->tam_heap = u_nodes.size();
	this->nodes = u_nodes;

	for (int i = (this->tam_heap - 1)/2; i >= 0; i--) {std::cout << i << std::endl; Heap::min_heapify(i);}
}


int main(int argc, char const *argv[])
{
	vector<HeapNode> teste = {{'a', 10}, {'a', 9}, {'a', 8}, {'a', 7}, {'a', 6}, {'a', 5}, {'a', 4}, {'a', 3}, {'a', 2}, {'a', 1}};
	std::cout << "aiii" << std::endl;
	Heap h(teste);
	std::cout << h << std::endl;
	return 0;
}

