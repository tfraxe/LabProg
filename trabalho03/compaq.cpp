#include "huff.hpp"

#include <iostream>
#include <string>
#include <string.h>

using std::cout; using std::endl; using std::string;

int main(int argc, char const *argv[])
{
	
	if (argc != 4)
	{
		cout << "Número inválido de argumentos!" << endl;
		exit(-1);
	}
	
	string arquivo_origem = argv[2];
	string arquivo_saida = argv[3];
	string arg1 = argv[1];

	if(arg1 == "-c")
	{
		cout << arquivo_origem << endl;
		cout << arquivo_saida << endl;
		tabela freqs;
		int count_char = 0;
		freqs = contar_caracteres(arquivo_origem, count_char);
		if (count_char == 0)
		{ 
			codificacao c;
			HuffTree hut;
			criar_compactado(c, hut, count_char, arquivo_origem, arquivo_saida);
			exit(0);
		} 
		Heap h = transformar_em_heap(freqs);
		HuffTree hf = construir_HuffTree(h, freqs);
		codificacao codigos = construir_codificacao(hf);
		criar_compactado(codigos, hf, count_char, arquivo_origem, arquivo_saida);
	}

	else if (arg1 == "-d")
	{
		descompactar(arquivo_origem, arquivo_saida);
	}
}