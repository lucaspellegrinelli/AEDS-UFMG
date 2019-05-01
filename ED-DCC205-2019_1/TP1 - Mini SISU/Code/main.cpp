#include <iostream>
#include "list.hpp"
#include "pair.hpp"
#include "student.hpp"

using namespace std;

int main(){
  int qtd_cursos;
  int qtd_alunos;

  cin >> qtd_cursos >> qtd_alunos;

  List<Pair<string, int>> cursos;
  for(int i = 0; i < qtd_cursos; i++){
    string nome_curso;
    int vagas_curso;
    while(std::getline(std::cin, nome_curso)) if(nome_curso.size() > 0) break;
    cin >> vagas_curso;
    cursos.insert_end(Pair<string, int>(nome_curso, vagas_curso));
  }

  List<Student> alunos;
  for(int i = 0; i < qtd_alunos; i++){
    string nome_aluno;
    float nota_aluno;
    int primeira_opcao;
    int segunda_opcao;
    while(std::getline(std::cin, nome_aluno)) if(nome_aluno.size() > 0) break;
    cin >> nota_aluno >> primeira_opcao >> segunda_opcao;
    alunos.insert_end(Student(nome_aluno, nota_aluno, primeira_opcao, segunda_opcao));
  }

  
}
