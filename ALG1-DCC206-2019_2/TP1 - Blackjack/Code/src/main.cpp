#include <iostream>
#include <utility>

int main(){
	int n, m, i;
	std::cin >> n >> m >> i;

	int ages[n];
	for(int i = 0; i < n; i++){
		std::cin >> ages[i];
	}

	std::pair<int, int> relations[m];
	for(int i = 0; i < m; i++){
		std::cin >> relations[i].first >> relations[i].second;
	}

	
}