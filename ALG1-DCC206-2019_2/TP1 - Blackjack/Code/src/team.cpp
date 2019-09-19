#include "team.h"

Team::Team(std::vector<int> members_age, std::map<int, std::vector<int>> relations){
	this->members_age = members_age;
	this->relations = relations;
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