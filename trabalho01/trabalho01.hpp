#ifndef TRABALHO01_HPP
#define TRABALHO01_HPP

#include <iostream>
#include <cmath>
#include <ctime>
#include <new>
#include <random>
using std::cout; using std::endl; using std::nothrow; 


inline int escolher_pivo(int inicio, int ultimo)
{
	return inicio + floor((ultimo+1-inicio)/2);
}

inline int* escolher_pivo(int* inicio, int* ultimo)
{
	return inicio + (int) floor((ultimo+1-inicio)/2);
}

int* escolher_pivo_aleatorio(int* inicio, int* fim)
{
	srand(time(NULL));
	size_t size_vetor = fim - inicio;
	return inicio + rand() % size_vetor;
}


int* particionamento_lomuto(int* inicio, int* pivo,  int* fim) //retorna a nova posição do pivô
{
	int temp = 0;
	temp = *inicio;
	*inicio = *pivo;
	*pivo = temp;

	int* menores = inicio;
	
	for(int* j = inicio + 1; j != fim; j++)
	{
		if (*j <= *inicio) // lembre-se que, neste momemento, o elemento pivô está sendo apontado por "início"
		{
			
			
			int temporario = *j;
			*j = *(menores+1);
			*(menores+1) = temporario;
			menores++;
			
		}
	}

	temp = *menores;
	//cout << *menores << endl;
	*menores = *inicio;
	*inicio = temp;

	return menores; //pointer to new pivot position
}

struct ponteiros 
{
	int* fim_menores;
	int* inicio_maiores;
};

struct ponteiros particionamento_triplo(int* inicio, int* pivo, int* fim) // particiona um vetor em [menores|iguais|maiores]
{

	//Coloca o elemento apontado por pivo no início do vetor. Não sei se este passo é realmente necessário aqui. Investigar. 
	int temp =  0;
	temp = *inicio;
	*inicio = *pivo;
	*pivo = temp;

	int* menores = NULL; // inicializa "fora" do vetor
	int* iguais = inicio; // como no início está o próprio elemento vetor, então igual começa apontado para ele.

	int elementoPivo = *inicio;

	for (int* j = inicio+1; j != fim; j++)
	{
		if (*j == elementoPivo)
		{
			//Troca o elemento que está em j com o elemento que está em iguais+1, e incrementa "iguais"". 
			int temporario = *j;
			*j = *(iguais+1);
			iguais = iguais + 1;
			*iguais = temporario;
		}


		else if (*j < elementoPivo)
		{
			//Coloca elemento apontado por j em menores+1, incrementa menores; coloca elementos que estava em menores+1 em iguais+1, incrementa iguais+1; coloca elemento que estava em iguais+1 em j.
			if (menores == NULL) menores = inicio;
			else ++menores;

			int temporario = *menores;
			*menores = *j;

			iguais = iguais + 1;

			int temporario2 = *iguais;
			*iguais = temporario;

			if( iguais != j) *j = temporario2;
		}
	}

	struct ponteiros pointers = {NULL, NULL};
	pointers.fim_menores = menores;
	pointers.inicio_maiores = iguais+1;

	return pointers;

}

struct indices
{
	int fim_menores;
	int inicio_maiores;
};

struct indices particionamento_triplo(int* v, int inicio, int pivo, int fim) // particiona um vetor em [menores|iguais|maiores]
{

	//Coloca o elemento apontado por pivo no início do vetor. Não sei se este passo é realmente necessário aqui. Investigar. 
	int temp =  0;
	temp = v[inicio];
	v[inicio] = v[pivo];
	v[pivo] = temp;

	int menores = inicio-1; // inicializa "fora" do vetor
	int iguais = inicio; // como no início está o próprio elemento pivô, então igual começa apontado para ele.

	int elementoPivo = v[inicio];

	for (int j = inicio+1; j != fim+1; j++)
	{
		if (v[j] == elementoPivo)
		{
			//Troca o elemento que está em j com o elemento que está em iguais+1, e incrementa "iguais"". 
			int temporario = v[j];
			v[j] = v[iguais+1];
			iguais = iguais + 1;
			v[iguais] = temporario;
		}


		else if (v[j] < elementoPivo)
		{
			//Coloca elemento apontado por j em menores+1, incrementa menores; coloca elementos que estava em menores+1 em iguais+1, incrementa iguais+1; coloca elemento que estava em iguais+1 em j.
			++menores;

			int temporario = v[menores];
			v[menores] = v[j];

			iguais = iguais + 1;

			int temporario2 = v[iguais];
			v[iguais] = temporario;

			if( iguais != j) v[j] = temporario2;
		}
	}

	struct indices index = {-1, -1};
	index.fim_menores = menores;
	index.inicio_maiores = iguais+1;

	return index;

}

void quicksort_ponteiros(int* inicio, int* fim) //Uma possível causa de confusão: "fim" é um ponteiro que aponta para "fora" do vetor, 1 posição depois do último elemento.
{
	if (inicio == fim-1) return;

	int* novaPosicaoPivo = particionamento_lomuto(inicio, escolher_pivo(inicio, fim-1), fim);
	//cout << "inicio: " << *inicio << " pivo: " << *novaPosicaoPivo << " fim: " << *(fim-1) << endl;
	if(novaPosicaoPivo != inicio) quicksort_ponteiros(inicio, novaPosicaoPivo);
	if (novaPosicaoPivo != fim-1) quicksort_ponteiros(novaPosicaoPivo+1, fim);

	/*
	struct ponteiros pointers = particionamento_triplo(inicio, escolher_pivo(inicio, fim), fim);
	if (pointers.fim_menores != NULL) quicksort_ponteiros(inicio, pointers.fim_menores + 1);
	if (pointers.inicio_maiores != fim) quicksort_ponteiros(pointers.inicio_maiores, fim);
	*/
}

void quicksort(int* vetor, int inicio, int fim)
{
	if (inicio == fim) return;
	

	struct indices indexes = particionamento_triplo(vetor, inicio, escolher_pivo(inicio, fim), fim);
	if (indexes.fim_menores != inicio-1)  quicksort(vetor, inicio, indexes.fim_menores);
	if (indexes.inicio_maiores != fim+1)  quicksort(vetor, indexes.inicio_maiores, fim);

}

void quicksort_aleatorio(int* inicio, int* fim) //Uma possível causa de confusão: "fim" é um ponteiro que aponta para "fora" do vetor, 1 posição depois do último elemento.
{
	if (inicio == fim-1) return;

	struct ponteiros pointers = particionamento_triplo(inicio, escolher_pivo_aleatorio(inicio, fim), fim);
	if (pointers.fim_menores != NULL) quicksort_aleatorio(inicio, pointers.fim_menores + 1);
	if (pointers.inicio_maiores != fim) quicksort_aleatorio(pointers.inicio_maiores, fim);
}

void quicksort_memoria(int* inicio, int* fim)
{
	while (fim-inicio > 1)
	{
		struct ponteiros pointers = particionamento_triplo(inicio, escolher_pivo(inicio, fim), fim);

		if(pointers.fim_menores == NULL) pointers.fim_menores = inicio;
			
			
		size_t tamMenores = (pointers.fim_menores+1) - inicio;
		size_t tamMaiores = (fim - pointers.inicio_maiores);

		if (tamMenores < tamMaiores)
		{
			quicksort_memoria(inicio, pointers.fim_menores+1);
			if (pointers.inicio_maiores != fim-1)
			{
				inicio = pointers.inicio_maiores;
				//pivo = inicio;
			}
			else return;
		}

		else
		{
			quicksort_memoria(pointers.inicio_maiores, fim);
			if (inicio != pointers.fim_menores)
			{
				fim = pointers.fim_menores + 1;
				//pivo = inicio;
			}
			else return;
		}
	}


	
	return;
}


inline int indexOf(int* vetor, int* elemento) //retorna o índice de um elemento de um vetor de inteiros.
{
	if (elemento == NULL) return -1;
	return elemento-vetor;
}

/*
int* quickselect(int* inicio, int* fim, int k)
{
	if (k >= (fim - inicio)) return NULL; //retorna nulo caso k seja maior do que o tamanho do vetor
	if(inicio == fim-1) return inicio; // se o vetor tiver um único elemento, retorne este elemento

	int* novaPosicaoPivo = particionamento_lomuto(inicio, fim); //para fazer o particionamento, vamos escolher sempre o primeiro elemento do vetor

	if (indexOf(inicio, novaPosicaoPivo) == k) return novaPosicaoPivo;
	else 
	{
		if(k < indexOf(inicio, novaPosicaoPivo)) return quickselect(inicio, novaPosicaoPivo, k);
		else return quickselect(novaPosicaoPivo+1, fim, k - indexOf(inicio, novaPosicaoPivo+1));
	}
}
*/

int* quickselect(int* inicio, int* fim, int k)
{
	if (k >= (fim - inicio)) NULL; //retorna nulo caso k seja maior do que o tamanho do vetor
	if(inicio == fim-1) return inicio; // se o vetor tiver um único elemento, retorne este elemento

	struct ponteiros pointers = particionamento_triplo(inicio, inicio,  fim); //para fazer o particionamento, vamos escolher sempre o primeiro elemento do vetor
	if(pointers.fim_menores == NULL) pointers.fim_menores = inicio;
	else pointers.fim_menores += 1;

	//temporario



	if (k >= indexOf(inicio, pointers.fim_menores) && k <= indexOf(inicio, pointers.inicio_maiores - 1)) return inicio + k;
	else 
	{
		if(k < indexOf(inicio, pointers.fim_menores)) return quickselect(inicio, pointers.fim_menores, k);
		else return quickselect(pointers.inicio_maiores, fim, k - indexOf(inicio, pointers.inicio_maiores));	
		 
	}
}


void print_vetor(int* inicio, int* fim)
{
	cout << "[";
	for (int* i = inicio; i != fim; i++)
		cout << *i << (i != fim-1 ? ", ": "");
	cout << "]\n";
}
//Corrigir mediana_das_medianas
struct ponteiros mediana_das_medianas(int* v, int* fim, int k) //nesta implementação, vamos usar quickselect para selecionar as medianas. 
{

	unsigned int size = 5;
	int* fim_sub = NULL; //fim de um sub-vetor
	int* mediana = NULL;
	int size_sub = 0; //tamanho de um sub-vetor
	int j = 0; //esta variável vai controlar com qual elemento do vetor a mediana de um sub-vetor vai ser trocada. 

	if (fim - v <= 5) 
	{
		struct ponteiros novos;
		int* kesimo_elemento = quickselect(v, fim, k); 
		novos.inicio_maiores = kesimo_elemento + 1;
		//cout << "v: " << *v << " kesimo elemento: " << *(kesimo_elemento) << " K: " << k << "vetor: " << endl;
		//print_vetor(v, v+(fim-v));
  		if(kesimo_elemento != NULL && kesimo_elemento != v) novos.fim_menores = kesimo_elemento - 1;
		else novos.fim_menores = NULL;
		//else novos.fim_menores = NULL; 
		return novos;
	}
	else
	{


		for (int* i = v; i < fim; i+=size)
		{
			if( (fim - i) >= size)
			{
				fim_sub = i+size;
				size_sub = size;	
			} 
			else
			{
				fim_sub = fim;
				size_sub = fim-i;	
			} 

			mediana = quickselect(i, fim_sub, floor(size_sub/2));
			int temporario = *mediana;
			*mediana = v[j];
			v[j] = temporario;
			j++;
		}

	}

	//int* medianaDasMedianas = quickselect(v, v+j, floor(j/2))
	struct ponteiros pointers = mediana_das_medianas(v, v+j, floor(j/2));
	int* medianaDasMedianas = pointers.inicio_maiores - 1;
	struct ponteiros pointers2 = particionamento_triplo(v, medianaDasMedianas, fim);
	//if (pointers2.fim_menores == NULL) pointers2.fim_menores = v;
	if (k >= indexOf(v, pointers2.fim_menores) && k <= indexOf(v, pointers2.inicio_maiores - 1)) {return pointers2;}
	else if (k < indexOf(v, pointers2.fim_menores)) {return mediana_das_medianas(v, pointers2.fim_menores + 1, k);}
	else 
	{
		pointers = mediana_das_medianas(pointers2.inicio_maiores, fim, k - indexOf(v, pointers2.inicio_maiores));
		if(pointers.fim_menores == NULL) pointers.fim_menores = pointers2.inicio_maiores - 1;
		return pointers; 
	}
}

void quicksort_mediana_medianas(int* inicio,  int* fim)
{
	while (fim-inicio > 1)
	{

		//cout << "calculando mediana de: ";
		//print_vetor(inicio, fim);
		//cout << "para valores: " << *inicio << " " << " " << *(fim-1) << " " << floor((fim-inicio)/2) << endl;
		struct ponteiros pointers = mediana_das_medianas(inicio, fim, floor( (fim-inicio)/2 ));

		//cout << "Mediana encontrada: " << *(pointers.inicio_maiores - 1) << endl;

		//cout << (pointers.fim_menores == NULL ? "nulo" : "nao-nulo") << endl;
		if(pointers.fim_menores == NULL) pointers.fim_menores = inicio;
			

		if(pointers.inicio_maiores == NULL) pointers.inicio_maiores == fim-1;
			
		size_t tamMenores = (pointers.fim_menores+1) - inicio;
		size_t tamMaiores = (fim - pointers.inicio_maiores);

		if (tamMenores < tamMaiores)
		{
			//cout << "esquerdo é menor" << tamMenores << " " << tamMaiores<<endl;
			quicksort_mediana_medianas(inicio, /*inicio,*/ pointers.fim_menores+1);
			
			if (pointers.inicio_maiores != fim-1)
			{
				inicio = pointers.inicio_maiores;
			}
			else return;
		}

		else
		{
			
			//cout << "direito é menor " << tamMenores << " " << tamMaiores << endl;
			quicksort_mediana_medianas(pointers.inicio_maiores, /*pointers.inicio_maiores,*/ fim);
			
			if (inicio != pointers.fim_menores)
			{
				fim = pointers.fim_menores + 1;
			}
			else return;
		}
	}


	
	return;
}


int* gerar_vetor(int tam, int inicio_intervalo, int fim_intervalo)
{
	int* novo_vetor = new(nothrow) int[tam];

	if(novo_vetor == nullptr)
	{
		cout << "Erro ao criar novo vetor! " << endl;

	}
	else
	{

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(inicio_intervalo, fim_intervalo);

		for(int *i = novo_vetor; i != novo_vetor + tam; i++) *i = dis(gen);

		cout << "Vetor criado!: "; 
		//print_vetor(novo_vetor, novo_vetor+tam);
	}

	return novo_vetor;
}

void copiar_vetor(int* origem, int tamanho, int* destino)
{
	for (int i = 0; i < tamanho; i++)
		destino[i] = origem[i];
}

bool vetor_ordenado(int* v, int tam)
{
	for (int* i = v; i < v+tam - 1; i++)
		if (*i > *(i+1)) return false;
	return true;
}

#endif