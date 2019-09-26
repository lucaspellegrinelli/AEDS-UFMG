#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

#define Inf 99999999

class Team{
private:
	// Guarda a idade de cada um dos membros por índice
	std::vector<int> members_age;

	// Guarda a lista de adjacencias de cada membro
	std::map<int, std::vector<int>> relations;

	// Guarda a lista de adjacencias invertida de cada membro
	std::map<int, std::vector<int>> inv_relations;

public:
	Team(){ };

	// Adiciona um novo membro com uma idade especificada
	void add_member(int age);

	// Retorna a idade do membro de índice especificado
	int get_member_age(int member);


	// Adiciona no mapa de relação uma nova relação entre dois membros identificados
	// pelo seus índices
	void add_relation(int from, int to);

	// Remove a relação entre dois membros do mapa de relações
	void remove_relation(int from, int to);

	// Testa se existe uma relaçao entre dois membros (direçao importa)
	bool check_relation(int from, int to);


	// Método geral que testa se o grafo tem ou não ciclos. Chama o método de DFS
	// "has_cycle_util"
	bool has_cycle();

	// Método que testa se existe um ciclo no grafo utilizando do algoritmo de
	// DFS
	bool has_cycle_util(int v, bool *visited, bool *stack);


	// Método geral que retorna qual o vértice "pai" de um vértice específico
	// tem menor idade chamando o DFS do método "get_youngest_child_util"
	int get_youngest_child(int v);

	// Método que retorna o vértice pai que corresponde ao membro de menor idade
	// que comanda o vértice atual utilizando o algoritmo do DFS
	int get_youngest_child_util(int v, bool *visited);


	// Método geral que retorna uma ordem de fala dos membros da equipe chamando
	// o método de ordenação topológica "get_meeting_order_util"
	std::vector<int> get_meeting_order();

	// Modifica o vetor "order" para que ele contenha uma ordenação topológica do
	// grafo atual por meio do algoritmo de DFS.
	void get_meeting_order_util(int v, bool *visited, std::vector<int> &order);


	// Função de SWAP: Modifica a orientaçao de uma aresta entre dois vértices,
	// caso isso resulte em um ciclo, retorne falso e reverta a modificação feita.
	//Caso contrário retorne verdadeiro
	bool swap(int a, int b);

	// Função COMMANDER: Retorna o resultado do DFS que acha o vértice pai que tem
	// a menor idade
	int commander(int a);

	// Função MEETING: Retorna uma das possíveis ordenações topológicas do grafo
	// que corresponde a uma ordem de fala dos membros
	std::vector<int> meeting();
};
