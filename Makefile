all: gerarPrimos gerarPrimosDuplicado

gerarPrimos:
	gcc -g gerarPrimos.c -o gerarPrimos -lm

gerarPrimosDuplicado:
	gcc -g gerarPrimosDuplicado.c -o gerarPrimosDuplicado -lm

clean:
	rm -f *.o gerarPrimos gerarPrimosDuplicado ./output ./detectLog
