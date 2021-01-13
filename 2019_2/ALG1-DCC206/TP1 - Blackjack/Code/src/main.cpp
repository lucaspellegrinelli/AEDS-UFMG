#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "team.h"

int main(int argc, char *argv[]){
	if(argc < 2) return 0;

	// Cria o arquivo de input e o inicializa
	std::ifstream infile;
	infile.open(argv[1]);

	int N, M, I;
	infile >> N >> M >> I;

	// Cria o objeto de um time
	Team t;

	// Le as idades dos membros da equipe
	for(int i = 0; i < N; i++){
		int age;
		infile >> age;
		t.add_member(age);
	}

	// Le as relações entre os membros da equipe
	for(int i = 0; i < M; i++){
		int from, to;
		infile >> from >> to;
		t.add_relation(from, to);
	}

	// Le e executa as ações especificas do problema
	for(int i = 0; i < I; i++){
		char instr;
		infile >> instr;

		if(instr == 'S'){
			// Caso seja um instrução de SWAP
			int a, b;
			infile >> a >> b;
			bool swap_ok = t.swap(a, b);

			if(swap_ok){
				std::cout << "S T" << std::endl;
			}else{
				std::cout << "S N" << std::endl;
			}
		}else if(instr == 'C'){
			// Caso seja uma instrução de COMMANDER
			int a;
			infile >> a;
			int comm = t.commander(a);
			std::cout << "C " << (comm == Inf ? "*" : std::to_string(comm)) << std::endl;
		}else{
			// Caso seja uma instrução de MEETIING
			std::vector<int> order = t.meeting();
			std::cout << "M ";
			for(int i : order){
				std::cout << i << " ";
			}
			std::cout << std::endl;
		}
	}
}
