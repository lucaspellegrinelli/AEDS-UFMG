#include <iostream>
#include <vector>
#include <map>

#include "team.h"

int main(){
	int n, m, i;
	std::cin >> n >> m >> i;

	std::vector<int> ages;
	for(int i = 0; i < n; i++){
		int age;
		std::cin >> age;
		ages.push_back(age);
	}

	std::map<int, std::vector<int>> relations;
	for(int i = 0; i < m; i++){
		int from, to;
		std::cin >> from >> to;
		if(relations.find(from - 1) == relations.end()){
			std::vector<int> r;
			relations.insert(std::make_pair(from - 1, r));
		}

		relations[from - 1].push_back(to - 1);
	}

	Team t(ages, relations);
	t.print_relations();
}