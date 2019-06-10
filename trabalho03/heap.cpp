#include "heap.hpp"
#include <limits>
using std::numeric_limits;

void Heap::min_heapify(int index)
{
	bool continuar = true;

	while(continuar)

	{

		int l = Heap::esq(index);
		int r = Heap::dir(index);
		int menor = 0;

		if ( (l <= (this->tam_heap) - 1) && /*((this->nodes[l]).peso < (this->nodes[index]).peso)*/ nodes[l] < nodes[index]) menor = l;
		else menor = index;

		if ( (r <= (this->tam_heap) - 1) && /*((this->nodes[r]).peso < (this->nodes[menor]).peso)*/ nodes[r] < nodes[menor]) menor = r;

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

	for (int i = (this->tam_heap - 1)/2; i >= 0; i--) {Heap::min_heapify(i);}
}

HeapNode Heap::peek_minimum()
{
	if(tam_heap == 0) throw "[Erro no peeking]: A heap está vazia!";
	return this->nodes[0];
}


HeapNode Heap::extract_minimum()
{

	if (tam_heap == 0) throw "[Erro na remoção]: A heap está vazia!";
	HeapNode min = this->nodes[0];
	this->nodes[0] = this->nodes[--tam_heap];
	this->nodes.pop_back();
	this->min_heapify(0);
	return min;
}

using std::cout; using std::endl;

void Heap::diminuir_peso(int pos, HeapNode hn)
{
	if (hn > nodes[pos]) throw "[Erro no diminuir_peso]: Novo peso é maior do que peso atual";

	nodes[pos] = hn;

	int pai = Heap::pai(pos);
	while ( (pos > 0) && (nodes[pai] > nodes[pos]) )
	{
		HeapNode temp = nodes[pos];
		nodes[pos] = nodes[pai];
		nodes[pai] = temp;

		pos = pai;
		pai = Heap::pai(pos);

	}

}


void Heap::inserir(HeapNode new_node)
{
	tam_heap++;
	nodes.push_back({"a", numeric_limits<int>::max()}); 
	Heap::diminuir_peso(tam_heap - 1, new_node);

}


/*
int main(int argc, char const *argv[])
{
	
	vector<HeapNode> teste = {{'a', 10}, {'a', 9}, {'a', 8}, {'a', 7}, {'a', 6}, {'a', 5} /*, {'a', 4}, {'a', 3}, {'a', 2}, {'a', 1}};
	Heap h(teste);
	cout << h << endl;

	//h.diminuir_peso(2, {'a', 2});

	h.inserir({'a', -1});
	
	cout << h << endl;

	h.extract_minimum();

	cout << h << endl;

	h.extract_minimum();

	cout << h << endl;

	h.extract_minimum();

	cout << h << endl;

	h.extract_minimum();

	cout << h << endl;

	h.extract_minimum();

	cout << h << endl;

	h.extract_minimum();

	cout << h << endl;

	h.extract_minimum();

	cout << h << endl;

	h.extract_minimum();

	cout << h << endl;





	
	return 0;
}
*/

