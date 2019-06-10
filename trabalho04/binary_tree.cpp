#include <iostream>
using std::cin; using std::cout; using std::endl;


template <typename T, typename U>

struct binary_node
{
	
	T chave;
	U dado;
	binary_node* pai;
	binary_node* esquerdo;
	binary_node* direito;

	bool operator < (binary_node outro)  {return this->chave < outro.chave;}
	bool operator > (binary_node outro)  {return this->chave > outro.chave; }
	
	/*
	std::ostream& operator << (std::ostream& out)
	{
		return out << "[ " << this->dado << ", " << this->chave << "] ";	
	}
	*/

	void print()
	{
		cout << "[ " << this->dado << ", " << this->chave << "] "; 
	}


	binary_node() = default;

	void incluir(binary_node& novo)
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
		this->print();
		if (this->direito != nullptr) (this->direito)->traversal();
	}


};



int main(int argc, char const *argv[])
{
	
	cout << "ai" << endl;
	binary_node<int, int> no = {100, 57, nullptr, nullptr, nullptr};

	binary_node<int, int> no2 = {50, 57, nullptr, nullptr, nullptr}; 


	binary_node<int, int> no3 = {150, 57, nullptr, nullptr, nullptr}; 

	no.incluir(no2); 

	no.incluir(no3);

	no.traversal();

	return 0;
}