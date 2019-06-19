/*

	TO-DO


	1) Sucessor
	2) Predecessor
	3) Remoção
	4) Busca
	5) Implementar dicionário e iterador. 



*/


#include <iostream>
using std::cin; using std::cout; using std::endl;


template <typename T, typename U>

struct BinaryNode
{
	
	T chave;
	U dado;
	BinaryNode* pai;
	BinaryNode* esquerdo;
	BinaryNode* direito;

	bool operator < (BinaryNode outro)  {return this->chave < outro.chave;}
	bool operator > (BinaryNode outro)  {return this->chave > outro.chave; }
	
	
	/*
	std::ostream& operator << (std::ostream& out)
	{
		return out << "[ " << this->dado << ", " << this->chave << "] ";	
	}
	*/
	

	/*
	void print()
	{
		cout << "[ " << this->dado << ", " << this->chave << "] "; 
	}
	*/


	BinaryNode() = default;

	void incluir(BinaryNode& novo)
	{

		if (this->esquerdo == nullptr || this->direito == nullptr)
		{
			if (novo < *this) this->esquerdo = &novo;
			else this->direito = &novo;
		}
		else
		{
			
			if (novo < *this) (this->esquerdo)->incluir(novo);
			else (this->direito)->incluir(novo);
		}
	}

	void traversal()
	{
		
		if (this->esquerdo != nullptr) {(this->esquerdo)->traversal();}
		cout << *this << endl;
		if (this->direito != nullptr) (this->direito)->traversal();
	}


};


template <typename T, typename U>
std::ostream& operator << (std::ostream& out, const BinaryNode<T, U>& bn)
{
	return out << "[ " << bn.dado << ", " << bn.chave << "] ";	
}




int main(int argc, char const *argv[])
{
	
	cout << "ai" << endl;
	BinaryNode<int, int> no = {100, 57, nullptr, nullptr, nullptr};

	BinaryNode<int, int> no2 = {50, 57, nullptr, nullptr, nullptr}; 


	BinaryNode<int, int> no3 = {150, 57, nullptr, nullptr, nullptr}; 

	no.incluir(no2); 

	no.incluir(no3);

	no.traversal();

	return 0;
}