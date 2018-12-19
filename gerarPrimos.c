#include <stdlib.h>
#include <stdio.h>
#include <math.h>


// Retorna 1 se numero for primo, e 0 caso contrário.
int eh_primo(int numero)
{
    unsigned long long int k, i;

    if(numero <= 3)
        return 1;
    if(numero % 2 == 0)
        return 0;

    k = sqrt(numero);

    for(i = 3; i <= k; i += 2)
        if(numero % i == 0)
            return 0;
    return 1;
}

// Se a flag for 1, retorna o número primo sucessor do primo gerado na chamada anterior começando no dois.
// Se a flag for 0, retorna 0, e além disso, zera a contagem de números primos das chamadas anteriores.
int gerar_primo(int flag)
{
    unsigned long long static int primo=2;
    unsigned long long int contador;

    if(flag == 0)
    {
        primo = 2;
        return 0;
    }

    contador = primo;
    if(contador <= 3)
    {
        primo++;
        if(primo == 4)
            primo++;
        return contador;
    }

    contador = primo;
    while(!(eh_primo(contador)))
    {
        contador = contador + 2;
    }
    primo = contador;
    primo = primo + 2;
    return (primo - 2);
}

int  main() {
  FILE *file;
  char *output = "/home/scheffel/trabalho-ftf/output";
  int numeroDePrimos = 1000000;
  int numero;
  file = fopen(output, "w");
  if(file == NULL) {
    printf("Error openning file.\n");
    exit(1);
  }

  int i = 0;

  printf("Geraração de %d números primos.\n", numeroDePrimos);
  printf("_________________________________\n");
  for(i = 0; i < numeroDePrimos; i++) {
    numero = gerar_primo(1);
    //printf("[%d] - %d\n", i+1, numero);
    fprintf(file, "%d ", numero);
  }
  printf("_________________________________\n");
  printf("Geração concluida.\n");
  fclose(file);

  return 0;
}
