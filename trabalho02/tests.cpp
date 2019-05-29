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
	const char* test_texto = gerar_texto_aleatorio(10, 6);
	const char* test_padrao = gerar_texto_aleatorio(size/5, 6);

	int* saida_kmp = new int[size+1];
	int* saida_fb = new int[size+1];

	buscar_kmp(test_padrao, test_texto, saida_kmp);
	buscar_forca_bruta(test_texto, test_padrao, saida_fb);

	if (vetores_iguais(saida_kmp, saida_fb)) cout << "são iguais" << endl;

	for(const char* t = test_texto; *t != '\0'; t++) cout << *t;
	cout << endl;

	for(const char* p = test_padrao; *p != '\0'; p++) cout << *p;
	cout << endl;

	char* padrao_piorCaso = new char[size/5];
	char* texto_piorCaso = new char[size];

	pior_caso2(padrao_piorCaso, size/5, texto_piorCaso, size);

	for(const char* t = padrao_piorCaso; *t != '\0'; t++) cout << *t;
	cout << endl;

	for(const char* p = texto_piorCaso; *p != '\0'; p++) cout << *p;
	cout << endl;



	

	return 0;
}