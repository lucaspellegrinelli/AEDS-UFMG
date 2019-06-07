#ifndef SORT
#define SORT

#include <string>

/*
	A classe "Sort" é uma classe que define um método de ordenamento genérico
	que funcione para variáveis do tipo long long. A classe também é responsável
	por definir a contagem de comparações e movimentações de chaves.
*/
class Sort{
public:
	/*
		Construtor vazio que inicializa os contadores de comparações e movimentações
		de chave como 0.
	*/
	Sort(){
		this->comparasion_count = 0;
		this->move_count = 0;
	}

	/*
		- O método "sort" a seguir é um método abstrato (ou seja, suas subclasses
		que farão a definição de como ordenar os vetores) que será chamado por códigos
		exteriores para ordenar o vetor desejado.

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
	virtual void sort(long long *arr, int left, int right) = 0;

	/*
		Retorna o número atual de comparações feitas pelo algoritmo
	*/
	int get_comparation_count(){
		return this->comparasion_count;
	}

	/*
		Retorna o número atual de movimentações feitas pelo algoritmo
	*/
	int get_move_count(){
		return this->move_count;
	}

	/*
		Reseta o número atual de comparações feitas pelo algoritmo
	*/
	void reset_comparasion_count(){
		this->comparasion_count = 0;
	}

	/*
		Reseta o número atual de movimentações feitas pelo algoritmo
	*/
	void reset_move_count(){
		this->move_count = 0;
	}

	/* Destrutor vazio */
	virtual ~Sort(){}
private:
	int comparasion_count;
	int move_count;
	int operation_cost;

protected:
	/*
		Método que será utilizado pelas classes filhas para contabilizar o número
		de comparações feitas
	*/
	void add_comparision(int how_much){
		this->comparasion_count += how_much;
	}

	/*
		Método que será utilizado pelas classes filhas para contabilizar o número
		de movimentações feitas
	*/
	void add_move(int how_much){
		this->move_count += how_much;
	}
};

#endif
