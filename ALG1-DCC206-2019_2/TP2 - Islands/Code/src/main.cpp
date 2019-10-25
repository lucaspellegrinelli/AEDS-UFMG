#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

std::pair<int, int> resolver_guloso(int N, std::vector<std::pair<int, int>> ilhas);
std::pair<int, int> resolver_dinamico(int N, std::vector<std::pair<int, int>> ilhas, int i);

int main(int argc, char *argv[]){
	if(argc < 2) return 0;

	// Cria o arquivo de input e o inicializa
	std::ifstream infile;
	infile.open(argv[1]);

	// Lê dinheiro disponível e quantidade de ilhas
	int N, M;
	infile >> N >> M;

	// Lê o custo e pontuaão das ilhas
	std::vector<std::pair<int, int>> ilhas;
	for(int i = 0; i < M; i++){
		int c, p;
		infile >> c >> p;
		ilhas.push_back(std::make_pair(c, p));
	}

	std::pair<int, int> sol_1 = resolver_guloso(N, ilhas);
	std::pair<int, int> sol_2 = resolver_dinamico(N, ilhas, ilhas.size());
	std::cout << sol_1.first << " " << sol_1.second << std::endl;
	std::cout << sol_2.first << " " << sol_2.second << std::endl;
}

std::pair<int, int> resolver_guloso(int N, std::vector<std::pair<int, int>> ilhas){
	// Ordena de forma decrescente em relação a (pontuacao / custo)
	std::sort(ilhas.begin(), ilhas.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b){
		return (float)a.second / a.first > (float)b.second / b.first;
	});

	int custo_atual = 0;
	int dias = 0;
	int pontuacao = 0;
	for(size_t i = 0; i < ilhas.size() && custo_atual < N; i++){
		while(custo_atual + ilhas[i].first <= N){
			custo_atual += ilhas[i].first;
			pontuacao += ilhas[i].second;
			dias++;
		}
	}

	return std::make_pair(pontuacao, dias);
}

std::pair<int, int> resolver_dinamico(int N, std::vector<std::pair<int, int>> ilhas, int i){
	// Caso base
	if(i == 0 || N == 0) return std::make_pair(0, 0);

    // Se o preço de ir para a ilha é maior que o dinheiro que temos
	if(ilhas[i - 1].first > N){
		// Ignore pois não podemos colocar essa ilha
		return resolver_dinamico(N, ilhas, i - 1);
	}else{
		// Chama para as outras ilhas diminuindo a capacidade
		std::pair<int, int> adicionar = resolver_dinamico(N - ilhas[i - 1].first, ilhas, i - 1);
		// Adiciona a pontuação e o dia a mais
		adicionar.first += ilhas[i - 1].second;
		adicionar.second++;

		// Chama paraa s outras ilhas mantendo a capacidade e não alterando a pontuação nem a quantidade de dias
		std::pair<int, int> ignorar = resolver_dinamico(N, ilhas, i - 1);

		// Vê qual das opções da uma pontuação melhor e retorne-a
		return adicionar.first > ignorar.first ? adicionar : ignorar;
	}
}
