#include "trabalho01.hpp"
#include "instancias_ruins_Quicksort.hpp"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
using std::cout; using std::cin; using std::endl; using std::string;
#include <new>
using std::nothrow;

void measure_time(int* vetor, int tamanho, void(*sort)(int*, int*), std::string sort_name)
{
	int* vetor_quicksort = new(nothrow) int[tamanho];
	if(vetor_quicksort == nullptr) {cout << "Erro ao copiar vetor" << endl; return;}
	copiar_vetor(vetor, tamanho, vetor_quicksort);
		
		
	std::clock_t inicio = std::clock();
	auto t_inicio = std::chrono::high_resolution_clock::now();
	sort(vetor_quicksort, vetor_quicksort+tamanho);
	std::clock_t fim = std::clock();
	auto t_fim = std::chrono::high_resolution_clock::now();


	cout << "\033[35m======================================================\033[0m" << endl;
	cout << "Tempos de " << sort_name << ": " << endl;
	cout << "\033[1;32mTempo de CPU:\033[0m " << 1000.0 * (fim-inicio) / CLOCKS_PER_SEC << " ms" << endl;
	cout << "\033[1;33mTempo real transcorrido:\033[0m " << std::chrono::duration<double, std::milli>(t_fim - t_inicio).count() << " ms" << endl;
	cout << "\033[1;36mVetor ordenado?\033[0m " << (vetor_ordenado(vetor_quicksort, tamanho) ? "Vetor está ordenado!" : "Vetor não está ordenado!") << endl;
	//print_vetor(vetor_quicksort, vetor_quicksort+tamanho);
	
	cout << "\033[35m======================================================\033[0m" << endl;
	
	delete[] vetor_quicksort;
}

void measure_time(int* vetor, int tamanho)
{
	int* vetor_quicksort = new(nothrow) int[tamanho];
	if(vetor_quicksort == nullptr) {cout << "Erro ao copiar vetor" << endl; return;}
	copiar_vetor(vetor, tamanho, vetor_quicksort);
		
		
	std::clock_t inicio = std::clock();
	auto t_inicio = std::chrono::high_resolution_clock::now();
	quicksort(vetor_quicksort, 0, tamanho-1);
	std::clock_t fim = std::clock();
	auto t_fim = std::chrono::high_resolution_clock::now();


	cout << "\033[35m======================================================\033[0m" << endl;
	cout << "Tempos de " << "QUICKSORT INDICES" << ": " << endl;
	cout << "\033[1;32mTempo de CPU: \033[0m" << 1000.0 * (fim-inicio) / CLOCKS_PER_SEC << " ms" << endl;
	cout << "\033[1;33mTempo real transcorrido:\033[0m " << std::chrono::duration<double, std::milli>(t_fim - t_inicio).count() << " ms" << endl;
	/*cout << "\033[1;36mVetor ordenado:\033[0m";
	print_vetor(vetor_quicksort, vetor_quicksort+tamanho);
	*/
	cout << "\033[1;36mVetor ordenado?\033[0m " << (vetor_ordenado(vetor_quicksort, tamanho) ? "Vetor está ordenado!" : "Vetor não está ordenado!") << endl;
	cout << "\033[35m======================================================\033[0m" << endl;
	delete[] vetor_quicksort;
}

int main(int argc, char const *argv[])
{
	bool continuar = false;
	do
	{
		system("clear");
		cout << "=======================================================================" << endl;
		cout << "Trabalho 01 - Cronometragem de diferentes implementações de QUICKSORT\n";
		cout << "Implementação feita por Thiago Fraxe Correia Pessoa\n";
		cout << "=======================================================================\n\n";

		cout << "Digite \'a\' para cronometrar usando vetor aleatório" << endl;
		cout << "Digite \'b\' para cronometrar usando gerador de piores instâncias" << endl;
		char selection = 'o';
		int* novo_vetor = nullptr;
		size_t tamanho = 0;

		cout << "> ";
		cin >> selection;

		switch(selection)
		{
			case 'a':
			{
				int fim_intervalo = 0;
				int inicio_intervalo = 0;
				cout << "Escolha o tamanho do vetor: ";
				cin >> tamanho;
				cout << "Escolha o início do intervalo: "; 
				cin >> inicio_intervalo;
				cout << "Escolha o fim do intervalo: ";
				cin >> fim_intervalo;

				novo_vetor = gerar_vetor(tamanho, inicio_intervalo, fim_intervalo);

				if (novo_vetor == nullptr) return -1;
				break;
			}
			case 'b':
			{
				cout << "Escolha o tamanho do vetor: ";
				cin >> tamanho;
				novo_vetor = new(nothrow) int[tamanho];
				if(novo_vetor == nullptr) {cout << "Erro ao alocar vetor!"; return -1;}
				bool creation_not_successful = escrever_instancia(novo_vetor, tamanho);
				if (creation_not_successful) {cout << "Erro ao criar vetor!"; return -1;}
				else {cout << "\033[1;32mNovo vetor criado\033[0m!" << endl; /*print_vetor(novo_vetor, novo_vetor+tamanho);*/}
				break;
			}
			default:
				return -1;
				break;

		}

		measure_time(novo_vetor, tamanho);
		measure_time(novo_vetor, tamanho, quicksort_ponteiros, "QUICKSORT PONTEIROS");
		measure_time(novo_vetor, tamanho, quicksort_memoria, "QUICKSORT MEMÓRIA");
		measure_time(novo_vetor, tamanho, quicksort_mediana_medianas, "QUICKSORT MEDIANA DAS MEDIANAS");
		measure_time(novo_vetor, tamanho, quicksort_aleatorio, "QUICKSORT ALEATÓRIO");

		delete[] novo_vetor;

		cout << "Deseja continuar? " << endl;
		char escolha = 'o';
		cout << "> ";
		cin >> escolha;
		if (escolha == 's') continuar = true;
		else continuar = false;


	} while (continuar);
	return 0;
}