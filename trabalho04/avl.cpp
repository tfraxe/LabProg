/*
	Prazo: 5/07


*/

#include <algorithm>
using std::max;
#include "avl.hpp"



void inicializar(DicAVL &D) { D.raiz = nullptr; }

void terminar_noh(Noh *D) 
{
	
	if(D->esq != nullptr) terminar_noh(D->esq);
	if (D->dir != nullptr) terminar_noh(D->dir);
		
	delete D;
	D = nullptr;

}

void terminar(DicAVL &D)
{
	terminar_noh(D.raiz);
	delete &D;
}

int inserir_noh(Noh* raiz, Noh* novo) //insere novo nó na árvore AVL retornando a nova altura da árvore
{
	if (raiz == nullptr) 
	{
		raiz = novo;
		return 1;
	}

	int nova_altura_sub;
	if ( (novo->chave) > (raiz->chave) ) //inserindo na sub-árvore direita
	{
		nova_altura_sub = inserir_noh(raiz->dir, novo);
		int nova_altura = max(nova_altura_sub, raiz->esq->h) + 1;
		raiz->h = nova_altura;
		
		int diff_alturas = abs(nova_altura - raiz->esq->h);
		if (diff_alturas > 1) {}
		else return nova_altura; 
	} 

	else
	{
		if ((novo->chave) < (raiz->chave))
		{

		}

		else
		{
			throw "Chave já inserida!";
		}
	}
}


Noh* inserir (DicAVL &D, TC c, TV v)
{

}

//Noh* procurar(DicAVL &)

int main(int argc, char const *argv[])
{
	
	return 0;
}