#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

class Team{
private:
	std::vector<int> members_age;
	std::map<int, std::vector<int>> relations;

public:
	Team(){ };

	void add_member(int age);

	void add_relation(int from, int to);
	void remove_relation(int from, int to);
	bool check_relation(int from, int to);

	bool swap(int a, int b);
	int commander(int a);
	void meeting();

	bool has_cycle();
	bool has_cycle_util(int v, bool *visited, bool *stack);

	void print_members();
	void print_relations();
};