#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contarVogais(char *palavra, int n);
char * removerPrimeiraLetra(char *s);
int eVogal(char c);

int main(){
  char s[30];

  scanf("%s", s);

  int n = contarVogais(s, 0);

  printf("%d\n", n);
}

int contarVogais(char *palavra, int n){
  if(strlen(palavra) == 0) return 0;
  else if(eVogal(palavra[0])) return contarVogais(palavra + 1, n) + 1;
  else return contarVogais(removerPrimeiraLetra(palavra), n);
}

char * removerPrimeiraLetra(char *s){
  return s + 1;
}

int eVogal(char c){
  return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}
