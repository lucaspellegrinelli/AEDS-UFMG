#ifndef QUICKSORT
#define QUICKSORT

#include "sort.hpp"
#include "insertion_sort.hpp"

#include <iostream>
#include <string>

/*
	Definição de um atalho para a criação de variáveis do tipo
		int* (*var)(long long*, int, int)

	Que representam uma função que retorna um int* e tem como parâmetros
	long long*, int e int.
	Essa função será de uso comum visto que é ela é utilizada como função
	de partição, definindo onde o pivo vai estar inicialmente.
*/
#define Partition(name) int* (*name)(long long*, int, int)

/*
A classe "Quicksort", subclasse de "Sort", implementa o aloritmo de
ordenação	chamado de Quick Sort.

Mais informações sobre o algoritmo olhando a documentação do trabalho ou
seguindo o link https://www.geeksforgeeks.org/quick-sort/
*/
class Quicksort : public Sort{
public:

	/*
		Construtor vazio -
			- Deixa o tipo de partição como o pivo no elemento do meio
			- Recursivo
			- Sem mudar para o inserção em tamanhos pequenos
	*/
	Quicksort() : Sort(){
		this->partition = Quicksort::MIDDLE_ELEMENT_PARTITION;
		this->iterative = false;
		this->change_sort_perc = 0.0;
		this->change_sort_limit = 0;
	}

	/*
		Construtor
			- Partition(partition)
				- Recebe qual será a função que irá definir a posição inicial do pivo
					durante a partição

			- double change_sort_perc
				- Qual a porcentagem do tamanho original os tamanhos dos subvetores
					criados durante	a ordenação precisam ter para que o método de ordenação
					seja alterado para o Inserção.

			- bool iterative
				- Define se o algoritmo do Quick Sort a ser utilizado será iterativo
					ou recursivo.
	*/
	Quicksort(Partition(partition), double change_sort_perc, bool iterative) : Sort(){
		this->partition = partition;
		this->iterative = iterative;
		this->change_sort_perc = change_sort_perc;
		this->change_sort_limit = 0;
	}

	/*
		- O método "sort" a seguir é uma sobreposição do método "sort" abstrato
		encontrado na definição da superclasse "Sort". É esse o método que será
		chamado por códigos exteriores para ordenar o vetor desejado.

		ENTRADAS:
			- long long*arr
				- Vetor de entrada, onde cada um dos itens é do tipo long long.
			- int left
				- Posição do limite esquerdo do vetor
			- int right
				- Posição do limite direito do vetor

		SAIDAS:
			- void
				- Nada é retornado pela função visto que o ordenamento acontece
				in-place no vetor de entrada.
	*/
	void sort(long long *arr, int left, int right) override {
		// Atualiza qual é o limite de tamanho entre o uso do Quick Sort e o
		// Insertion Sort
		this->change_sort_limit = (right - left + 1) * change_sort_perc;

		// Chama a versão correta do algoritmo dependendo do que foi passado para o construtor
		if(this->iterative){
			iterative_sort(arr, left, right);
		}else {
			recursive_sort(arr, left, right);
		}

		this->change_sort_limit = 0;
	}

	/* -------------------- PARTITIONS -------------------- */

	/*
		Definição as das funções de escolha do pivo. É estático pois a função não
		depende dos valores perticulares de cada objeto e devem ser passados
		para o construtor.

		Todas as funções a seguir seguem a forma:

		ENTRADAS:
		- long long*arr
			- Vetor de entrada, onde cada um dos itens é do tipo long long.
		- int left
			- Posição do limite esquerdo do vetor
		- int right
			- Posição do limite direito do vetor

		SAIDAS:
			- int[2]
				- [0] - Quantas comparações foram utilizadas para chegar no resultado
				- [1] - A posição do pivo
	*/

	/*
		Escolha do pivo pelo primeiro elemento. Apenas retorna o limite esquerdo
		do vetor. Não faz comparações.
	*/
	static int* FIRST_ELEMENT_PARTITION(long long *arr, int left, int right){
		return new int[2]{0, left};
	};

	/*
		Escolha do pivo pelo elemento do meio. Retorna a média entre os limites
		esquerdo e direito do vetor. Não faz comparações.
	*/
	static int* MIDDLE_ELEMENT_PARTITION(long long *arr, int left, int right){
		return new int[2]{0, (left + right) / 2};
	};

	/*
		Escolha do pivo pela mediana entre as valores o primeiro, o último e o
		elemento do meio do vetor. Faz entre 2 a 3 comparações, dependendo do
		caso em que cair.
	*/
	static int* MEDIAN_OF_3_PARTITION(long long *arr, int left, int right){
		int a_index = left;
		int b_index = (left + right) / 2;
		int c_index = right;

		long long a = arr[a_index];
		long long b = arr[b_index];
		long long c = arr[c_index];

		if(a > b){
			if(b > c) return new int[2]{2, b_index}; // a > b > c
			else if(a > c) return new int[2]{3, c_index}; // a > c > b
			else return new int[2]{3, a_index}; // c > a > b
		}else {
			if(a > c)	return new int[2]{2, a_index}; // b > a > c
			else if(b > c) return new int[2]{3, c_index}; // b > c > a
			else return new int[2]{3, b_index}; // c > b > a
		}
	};

private:
	/* Variáveis locais da classe */
	Partition(partition);
	bool iterative;
	double change_sort_perc;
	int change_sort_limit;

	/*
		Definição da versão recursiva do Quicksort

		Para cada chamada, o vetor é dividido em dois a partir do valor de
		um elemento chamado pivo, que dependendo da variação do quicksort utilizado
		é escolhido diferente. Assim, é possível chamar denovo esse método para
		cada uma das metades.
	*/
	void recursive_sort(long long *arr, int left, int right){
		this->add_comparision(1); // Adiciona a comparação do "if" da linha abaixo
		if((right - left + 1) <= this->change_sort_limit){
			// Cria o objeto do inserção
			InsertionSort insertion = InsertionSort();
			// Ordena o vetor por meio da inserção
			insertion.sort(arr, left, right);

			// Adicionando as comparações/movimentos feitas no inserção
			this->add_comparision(insertion.get_comparation_count());
			this->add_move(insertion.get_move_count());
		}else{
			// Particiona o vetor
			int *p = partitionate_array(arr, left, right);

			// Chama recursivamente esse mesmo método
			if(p[1] > left) recursive_sort(arr, left, p[1]);
			if(p[0] < right) recursive_sort(arr, p[0], right);

			// Adiciona as comparações dos dois "if" de cima
			this->add_comparision(2);
		}
	}

	/*
		Definição da versão iterativa do Quicksort

		A ideia fundalmentalmente é a mesma da versão recursiva, porém precisamos
		recriar o stack que o computador cria ao fazer as chamadas recursives. Para
		isso criamos uma estrutura de pilha. A estrutura criada nessa implementação
		é a versão otimizada da com duas pilhas, uma para cada lado do vetor. Nesse
		caso, guardamos também os valores para cada lado porém intercalando-os
		entre as posições de índice ímpar e par da pilha.
	*/
	void iterative_sort(long long *arr, int left, int right){
		// Criação da pilha de execução
		int stack[right - left + 1];
		int top = -1;

		// Adiciona o primeiro valor na pilha que é de fato a chamada inicial
		stack[++top] = left;
		stack[++top] = right;

		// Enquanto a pilha tiver elementos
		while(top >= 0){
			// Adiciona a comparação feita no while
			this->add_comparision(1);

			// Resgata e retira os dados da chamada do topo
			right = stack[top--];
			left = stack[top--];

			// Particiona o vetor e achar o pivo
			int *p = partitionate_array(arr, left, right);

			// Caso a "direita atual" estiver nos limites da esquerda, adiciona
			// essa chamada a pilha
			if (p[1] > left) {
				stack[++top] = left;
				stack[++top] = p[1];
			}
			// Adiciona a comparação do "if" de cima
			this->add_comparision(1);

			// Caso a "esquerda atual" estiver nos limites da direita adiciona
			// essa chamada a pilha
			if (p[0] < right) {
				stack[++top] = p[0];
				stack[++top] = right;
			}
			// Adiciona a comparação do "if" de cima
			this->add_comparision(1);
		}

		// Adiciona a comparação feita imediatamente antes do break do "while"
		this->add_comparision(1);
	}

	/*
		Função de partição do vetor

		O objetivo dessa função é definir um pivo (um dos elementos do vetor
		escolhido de forma oportuna) e reorganizar o vetor de forma que todos os
		elementos menores que o pivo estarão em índices menores que o dele e todos
		os elementos maiores que o pivo estarão em índices maiores que o dele.

		A função retorna a posição do primeiro elemento diferente do pivo acima
		do pivo e a posição do primeiro elemento diferente do pivo abaixo do pivo.
	*/
	int* partitionate_array(long long *arr, int left, int right){
		// Chama a função de escolher o pivo
		int *p = this->partition(arr, left, right);

		// Adiciona o número de comparações necessárias para escolher o pivo
		this->add_comparision(p[0]);

		// Encontra o valor do pivo (visto que a função retornou a posição do pivo)
    long long pivot = arr[p[1]];

		// Define os limites "atuais" da reorganização
		int i = left;
		int j = right;

		// Enquanto existem elementos não checados
		while(i <= j){
			// Se o elemento de índice menor que o pivo é de fato menor que o pivo,
			// nada precisa ser feito. Caso contrário, saia do while com o "i" na
			// posição desse elemento.
			while(arr[i] < pivot){
				i++;

				// Adiciona a comparação feita pelo while
				this->add_comparision(1);
			}
			// Adiciona a comparação feita imediatamente antes do break do "while"
			this->add_comparision(1);

			// Se o elemento de índice maior que o pivo é de fato maior que o pivo,
			// nada precisa ser feito. Caso contrário, saia do while com o "j" na
			// posição desse elemento.
			while(arr[j] > pivot){
				j--;

				// Adiciona a comparação feita pelo while
				this->add_comparision(1);
			}
			// Adiciona a comparação feita imediatamente antes do break do "while"
			this->add_comparision(1);

			// Nesse ponto do algoritmo, temos o "i" na posição de um elemento que é
			// maior que o pivo mas está com o índice menor e temos o "j" na posição
			// de um elemento que é menor que o pivo mas está com o índice maior.
			// Logo temos que substitui-los para consertar a ordem esperada.
			if(i <= j) swap(arr[i++], arr[j--]);

			// Adiciona as comparações feitas pelo "if" acima e pelo "while"
			this->add_comparision(2);
		}

		// Adiciona a comparação feita imediatamente antes do break do "while"
		this->add_comparision(1);

		return new int[2]{i, j};
	}

	/*
		Função de troca de chaves

		Essa função é responsável por trocar os valores de duas posições de memória.
		É geralmente utilizada no contexto desse algoritmo para trocar posições de
		um vetor.
	*/
	void swap(long long& a, long long &b){
		long long t = a;
		a = b;
		b = t;

		// Adiciona o número de mudanças de posição feitas.
		this->add_move(1);
	}
};

#endif
