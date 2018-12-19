#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
//#include <sys/time.h>
#include <math.h>
//#include <unistd.h>



// Retorna 1 se numero for primo, e 0 caso contrário.
int eh_primo(int numero, char *detectLog)
{
    unsigned long long int k, i;
    FILE *fp;
    int flag1 = 0, flag2 = 0;

    if(numero <= 3)
        return 1;
    if(numero % 2 == 0)
        return 0;

    k = sqrt(numero);

    for(i = 3; i <= k; i += 2)
        if(numero % i == 0)
            flag1 = 0;

    for(i = 3; i <= k; i += 2)
        if(numero % i == 0)
            flag2 = 0;

    if(flag1 != flag2) {
      if (fp = fopen(detectLog, "a")) {
          fprintf(fp, " %d %d\n",flag1,flag2);
          fclose(fp);
      }
    }

    if(flag1 == 0){
      return flag1;
    }

    return 1;
}

// Se a flag for 1, retorna o número primo sucessor do primo gerado na chamada anterior começando no dois.
// Se a flag for 0, retorna 0, e além disso, zera a contagem de números primos das chamadas anteriores.
int gerar_primo(int flag, char *detectLog)
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
    while(!(eh_primo(contador, detectLog)))
    {
        contador = contador + 2;
    }
    primo = contador;
    primo = primo + 2;
    return (primo - 2);
}

void print_data(int size, unsigned *data) {
  int i = 0;
  printf("Printing data:\n");
  for(i = 0; i < size; i++) {
    printf("%u\n", data[i]);
  }
}

void readFileUnsigned(unsigned *input, char *filename, int size) {
    FILE *finput;
    if (finput = fopen(filename, "rb")) {
        fread(input, size * sizeof(unsigned), 1, finput);
        print_data(size, input);
    } else {
        printf("Error reading input file");
        exit(1);
    }
}

unsigned * gerar_primos_wrapper(int size, char *detectLog) {

    unsigned *data = (unsigned *)malloc(size*sizeof(unsigned));
    int i = 0;
    unsigned int numero = 0;
    gerar_primo(0, detectLog);

    for(i = 0; i < size; i++) {
      numero = gerar_primo(1, detectLog);
      data[i] = numero;
    }

    return data;
}

void save_output(int size, unsigned *data, char * outputFile) {

    FILE *fp;
    if (fp = fopen(outputFile, "wb")) {
        fwrite(data, size * sizeof(unsigned), 1, fp);
    } else {
        printf("Error writing output file");
        exit(1);
    }
    fclose(fp);
}

void compare_output(int size, unsigned *data1, unsigned *data2, char *detectLog) {
    int i;
    FILE *fp;
    for(i=0; i<size; i++) {
        if(data1[i] != data2[i]) {
            if (fp = fopen(detectLog, "a")) {
                fprintf(fp, "[%d]: %u %u\n",i,data1[i],data2[i]);
                fclose(fp);
            }

        }
    }
}

int main(int argc, char** argv)
{
    int quantidadeDePrimos = 1000000;
    char *outputFile = "/home/scheffel/trabalho-ftf/output";
    char *detectLog = "/home/scheffel/trabalho-ftf/detectLog";
    unsigned *data1, *data2, *input;


    // Execute quicksort and save the result at data1
    data1 = gerar_primos_wrapper(quantidadeDePrimos, detectLog);
    // Execute quicksort and save the result at data2
    //data2 = gerar_primos_wrapper(quantidadeDePrimos);

    // Compare outputs to check for SDCs
    //compare_output(quantidadeDePrimos, data1, data2, detectLog);

    // Save one of the outputs to disk
    save_output(quantidadeDePrimos, data1, outputFile);

    //print_data(quantidadeDePrimos, data1);

    free(data1);
    free(data2);
    printf("Done\n");

    return 0;
}
