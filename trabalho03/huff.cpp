#include "huff.hpp"
#include <fstream>
using std::ifstream; using std::ofstream;
#include <iostream>
using std::cin;  using std::cout; using std::endl;
/*
#include <queue>
using std::queue;
*/
#include <stack>
using std::stack;
#include <string>
using std::stoi; using std::getline;
#include <sstream>
using std::istringstream; 



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

tabela contar_caracteres(string nome_arquivo, int& count_char)
{
	ifstream is(nome_arquivo);

	char c;

	tabela frequencias;
	while (is.get(c))  
	{
		//cout << c;
		if (frequencias.count(c) == 1) frequencias[c]++;
		else frequencias[c] = 1;
		count_char++;
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

	if(hf.size() == 1) codigo = "0";

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

void criar_compactado(codificacao& c, HuffTree& hf, int num_char, string arquivo_origem, string arquivo_saida)
{
	ofstream os(arquivo_saida);

	os << "n" << endl;
	os << num_char << endl;
	
	os << "hf" << endl;

	for (auto h : hf)
	{
		if (h.esq == -1 && h.dir == -1)
		{
			if (h.dado == "\n") os << "el" << h.esq << "|" << h.dir << endl;
			else if (h.dado == "|") os << "ba" << h.esq << "|" << h.dir << endl;
			else os << h.dado[0] << h.esq << "|" << h.dir << endl; 
		}

		else
		{
			os << "o" << h.esq << "|" << h.dir << endl;
		}
	}

	os << "fh" << endl;
	
	if(num_char == 0) return;

	ifstream is(arquivo_origem);
	char d;
	unsigned char a = 0;
	int i = 0;

	string codigo = "";
	while(is.get(d))
	{
		/*
		codigo = codigo + c[d];
		
		if (codigo.size() >= 8)
		{
			string sub_cod = codigo.substr(0, 8);
			codigo = codigo.substr(8, codigo.size());
			
			a = 0;
			int i = 0;
			for (auto s : sub_cod)
			{
				if ( i != 0) a = (a << 1) | (s - 48);
				else a = a | (s-48);
				i++;
			}

			//std::cout << "Escreveu: " << (int) a << "no arquivo " << arquivo_saida << std::endl;
			os << a;
		}
		*/

		codigo = c[d];
	

		for (auto s : codigo)
		{
			if (i != 0) a = (a << 1) | (s - 48);
			else a = a | (s-48);
			i++;
			if (i == 8)
			{
				os << a;
				a = 0;
				i = 0;
			}
		}
	}


	if ( i != 0 )
	{
		a = a << (8 - i);
		os << a;
		a = 0;
		i = 0;
	}

	//cout << codigo << endl;
	/*
	if (codigo.size() > 0)
	{
		if (codigo.size() > 8) cout << "é maior que 8! " << codigo.size() << endl;
		a = 0;
		int i = 0;
		for (auto s : codigo)
		{
			if ( i != 0) a = (a << 1) | (s - 48);
			else a = a | (s-48);
			i++;
		}

		a = a << (8 - codigo.size());

		//cout << "Escreveu agora: " << (int) a << "no arquivo " << arquivo_saida << endl;	
		os << a;
	}
	*/



	os.close();
}


void descompactar(string arquivo_origem, string arquivo_saida)
{
	
	ifstream is(arquivo_origem);
	enum Mode {READING_COUNT, READING_HF, READING_CHAR};

	int num_char = 0;
	Mode modo;
	string linha = "";
	vector<HuffNode> hf;
	while( modo != READING_CHAR && getline(is, linha))
	{
		if(linha == "n") {modo = READING_COUNT; continue;}

		if(modo == READING_COUNT) 
		{
			if (linha == "hf") modo = READING_HF;
			else {num_char = stoi(linha, nullptr, 10);}
		}
		else if (modo == READING_HF)
		{
			if (linha == "fh") modo = READING_CHAR;
			else if (linha != "fh")
			{
				istringstream f(linha);
				string s1;
				getline(f, s1, '|');
				string dado;
				int esq;
				int dir;
				if(s1.substr(0, 2) == "el")
				{
					dado = "\n";
					//cout << "entrou2" << endl;
					esq = stoi(s1.substr(2, s1.size()), nullptr, 10);
					//cout << "saiu2" << endl;
				}
				else if (s1.substr(0, 2) == "ba")
				{
					dado = "|";
					//cout << "entrou2" << endl;
					esq = stoi(s1.substr(2, s1.size()), nullptr, 10);
				}
				else
				{
					dado = {s1[0]};
					//cout << "entrou3" << endl;
					//cout << s1 << endl;
					esq = stoi(s1.substr(1, s1.size()), nullptr, 10);
					//cout << "saiu3" << endl;
				}

				getline(f, s1, '|');
				dir = stoi(s1, nullptr, 10);

				hf.push_back({dado, 0, esq, dir}); 

			}
		
		}

		/*
		else if (modo == READING_CHAR)
		{
			char d;
			istringstream g(linha);
			g.get(d);
			cout << d << endl;
		}
		*/


	}

	if(modo == READING_CHAR)
	{
		char d;
		HuffNode hn;
		if (hf.size() > 0) hn = hf.back();
		int n = 0;
		char bit;

		ofstream os(arquivo_saida);
		while(is.get(d))
		{
			if (n == num_char) {break;}
			
			for(int i = 7; i >=0 && n< num_char; i--)
			{
				bit = (d >> i) & 1;
				if(hf.size() > 1)
				
				{
					if (bit == 0) hn = hf[hn.esq];
					else hn = hf[hn.dir];	
				}
				

				if(hn.esq == -1 && hn.dir == -1)
				{
					//cout << "Escreveu " << hn.dado << " ao arquivo de saída" << endl;
					os << hn.dado;
					hn = hf.back();
					n++;
				}
			}

		}

		os.close();
	}

}



/*

int main(int argc, char const *argv[])
{
	
	tabela freqs;

	int count_char = 0;

	freqs = contar_caracteres("teste.txt", count_char);
	cout << count_char << endl;
	
	Heap h = transformar_em_heap(freqs);
	//cout << h << endl;
	
	HuffTree hf = construir_HuffTree(h, freqs);
	//print_huffTree(hf);
	
	
	codificacao codigos = construir_codificacao(hf);
	cout << codigos.size() << endl;
	
	for (auto c : codigos) cout << c.first << ", " << c.second << endl;
	
	criar_compactado(codigos, hf, count_char, "teste.txt", "saida.txt");
	descompactar("saida.txt", "d.txt");
	//cout << "========================" << endl;
	//print_huffTree(hf);

	cout << "oi" << endl;

	return 0;
}
*/
