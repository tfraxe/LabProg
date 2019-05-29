#include <iostream>
#include <chrono>
#include <climits>
#include <new>
using std::cout; using std::cin; using std::endl; using std::string; using std::nothrow;
#include "trabalho02.hpp"
#include "instancias_Reais_Trabalho_2.hpp"


void measure_time(const char* texto, const char* padrao, unsigned int tam_texto)
{
	unsigned int size_saida;
	if (tam_texto == UINT_MAX) size_saida = 10000000;
	else size_saida = tam_texto + 1;
	int* saida_kmp = new (nothrow) int[size_saida];
	int* saida_fb = new (nothrow) int[size_saida];
	if (saida_kmp == nullptr || saida_fb == nullptr)
	{
		cout << "Não foi possível alocar memória para vetor de saída. Saindo.." << endl;
		exit(-1);
	}
	std::clock_t inicio = std::clock();
	auto t_inicio = std::chrono::high_resolution_clock::now();
	buscar_kmp(padrao, texto, saida_kmp);
	std::clock_t fim = std::clock();
	auto t_fim = std::chrono::high_resolution_clock::now();

	cout << "\033[35m======================================================\033[0m" << endl;
	cout << "Tempos de Knuth-Morris-Pratt" << endl;
	cout << "\033[1;32mTempo de CPU:\033[0m " << 1000.0 * (fim-inicio) / CLOCKS_PER_SEC << " ms" << endl;
	cout << "\033[1;33mTempo real transcorrido:\033[0m " << std::chrono::duration<double, std::milli>(t_fim - t_inicio).count() << " ms" << endl;
	cout << "\033[35m======================================================\033[0m" << endl;


	inicio = std::clock();
	t_inicio = std::chrono::high_resolution_clock::now();
	buscar_forca_bruta(texto, padrao, saida_fb);
	fim = std::clock();
	t_fim = std::chrono::high_resolution_clock::now();

	cout << "\033[35m======================================================\033[0m" << endl;
	cout << "Tempos de Força Bruta" << endl;
	cout << "\033[1;32mTempo de CPU:\033[0m " << 1000.0 * (fim-inicio) / CLOCKS_PER_SEC << " ms" << endl;
	cout << "\033[1;33mTempo real transcorrido:\033[0m " << std::chrono::duration<double, std::milli>(t_fim - t_inicio).count() << " ms" << endl;
	cout << "\033[35m======================================================\033[0m" << endl;

	cout << "\033[1;36mOs dois vetores de saída são iguais??\033[0m " << (vetores_iguais(saida_kmp, saida_fb) ? "Sim!" : "Não!") << endl;






}


int main(int argc, char const *argv[])
{
	bool continuar = false;

	do
	{
		system("clear");
		cout << "=======================================================================" << endl;
		cout << "Trabalho 02 - Busca de Subsequência de Caracteres\n";
		cout << "Implementação feita por Thiago Fraxe Correia Pessoa\n";
		cout << "=======================================================================\n\n";

		cout << "Digite \'1\' para cronometrar Pior Caso 1" << endl;
		cout << "Digite \'2\' para cronometrar Pior Caso 2" << endl;
		cout << "Digite \'3\' para cronometrar usando Instâncias Aleatórias" << endl;
		cout << "Digite \'4\' para cronometrar usando Texto Real" << endl;

		char selection = '0';

		cout << "> ";
		cin >> selection;

		switch(selection)
		{
			case '1':
			case '2':
			case '3':
			{

				unsigned int tam_padrao = 0;
				unsigned int tam_texto = 0;
				bool erro = false;
				do
				{
					erro = false;
					cout << "Escolha o tamanho do padrao: ";
					cin >> tam_padrao;
					cout << "Escola o tamanho do texto: ";
					cin >> tam_texto;
					if (tam_padrao > tam_texto) { cout << "Erro! Tamanho do padrão não pode ser maior do que o do texto!" << endl; erro = true;}	
				} while(erro);

				const char* padrao = new (nothrow) char[tam_padrao];
				const char* texto = new (nothrow) char[tam_texto];

				if(padrao == nullptr || texto == nullptr)
				{
					cout << "Não foi possível alocar memória para texto ou padrão. Saindo.." << endl;
					return -1;
				}

				if(selection == '1') pior_caso1((char*) padrao, tam_padrao, (char*) texto, tam_texto);
				else if(selection == '2') pior_caso2((char*) padrao, tam_padrao, (char*) texto, tam_texto);
				else
				{
					
					unsigned short int l = 0;
					do
					{
						cout << "Escolha o valor de l (as primeiras l letras do alfabeto): " << endl;
						erro = false;
						cin >> l;
						if (l < 1 || l > 26 ) erro = true;
					} while(erro);

					padrao = gerar_texto_aleatorio(tam_padrao, l);
					texto = gerar_texto_aleatorio(tam_texto, l);
				}

				measure_time(texto, padrao, tam_texto);
				delete[] padrao;
				delete[] texto;
				break;
			}

			case '4':
			{
				bool erro2 = false;
				int numero_padrao = 0;
				do
				{
					erro2 = false;
					cout << "Escolha um número entre 0 e 35129 para especificar padrão utilizado" << endl;
					cin >> numero_padrao;
					if (numero_padrao < 0 || numero_padrao > 35129) erro2 = true;	
				} while (erro2);

				measure_time(Texto_Livros, Padroes_Palavras[numero_padrao], UINT_MAX);

				break;
			}
			default:
				break;
				


		}

		cout << "Deseja continuar? <s/n>" << endl;
		char escolha = 'o';
		cout << "> ";
		cin >> escolha;
		if (escolha == 's') continuar = true;
		else continuar = false;



	} while( continuar );
	return 0;
}