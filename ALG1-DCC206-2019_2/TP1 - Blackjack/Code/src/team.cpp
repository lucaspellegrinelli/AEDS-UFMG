#include "team.h"

void Team::add_member(int age){
	this->members_age.push_back(age);
}

void Team::add_relation(int from, int to){
	if(this->relations.find(from) == this->relations.end()){
		std::vector<int> r;
		this->relations.insert(std::make_pair(from, r));
	}

	this->relations[from].push_back(to);
}

void Team::remove_relation(int from, int to){
	this->relations[from].erase(std::remove(this->relations[from].begin(), this->relations[from].end(), to), this->relations[from].end());
}

bool Team::check_relation(int from, int to){
	return std::find(this->relations[from].begin(), this->relations[from].end(), to) != this->relations[from].end();
}

bool Team::has_cycle(){
	bool *stack = new bool[this->members_age.size()];
	bool *visited = new bool[this->members_age.size()];

	for(size_t i = 0; i < this->members_age.size(); i++){
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
			if(!visited[i] && this->has_cycle_util(i, visited, stack)){
				return true;
			}else if(stack[i]){
				return false;
			}
		}
	}

	stack[v] = false;
	return false;
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
	return 0;
}

void Team::meeting(){
	std::cout << "M Bla" << std::endl;
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