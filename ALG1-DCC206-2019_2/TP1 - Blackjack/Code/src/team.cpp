#include "team.h"

// Adiciona um novo membro com uma idade especificada
void Team::add_member(int age){
	this->members_age.push_back(age);
}

// Retorna a idade do membro de índice especificado
int Team::get_member_age(int member){
	return this->members_age[member - 1];
}

// Adiciona no mapa de relação uma nova relação entre dois membros identificados
// pelo seus índices
void Team::add_relation(int from, int to){
	if(this->relations.find(from) == this->relations.end()){
		std::vector<int> r;
		this->relations.insert(std::make_pair(from, r));
		this->inv_relations.insert(std::make_pair(to, r));
	}

	this->relations[from].push_back(to);
	this->inv_relations[to].push_back(from);
}

// Remove a relação entre dois membros do mapa de relações
void Team::remove_relation(int from, int to){
	this->relations[from].erase(std::remove(this->relations[from].begin(), this->relations[from].end(), to), this->relations[from].end());
	this->inv_relations[to].erase(std::remove(this->inv_relations[to].begin(), this->inv_relations[to].end(), from), this->inv_relations[to].end());
}

// Testa se existe uma relaçao entre dois membros (direçao importa)
bool Team::check_relation(int from, int to){
	return std::find(this->relations[from].begin(), this->relations[from].end(), to) != this->relations[from].end();
}

// Método geral que testa se o grafo tem ou não ciclos. Chama o método de DFS
// "has_cycle_util"
bool Team::has_cycle(){
	bool *stack = new bool[this->members_age.size() + 1];
	bool *visited = new bool[this->members_age.size() + 1];
	for(size_t i = 0; i <= this->members_age.size(); i++, stack[i] = false, visited[i] = false);

	for(size_t i = 1; i <= this->members_age.size(); i++){
		if(this->has_cycle_util(i, visited, stack)){
			return true;
		}
	}

	return false;
}

// Método que testa se existe um ciclo no grafo utilizando do algoritmo de
// DFS
bool Team::has_cycle_util(int v, bool *visited, bool *stack){
	if(!visited[v]){
		stack[v] = true;
		visited[v] = true;

		for(int i : this->relations[v]){
			if((!visited[i] && this->has_cycle_util(i, visited, stack)) || stack[i]){
				return true;
			}
		}
	}

	stack[v] = false;
	return false;
}

// Método geral que retorna qual o vértice "pai" de um vértice específico
// tem menor idade chamando o DFS do método "get_youngest_child_util"
int Team::get_youngest_child(int v){
	bool *visited = new bool[this->members_age.size() + 1];
	for(size_t i = 0; i <= this->members_age.size(); i++, visited[i] = false);
	return this->get_youngest_child_util(v, visited);
}

// Método que retorna o vértice pai que corresponde ao membro de menor idade
// que comanda o vértice atual utilizando o algoritmo do DFS
int Team::get_youngest_child_util(int v, bool *visited){
	if(!visited[v]){
		visited[v] = true;

		int youngest_age = Inf;
		for(int i : this->inv_relations[v]){
			if(!visited[i]){
				// Testa se a menor idade atual é maior que a idade do vértice atual e
				// de seus filhos (que no grafo nao invertido são os seus pais)
				youngest_age = std::min(youngest_age, this->get_member_age(i));
				youngest_age = std::min(youngest_age, this->get_youngest_child_util(i, visited));
			}
		}

		return youngest_age;
	}

	return Inf;
}

// Método geral que retorna uma ordem de fala dos membros da equipe chamando
// o método de ordenação topológica "get_meeting_order_util"
std::vector<int> Team::get_meeting_order(){
	bool *visited = new bool[this->members_age.size() + 1];
	for(size_t i = 0; i <= this->members_age.size(); i++, visited[i] = false);
	std::vector<int> order;

	for(size_t i = 1; i <= this->members_age.size(); i++){
		if(!visited[i]){
			get_meeting_order_util(i, visited, order);
		}
	}

	return order;
}

// Modifica o vetor "order" para que ele contenha uma ordenação topológica do
// grafo atual por meio do algoritmo de DFS.
void Team::get_meeting_order_util(int v, bool *visited, std::vector<int> &order){
	visited[v] = true;
	for(int i : this->relations[v]){
		if(!visited[i]){
			get_meeting_order_util(i, visited, order);
		}
	}

	order.insert(order.begin(), v);
}

// Função de SWAP: Modifica a orientaçao de uma aresta entre dois vértices,
// caso isso resulte em um ciclo, retorne falso e reverta a modificação feita.
//Caso contrário retorne verdadeiro
bool Team::swap(int a, int b){
	if(this->check_relation(a, b)){
		this->remove_relation(a, b);
		this->add_relation(b, a);

		if(this->has_cycle()){
			this->remove_relation(b, a);
			this->add_relation(a, b);
			return false;
		}
	}else if(this->check_relation(b, a)){
		this->remove_relation(b, a);
		this->add_relation(a, b);

		if(this->has_cycle()){
			this->remove_relation(a, b);
			this->add_relation(b, a);
			return false;
		}
	}else{
		return false;
	}

	return true;
}

// Função COMMANDER: Retorna o resultado do DFS que acha o vértice pai que tem
// a menor idade
int Team::commander(int a){
	return this->get_youngest_child(a);
}

// Função MEETING: Retorna uma das possíveis ordenações topológicas do grafo
// que corresponde a uma ordem de fala dos membros
std::vector<int> Team::meeting(){
	return this->get_meeting_order();
}
