#ifndef TRABALHO02_HPP
#define TRABALHO02_HPP

#include <ctime>
#include <random>

//LEMBRE-SE: NA GERAÇÃO DE STRINGS, LEMBRE-SE DE ALOCAR +1 NO TAMANHO PARA ADICIONAR O \0!!!

// Checa se duas strings são iguais

bool sao_iguais(const char* string1, const char* string2)
{
	const char* s1;
	const char* s2;
	for (s1 = string1, s2 = string2; *s1 != '\0'; s1++)
	{
		if(*s1 != *(s2++)) return false;
	}

	if (*s2 == '\0') return true;
	else return false;
}

void gerar_texto_aleatorio(char* inicio, unsigned int size, unsigned short int l)
{
	if(l < 1 || l > 26) throw -1;
	srand(time(NULL));
	for (char* i = inicio; i < inicio + size; i++) *i = "abcdefghijklmnopqrstuvwxyz"[rand() % l];

}

void gerar_texto_aleatorio2(char* inicio, unsigned int size, unsigned short int l)
{
	if(l < 1 || l > 26) throw -1;
	srand(time(NULL));
	for (char* i = inicio; i < inicio + size; i++) *i = 97 + (rand() % l);

}

void pior_caso1(char* padrao, unsigned int size_padrao, char* texto, unsigned int size_texto)
{
	for (char* i = texto; i < texto + size_texto; i++) *i = 'a';
	for (char* p = padrao; p < padrao + (size_padrao - 1); p++) *p = 'a';

	padrao[size_padrao - 1] = 'b';

}


void pior_caso2(char* padrao, unsigned int size_padrao, char* texto, unsigned int size_texto)
{
	for (char* i = texto; i < texto + size_texto; i++) *i = 'a';
	for (char* p = padrao; p < padrao + size_padrao; p++) *p = 'a';


}

// Checa se há ocorrência do padrão a partir da posição indicada por texto

bool ha_ocorrencia(const char* padrao, const char* texto)
{
	const char* p;
	const char* t;
	for(p = padrao, t = texto; *p != '\0'; p++)
	{
		if (*p != *(t++)) return false;
	}

	return true;
}

// Usa força bruta para procurar por substrings
void buscar_forca_bruta(const char* texto, const char* padrao, int* saida)
{
	int* s = saida;
	for(const char* t = texto; *t != '\0'; t++)
	{
		if( ha_ocorrencia(padrao, t) ) *(s++) = t - texto; 
	}

	*s = -1;
}

void preencher_pi(unsigned int* pi_inicio, unsigned int* pi_final, const char* padrao)
{
	*pi_inicio = 0;
	unsigned int* k;
	for (unsigned int* i = pi_inicio + 1; i < pi_final+1; i++)
	{
		k = i-1;
		for(;;)
		{
			unsigned int l = *k;
			if (l==0) 
			{
				if (*padrao == padrao[i - pi_inicio]) {*i = 1; break;}
				else {*i = 0; break;}
			}

			else
			{
				if(padrao[i - pi_inicio] == padrao[l]) {*i = l+1; break;}
				else k = i + (l-1);
			}
		}
	}
}

unsigned int sizeOf(const char* p)
{
	unsigned int tam = 0;

	const char* p_iter = p;

	while(*(p_iter++) != '\0') ++tam;

	return tam;
}

void buscar_kmp(const char* padrao, const char* texto, int* saida)
{
	unsigned int size_padrao = sizeOf(padrao);
	unsigned int size_texto = sizeOf(texto);
	unsigned int* pi = new unsigned int[size_padrao];

	preencher_pi(pi, pi + (size_padrao - 1), padrao);

	unsigned int i = 0;
	unsigned int j = 0;
	int* s = saida;

	while (i < size_texto)
	{
		if (texto[i] != padrao[j])
		{
			if (j == 0) ++i;
			else j = pi[j-1]; //Aqui que o "deslocamento" é feito. A comparação será feita com o elemento imediamente posterior ao último que está no maior prefixo que também é sufixo p[j-1]
		}

		else
			if(j == size_padrao - 1) {*(s++) = i-j; j = pi[j]; ++i;} //outro deslocamento 
			else {++i; ++j;}

	}

	delete[] pi;
	*s = -1;


}
#endif