#include <vector>
#include <map>
#include <iostream>

class Team{
private:
	std::vector<int> members_age;
	std::map<int, std::vector<int>> relations;

public:
	Team(){ };
	Team(std::vector<int> members_age, std::map<int, std::vector<int>> relations);

	void print_members();
	void print_relations();
};