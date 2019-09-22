#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

#define Inf 99999999

class Team{
private:
	std::vector<int> members_age;
	std::map<int, std::vector<int>> relations;
	std::map<int, std::vector<int>> inv_relations;

public:
	Team(){ };

	void add_member(int age);
	int get_member_age(int member);

	void add_relation(int from, int to);
	void remove_relation(int from, int to);
	bool check_relation(int from, int to);

	bool swap(int a, int b);
	int commander(int a);
	std::vector<int> meeting();

	bool has_cycle();
	bool has_cycle_util(int v, bool *visited, bool *stack);

	int get_youngest_child(int v);
	int get_youngest_child_util(int v, bool *visited);

	std::vector<int> get_meeting_order();
	void get_meeting_order_util(int v, bool *visited, std::vector<int> &order);

	void print_members();
	void print_relations();
	void print_inv_relations();
};
