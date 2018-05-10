#include <stdio.h>

int main(){
	char sexo;
	int idade;
	int contr;

	scanf("%c", &sexo);
	scanf("%d", &idade);
	scanf("%d", &contr);

  if(idade < 0){
      printf("Idade invalida!\n");
  }else if(sexo != 'M' && sexo != 'F'){
      printf("Sexo invalido!\n");
  }else if(contr <= 0){
      printf("Tempo de contribuicao invalido!\n");
  }else{
  	if(sexo == 'M'){
  		if(idade >= 70){
  		    printf("Aposentadoria compulsoria\n");
      	}else if(idade >= 65 || (idade >= 60 && contr >= 35)){
      		printf("O servidor pode aposentar\n");
      	}else{
      		printf("O servidor nao pode aposentar\n");
      	}
      }else if(sexo == 'F'){
      	if(idade >= 70){
      		printf("Aposentadoria compulsoria\n");
      	}else if(idade >= 60 || (idade >= 55 && contr >= 30)){
      		printf("O servidor pode aposentar\n");
      	}else{
      		printf("O servidor nao pode aposentar\n");
      	}
      }else{
  	    printf("Idade invalida!\n");
      }
	}

	return 0;
}
