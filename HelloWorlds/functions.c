#include <stdio.h>



void myFunction(int contador) {
  
  if (contador <= 5){
    printf("ciclo %d\n", contador);
    myFunction(++contador);
  }
  else{
    printf("Recursividad acabada");
  }
}

int main() {
  myFunction(1);
  return 0;
}



