#ifndef INSERTION_SORT
#define INSERTION_SORT

#include "sort.hpp"

/*
	A classe "InsertionSort", subclasse de "Sort", implementa o aloritmo de
	ordenação	chamado de Insertion Sort.

	Mais informações sobre o algoritmo olhando a documentação do trabalho ou
	seguindo o link https://www.geeksforgeeks.org/insertion-sort/
*/
class InsertionSort : public Sort{
public:
	/* Construtor Vazio */
	InsertionSort() : Sort(){ }

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
	void sort(long long *arr, int left, int right) override{
		for (int i = left + 1; i < right; i++){
			// Adiciona a comparação feita no "for" de cima
			this->add_comparision(1);

			// Escolhe o valor do vetor que será colocado no lugar
			long long key = arr[i];
			this->add_move(1);
			int j = i - 1;

			// Enquanto o valor estiver fora do lugar
			while (j >= left && arr[j] > key){
				// Adiciona as comparações feitas no "while" de cima
				this->add_comparision(2);

				// Desloca os valores do vetor
				arr[j + 1] = arr[j];
				// Adiciona o movimento de posições do vetor feita na linha acima
				this->add_move(1);

				j = j - 1;
			}

			// Adiciona a comparação feita logo antes do while ser quebrado
			// Será adicionada apenas uma comparação caso a primeira condição
			// do while (j >= left) falhar. Caso contrário, serão adicionadas
			// duas comparações visto que se a primeira foi verdadeira, a segunda
			// teve que ser testada
			this->add_comparision(1 + (j >= left) ? 1 : 0);

			arr[j + 1] = key;
			// Adiciona o movimento de posições do vetor feita na linha acima
			this->add_move(1);
		}

		// Adiciona a comparação feita imediatamente antes do "for" ser quebrado
		this->add_comparision(1);
	}

	/* Destrutor Vazio */
	~InsertionSort(){}
};

#endif
