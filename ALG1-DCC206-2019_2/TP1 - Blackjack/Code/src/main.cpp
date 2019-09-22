#include <iostream>
#include <vector>
#include <map>

#include "team.h"

int main(){
	int N, M, I;
	std::cin >> N >> M >> I;

	Team t;

	for(int i = 0; i < N; i++){
		int age;
		std::cin >> age;
		t.add_member(age);
	}

	for(int i = 0; i < M; i++){
		int from, to;
		std::cin >> from >> to;
		t.add_relation(from, to);
	}

	for(int i = 0; i < I; i++){
		char instr;
		std::cin >> instr;
		if(instr == 'S'){
			int a, b;
			std::cin >> a >> b;
			bool swap_ok = t.swap(a, b);

			if(swap_ok){
				std::cout << "S T" << std::endl;
			}else{
				std::cout << "S N" << std::endl;
			}
		}else if(instr == 'C'){
			int a;
			std::cin >> a;
			int comm = t.commander(a);
			std::cout << "C " << (comm == Inf ? "*" : std::to_string(comm)) << std::endl;
		}else{
			std::vector<int> order = t.meeting();
			std::cout << "M ";
			for(int i : order){
				std::cout << i << " ";
			}
			std::cout << std::endl;
		}
	}
}
