all: testes

lab07: lab07.o pilha.o fila.o
	gcc lab07.o pilha.o fila.o -lm -o lab07

lab07.o: lab07.c pilha.h fila.h
	gcc -std=c99 -Wall -Werror -Werror=vla -g -c lab07.c

pilha.o: pilha.c pilha.h
	gcc -std=c99 -Wall -Werror -Werror=vla -g -c pilha.c

fila.o: fila.c fila.h
	gcc -std=c99 -Wall -Werror -Werror=vla -g -c fila.c

testes: lab07
	./lab07 < ./lab07testes/in/t01_in.txt > ./lab07testes/meuout/t01_meuout.txt
	./lab07 < ./lab07testes/in/t02_in.txt > ./lab07testes/meuout/t02_meuout.txt
	./lab07 < ./lab07testes/in/t03_in.txt > ./lab07testes/meuout/t03_meuout.txt
	./lab07 < ./lab07testes/in/t04_in.txt > ./lab07testes/meuout/t04_meuout.txt
	./lab07 < ./lab07testes/in/t05_in.txt > ./lab07testes/meuout/t05_meuout.txt
	./lab07 < ./lab07testes/in/t06_in.txt > ./lab07testes/meuout/t06_meuout.txt
	diff ./lab07testes/out/t01_out.txt ./lab07testes/meuout/t01_meuout.txt > ./lab07testes/resultados/t01_resultado.txt
	diff ./lab07testes/out/t02_out.txt ./lab07testes/meuout/t02_meuout.txt > ./lab07testes/resultados/t02_resultado.txt
	diff ./lab07testes/out/t03_out.txt ./lab07testes/meuout/t03_meuout.txt > ./lab07testes/resultados/t03_resultado.txt
	diff ./lab07testes/out/t04_out.txt ./lab07testes/meuout/t04_meuout.txt > ./lab07testes/resultados/t04_resultado.txt
	diff ./lab07testes/out/t05_out.txt ./lab07testes/meuout/t05_meuout.txt > ./lab07testes/resultados/t05_resultado.txt
	diff ./lab07testes/out/t06_out.txt ./lab07testes/meuout/t06_meuout.txt > ./lab07testes/resultados/t06_resultado.txt
