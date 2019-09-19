#include <iostream>
#include <vector>
#include <map>

#include "team.h"

int main(){
	int n, m, i;
	std::cin >> n >> m >> i;

	Team t;

	for(int i = 0; i < n; i++){
		int age;
		std::cin >> age;
		t.add_member(age);
	}

	for(int i = 0; i < m; i++){
		int from, to;
		std::cin >> from >> to;
		t.add_relation(from, to);
	}

	t.print_relations();
}