#include <iostream>
#include <iomanip>
#include <fstream>
#include "list.hpp"
#include "pair.hpp"
#include "student.hpp"

using namespace std;

int main(int argc, char *argv[]){
  int qtd_cursos;
  int qtd_alunos;

  cin >> qtd_cursos >> qtd_alunos;

  Pair<string, int> cursos[qtd_cursos];
  for(int i = 0; i < qtd_cursos; i++){
    string nome_curso;
    int vagas_curso;
    while(std::getline(std::cin, nome_curso)) if(nome_curso.size() > 0) break;
    cin >> vagas_curso;
    cursos[i] = Pair<string, int>(nome_curso, vagas_curso);
  }

  List<Student> alunos;
  for(int i = 0; i < qtd_alunos; i++){
    string nome_aluno;
    float nota_aluno;
    int primeira_opcao;
    int segunda_opcao;
    while(std::getline(std::cin, nome_aluno)) if(nome_aluno.size() > 0) break;
    cin >> nota_aluno >> primeira_opcao >> segunda_opcao;
    alunos.insert_ordered(Student(i, nome_aluno, nota_aluno, primeira_opcao, segunda_opcao));
  }

  List<Student> concorrencia_cursos[qtd_cursos];
  for(int i = 0; i < qtd_cursos; i++){
    for(int j = 0; j < qtd_alunos; j++){
      if(alunos.get(j).apllied_for(i)){
        concorrencia_cursos[i].insert_ordered(alunos.get(j));
      }
    }
  }

  int esta_aprovado[qtd_alunos];
  for(int i = 0; i < qtd_alunos; i++) esta_aprovado[i] = -1;

  int qtd_aprovado[qtd_cursos];
  for(int i = 0; i < qtd_cursos; i++) qtd_aprovado[i] = 0;

  List<Student> aprovados[qtd_cursos];
  List<Student> lista_espera[qtd_cursos];

  bool mudou = true;
  while(mudou){
    mudou = false;
    for(int curso = 0; curso < qtd_cursos; curso++){
      int n_conc = concorrencia_cursos[curso].size();
      int n_vagas = cursos[curso].second;
      int min = n_conc < n_vagas ? n_conc : n_vagas;

      int i_nao_aprovados = qtd_aprovado[curso];

      for(int i = 0; i < n_conc && i_nao_aprovados < min && qtd_aprovado[curso] < n_vagas; i++){
        Student aluno = concorrencia_cursos[curso].get(n_conc - i - 1);
        if(esta_aprovado[aluno.id] == -1){
          if(aluno.first_option == curso){
            aprovados[curso].insert_ordered_course(aluno, curso);
            esta_aprovado[aluno.id] = 0;
            qtd_aprovado[curso]++;
            mudou = true;
          }

          i_nao_aprovados++;
        }
      }
    }
  }

  for(int curso = 0; curso < qtd_cursos; curso++){
    int n_conc = concorrencia_cursos[curso].size();
    int n_vagas = cursos[curso].second;
    int min = n_conc < n_vagas ? n_conc : n_vagas;

    int i_nao_aprovados = qtd_aprovado[curso];

    for(int i = 0; i < n_conc && i_nao_aprovados < min && qtd_aprovado[curso] < n_vagas; i++){
      Student aluno = concorrencia_cursos[curso].get(n_conc - i - 1);
      if(esta_aprovado[aluno.id] == -1){
        if(aluno.second_option == curso){
          aprovados[curso].insert_ordered_course(aluno, curso);
          esta_aprovado[aluno.id] = 1;
          qtd_aprovado[curso]++;
        }

        i_nao_aprovados++;
      }
    }
  }

  for(int curso = 0; curso < qtd_cursos; curso++){
    int n_conc = concorrencia_cursos[curso].size();

    for(int i = 0; i < n_conc; i++){
      Student aluno = concorrencia_cursos[curso].get(n_conc - i - 1);
      if(esta_aprovado[aluno.id] == -1){
        lista_espera[curso].insert_ordered_course(aluno, curso);
      }else if(esta_aprovado[aluno.id] == 1){
        if(aluno.second_option == curso){
          lista_espera[curso].insert_ordered_course(aluno, curso);
        }
      }
    }
  }

  cout << fixed << setprecision(2);
  for(int i = 0; i < qtd_cursos; i++){
    float nota_corte = 0;
    if(aprovados[i].size() >= cursos[i].second){
      nota_corte = aprovados[i].get(0).grade;
    }
    cout << cursos[i].first << " " << nota_corte << endl;
    cout << "Classificados" << endl;
    for(int j = aprovados[i].size() - 1; j >= 0; j--){
      Student aluno = aprovados[i].get(j);
      cout << aluno.name << " " << (double)aluno.grade << endl;
    }
    cout << "Lista de espera" << endl;
    for(int j = lista_espera[i].size() - 1; j >= 0; j--){
      Student aluno = lista_espera[i].get(j);
      cout << aluno.name << " " << (double)aluno.grade << endl;
    }
  }
}
