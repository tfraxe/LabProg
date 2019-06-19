#include "huff.hpp"
#include <fstream>
using std::ifstream;
#include <iostream>
using std::cin;  using std::cout; using std::endl;
/*
#include <queue>
using std::queue;
*/
#include <stack>
using std::stack;



void print_huffTree(HuffTree& hf)
{
	vector<HuffNode> filhos_hn;
	vector<HuffNode> atuais_hn;
	filhos_hn.push_back(hf.back());

	while(!filhos_hn.empty())
	{
		atuais_hn = filhos_hn;
		filhos_hn.clear();

		for (auto ah : atuais_hn)
		{
			cout << ah;

			if(ah.esq != -1) filhos_hn.push_back(hf[ah.esq]);
			if(ah.dir != -1) filhos_hn.push_back(hf[ah.dir]);

			cout << " ";


		}

		atuais_hn.clear();
		cout << "||" << endl;
	}
}

tabela contar_caracteres(string nome_arquivo)
{
	ifstream is("teste.txt");

	char c;

	tabela frequencias;
	while (is.get(c))  
	{
		cout << c;
		if (frequencias.count(c) == 1) frequencias[c]++;
		else frequencias[c] = 1;
	}

	is.close();

	return frequencias;
}



Heap transformar_em_heap(tabela frequencias)
{
	vector<HeapNode> nodes;

	for (auto& f : frequencias)
	{
		nodes.push_back({ {f.first}, f.second});
	}

	
	return Heap(nodes);

}

HuffTree construir_HuffTree(Heap& h, tabela& frequencias)
{
	HuffTree hf;
	FastIndex fi;
	int index = 0; 

	
	for (auto& f : frequencias)
	{
		hf.push_back({ {f.first}, f.second, -1, -1 });  //Adicionado caracteres como folhas da HuffTree
		fi[{f.first}] = index++;

	}

	

	while (h.get_tamanho() != 1)
	{
		HeapNode min1 = h.extract_minimum();
		HeapNode min2 = h.extract_minimum();
		

		string concat_dado = min1.dado + min2.dado;
		int soma_pesos = min1.peso + min2.peso;
		
		HeapNode novo_no_heap = {concat_dado, soma_pesos};
		h.inserir(novo_no_heap);

		HuffNode novo_no_huff = {concat_dado, soma_pesos, fi[min1.dado], fi[min2.dado]};
		fi[concat_dado] = index++;
		hf.push_back(novo_no_huff);


	}

	return hf;
}

codificacao construir_codificacao(HuffTree& hf)
{
	
	
	HuffNode no_raiz = hf.back();
	stack<HuffNode> pilha;
	pilha.push(no_raiz);
	codificacao codigos;
	//char codigo = 0;
	string codigo = "";

	bool* visitado = new bool[hf.size()];

	
	for (bool* i = visitado; i < (visitado + hf.size()); ++i) *i = false;
	
	visitado[hf.size() - 1] = true;

	while (!pilha.empty())
	{
		HuffNode no_atual = pilha.top();

		if(no_atual.esq != -1 && !visitado[no_atual.esq])
		{
			pilha.push(hf[no_atual.esq]);
			visitado[no_atual.esq] = true;
			//codigo = (codigo << 1) | 0; 
			codigo = codigo + "0";
		}
		else if (no_atual.dir != -1 && !visitado[no_atual.dir])
		{
			pilha.push(hf[no_atual.dir]);
			visitado[no_atual.dir] = true;
			//codigo = (codigo << 1) | 1;	
			codigo = codigo + "1";
		}
		else
		{
			if(no_atual.dir == -1 && no_atual.esq == -1)
			{
				codigos[no_atual.dado[0]] = codigo;
				//cout << no_atual.dado << ": " << codigo << endl;
				
				
			}
			pilha.pop();
			//codigo = codigo >> 1;
			codigo.pop_back();
		}

	}

	return codigos;
}



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

int main(int argc, char const *argv[])
{
	tabela freqs;

	freqs = contar_caracteres("teste.txt");
	
	Heap h = transformar_em_heap(freqs);
	//cout << h << endl;
	
	HuffTree hf = construir_HuffTree(h, freqs);
	//print_huffTree(hf);
	
	
	codificacao codigos = construir_codificacao(hf);
	cout << codigos.size() << endl;
	
	for (auto c : codigos) cout << c.first << ", " << c.second << endl;
	

	cout << "oi" << endl;

	return 0;
}
