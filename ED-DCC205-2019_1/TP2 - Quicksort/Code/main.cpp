#include <iostream>

using namespace std;

void troca(int* a, int* b){
  int t = *a;
  *a = *b;
  *b = t;
}

int particao (int arr[], int esq, int dir){
  int pivo = arr[dir];
  int i = (esq - 1);

  for (int j = esq; j <= dir - 1; j++){
    if (arr[j] <= pivo){
      troca(&arr[i], &arr[j]);
    }
  }

  troca(&arr[i + 1], &arr[dir]);
  return (i + 1);
}

void quick_sort(int arr[], int esq, int dir){
  if (esq < dir){
    int pi = particao(arr, esq, dir);
    quick_sort(arr, esq, pi - 1);
    quick_sort(arr, pi + 1, dir);
  }
}

int main(){
  int arr[] = {10, 7, 8, 9, 1, 5};
  int n = sizeof(arr)/sizeof(arr[0]);
  quick_sort(arr, 0, n - 1);

  for(int i = 0; i < n; i++){
    cout << arr[i] << " ";
  }
  cout << endl;
  
  return 0;
}
