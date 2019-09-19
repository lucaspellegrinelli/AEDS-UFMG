#include "team.h"

void Team::add_member(int age){
	this->members_age.push_back(age);
}

void Team::add_relation(int from, int to){
	if(this->relations.find(from - 1) == this->relations.end()){
		std::vector<int> r;
		this->relations.insert(std::make_pair(from - 1, r));
	}

	this->relations[from - 1].push_back(to - 1);
}

void Team::print_relations(){
	for(auto it = this->relations.begin(); it != this->relations.end(); it++){
		std::cout << "[" << it->first << "] ";
		for(size_t i = 0; i < it->second.size(); i++){
			std::cout << it->second[i] << " ";
		}
		std::cout << std::endl;
	}
}