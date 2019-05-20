#include "trabalho02.hpp"
#include <iostream>
using std::cout; using std::endl;

int main(int argc, char const *argv[])
{
	const char string1[] = "Oi, meu nome é Thiago";
	const char string2[] = "Oi, meu nome é Thiago";
	cout << (sao_iguais(string2, string1) ? "iguais" : "diferentes") << endl;
	cout << "que" << endl;

	const char doido[] = "ababaaba";
	const char padrao[] = "aba";
	int* saida = new int[9];

	cout << (ha_ocorrencia(padrao, doido) ? "ocorre" : "nao") << endl;
	buscar_forca_bruta(doido, padrao, saida);

	for(int* s = saida; *s != -1; s++) cout << *s << endl;

	int* saida2 = new int[9];



	buscar_kmp(padrao, doido, saida2);
	for(int* s = saida2; *s != -1; s++) cout << *s << endl;


	//teste de geração de texto aleatório

	unsigned int size = 10;
	char* test_texto = new char[size];
	try
	{
		gerar_texto_aleatorio2(test_texto, size, 3);
		
	}

	catch(int e)
	{
		cout << "Erro numero " << "ocorreu" << endl;
		return -1;
	}

	for (char* i = test_texto; i < test_texto + size; i++) cout << *i << "";
	cout << endl;

	

	return 0;
}