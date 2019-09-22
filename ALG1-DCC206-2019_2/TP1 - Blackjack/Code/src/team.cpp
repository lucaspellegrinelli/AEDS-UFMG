#include "team.h"

void Team::add_member(int age){
	this->members_age.push_back(age);
}

int Team::get_member_age(int member){
	return this->members_age[member - 1];
}

void Team::add_relation(int from, int to){
	if(this->relations.find(from) == this->relations.end()){
		std::vector<int> r;
		this->relations.insert(std::make_pair(from, r));
		this->inv_relations.insert(std::make_pair(to, r));
	}

	this->relations[from].push_back(to);
	this->inv_relations[to].push_back(from);
}

void Team::remove_relation(int from, int to){
	this->relations[from].erase(std::remove(this->relations[from].begin(), this->relations[from].end(), to), this->relations[from].end());
	this->inv_relations[to].erase(std::remove(this->inv_relations[to].begin(), this->inv_relations[to].end(), from), this->inv_relations[to].end());
}

bool Team::check_relation(int from, int to){
	return std::find(this->relations[from].begin(), this->relations[from].end(), to) != this->relations[from].end();
}

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

int Team::get_youngest_child(int v){
	bool *visited = new bool[this->members_age.size() + 1];
	for(size_t i = 0; i <= this->members_age.size(); i++, visited[i] = false);
	return this->get_youngest_child_util(v, visited);
}

int Team::get_youngest_child_util(int v, bool *visited){
	if(!visited[v]){
		visited[v] = true;

		int youngest_age = Inf;
		for(int i : this->inv_relations[v]){
			if(!visited[i]){
				youngest_age = std::min(youngest_age, this->get_member_age(i));
				youngest_age = std::min(youngest_age, this->get_youngest_child_util(i, visited));
			}
		}

		return youngest_age;
	}

	return Inf;
}

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

void Team::get_meeting_order_util(int v, bool *visited, std::vector<int> &order){
	visited[v] = true;
	for(int i : this->relations[v]){
		if(!visited[i]){
			get_meeting_order_util(i, visited, order);
		}
	}

	order.push_back(v);
}

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

int Team::commander(int a){
	return this->get_youngest_child(a);
}

std::vector<int> Team::meeting(){
	return this->get_meeting_order();
}

void Team::print_members(){
	for(int i : this->members_age){
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

void Team::print_relations(){
	for(auto it = this->relations.begin(); it != this->relations.end(); it++){
		std::cout << "[" << it->first << "] ";
		for(int i : it->second){
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
}

void Team::print_inv_relations(){
	for(auto it = this->inv_relations.begin(); it != this->inv_relations.end(); it++){
		std::cout << "[" << it->first << "] ";
		for(int i : it->second){
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
}
