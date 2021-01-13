#ifndef SORT_REQUEST
#define SORT_REQUEST

#include "quick_sort.hpp"

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <string>

// 1 unidade a menos que o maior valor gerado pela função rand()
#define MAX_RAND_N 9223372036854775806

// Número de testes que serão feitos para cada tipo de teste para evitar
// resultados fora do padrão.
#define NUMBER_OF_TESTS 20

/*
	A classe SortRequest tem como objetivo executar os testes requeridos pela
	descrição do objeto para uma combinação de parâmetros. Funciona basicamente
	como uma "central" de execução de testes, instanciando uma classe Quicksort
	e medindo os resultados.
*/
class SortRequest{
public:

	/*
		Construtor - Recebe os possíveis parâmetros que o programa pode receber:
			- std::string variation
				- Variação do Quicksort utilizado: QC, QM3, QPE, QI1, QI5, QI10 e QNR
			std::string arr_type
				- Tipos dos vetores: Ale, OrdC e OrdD
			std::string arr_size
				- Tamanho dos vetores a serem gerados.
			bool print_arr
				- Se é ou não para imprimir os vetores utilizados para os testes
	*/
	SortRequest(std::string variation, std::string arr_type, std::string arr_size, bool print_arr){
		this->variation = variation;
		this->arr_type = arr_type;
		this->arr_size = std::stoi(arr_size);
		this->print_arr = print_arr;
	}

	/*
		Método que controla os testes em sí.

		Aqui é criado a instância da classe "Quicksort" respeitando os parâmetros
		passados para o construtor. Assim é possível gerar os vetores, ordena-los
		e guardar os valores de comparações, movimentações e tempo de execução
		para então calcular a média/mediana e mostrar na saída padrão.
	*/
	void run(){
		Quicksort *qs = new Quicksort();

		// Para cada tipo de variação de Quicksort, crie a instância adequada.
		if(this->variation == "QC"){
			qs = new Quicksort(Quicksort::MIDDLE_ELEMENT_PARTITION, 0.0, false);
		}else if(this->variation == "QM3"){
			qs = new Quicksort(Quicksort::MEDIAN_OF_3_PARTITION, 0.0, false);
		}else if(this->variation == "QPE"){
			qs = new Quicksort(Quicksort::FIRST_ELEMENT_PARTITION, 0.0, false);
		}else if(this->variation == "QI1"){
			qs = new Quicksort(Quicksort::MEDIAN_OF_3_PARTITION, 0.01, false);
		}else if(this->variation == "QI5"){
			qs = new Quicksort(Quicksort::MEDIAN_OF_3_PARTITION, 0.05, false);
		}else if(this->variation == "QI10"){
			qs = new Quicksort(Quicksort::MEDIAN_OF_3_PARTITION, 0.1, false);
		}else if(this->variation == "QNR"){
			qs = new Quicksort(Quicksort::MIDDLE_ELEMENT_PARTITION, 0.0, true);
		}

		// Criação dos vetores/matrizes que armazenarão as métricas das ordenações
		long long **arrs = new long long*[NUMBER_OF_TESTS];
		long long *comparisions = new long long[NUMBER_OF_TESTS];
		long long *moves = new long long[NUMBER_OF_TESTS];
		long long *times = new long long[NUMBER_OF_TESTS];

		// Repetindo a ordenação "NUMBER_OF_TESTS" vezes
		for(int i = 0; i < NUMBER_OF_TESTS; i++){
			// Reseta os contadores
			qs->reset_comparasion_count();
			qs->reset_move_count();

			// Gera o vetor do tipo determinado
			arrs[i] = generate_array(this->arr_type, this->arr_size);
			long long *arr_copy = copy_array(arrs[i], this->arr_size);

			// Ordena o vetor e armazene o tempo que gastou
			times[i] = time_sort(qs, arr_copy, this->arr_size);

			// Armazene o número de comparações e o número de movimentações
			comparisions[i] = qs->get_comparation_count();
			moves[i] = qs->get_move_count();
		}

		// Calculos das médias e medianas das métricas determinadas
		long long avg_comp = get_average(comparisions, NUMBER_OF_TESTS);
		long long avg_moves = get_average(moves, NUMBER_OF_TESTS);
		long long med_times = get_median(times, NUMBER_OF_TESTS);

		// Escreve na saída padrão as estatisticas gerais do desempenho
		output_sort_info(avg_comp, avg_moves, med_times);

		// Caso seja desejado pelo usuário, escreva também os vetores utilizados
		// para os testes
		if(this->print_arr){
			for(int i = 0; i < NUMBER_OF_TESTS; i++){
				output_array(arrs[i], this->arr_size);
			}
		}
	}
private:
	std::string variation;
	std::string arr_type;
	int arr_size;
	bool print_arr;

	/*
		Método responsável por achar a média dos valores de um vetor de long long.
		Observação: Resultado truncado
	*/
	long long get_average(long long *arr, int size){
		long long sum = 0;
		for(int i = 0; i < size; i++){
			sum += arr[i];
		}

		return sum / size;
	}

	/*
		Método responsável por achar a mediana dos valores de um vetor de long long.
		Observação: Resultado truncado
	*/
	long long get_median(long long *arr, int size){
		Quicksort *qs = new Quicksort();
		qs->sort(arr, 0, size - 1);

		if(size % 2 == 0){
			return (arr[size / 2] + arr[size / 2 - 1]) / 2;
		}else{
			return arr[size / 2];
		}
	}

	/*
		Método responsável por executar o ordenamento e calcular o tempo que foi
		gasto por essa ordenação (que é o valor retornado).
	*/
	long long time_sort(Quicksort *qs, long long *arr, int size){
		// Acha o tempo inicial
		auto begin = std::chrono::high_resolution_clock::now();

		// Ordena o vetor
		qs->sort(arr, 0, size - 1);

		// Acha o tempo final
		auto end = std::chrono::high_resolution_clock::now();

		// Acha a diferença entre o tempo inicial e final
		auto dur = end - begin;
		auto dur_in_ms = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
		return dur_in_ms;
	}

	/*
		Método respnsável por criar uma cópia de um vetor visto que uma simples
		atribuição copiaria a posição de memória do vetor e ao modificar o segundo
		vetor, o primeiro também seria alterado.
	*/
	long long * copy_array(long long *arr, int size){
		long long *new_arr = new long long[size];
		for(int i = 0; i < size; i++){
			new_arr[i] = arr[i];
		}
		return new_arr;
	}

	/*
		Método responsável por gerar o vetor dependendo do tipo de vetor especificado
		pelo parâmetro "std::string type".

		Os tipos aceitos são:
			- "Ale" - Aleatório
			- "OrdC" - Ordenado Crescente
			- "OrdD" - Ordenado Decrescente
	*/
	long long * generate_array(std::string type, int size){
		long long *arr = new long long[size];
		for(int i = 0; i < size; i++){
			if(type == "Ale") arr[i] = rand() % MAX_RAND_N;
			else if(type == "OrdC") arr[i] = i;
			else if(type == "OrdD") arr[i] = MAX_RAND_N - i;
		}

		return arr;
	}

	/*
		Método responsável por imprimir na saída padrão as estatisticas gerais
		de um teste de ordenamento.
	*/
	void output_sort_info(long long comparisions, long long moves, long long time){
		std::cout << this->variation << " " <<
								 this->arr_type << " " <<
								 this->arr_size << " " <<
								 comparisions << " " <<
								 moves << " " <<
								 time << std::endl;
	}

	/*
		Método responsável por imprimir na saída padrão um vetor de long long
	*/
	void output_array(long long *arr, int size){
		for(int i = 0; i < size; i++){
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}
};

#endif
