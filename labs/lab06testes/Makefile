all: testes

lab06: lab06.o cobra.o
	gcc lab06.o cobra.o -g -lm -o lab06

lab06.o: lab06.c cobra.h
	gcc -std=c99 -Wall -Werror=vla -c lab06.c

cobra.o: cobra.c cobra.h
	gcc -std=c99 -Wall -Werror=vla -c cobra.c

testes: lab06
	./lab06 < ./lab06testes/in/t01_in.txt > ./lab06testes/meuout/t01_meuout.txt
	./lab06 < ./lab06testes/in/t02_in.txt > ./lab06testes/meuout/t02_meuout.txt
	./lab06 < ./lab06testes/in/t03_in.txt > ./lab06testes/meuout/t03_meuout.txt
	./lab06 < ./lab06testes/in/t04_in.txt > ./lab06testes/meuout/t04_meuout.txt
	./lab06 < ./lab06testes/in/t05_in.txt > ./lab06testes/meuout/t05_meuout.txt
	./lab06 < ./lab06testes/in/t06_in.txt > ./lab06testes/meuout/t06_meuout.txt
	diff ./lab06testes/out/t01_out.txt ./lab06testes/meuout/t01_meuout.txt > ./lab06testes/resultados/t01_resultado.txt
	diff ./lab06testes/out/t02_out.txt ./lab06testes/meuout/t02_meuout.txt > ./lab06testes/resultados/t02_resultado.txt
	diff ./lab06testes/out/t03_out.txt ./lab06testes/meuout/t03_meuout.txt > ./lab06testes/resultados/t03_resultado.txt
	diff ./lab06testes/out/t04_out.txt ./lab06testes/meuout/t04_meuout.txt > ./lab06testes/resultados/t04_resultado.txt
	diff ./lab06testes/out/t05_out.txt ./lab06testes/meuout/t05_meuout.txt > ./lab06testes/resultados/t05_resultado.txt
	diff ./lab06testes/out/t06_out.txt ./lab06testes/meuout/t06_meuout.txt > ./lab06testes/resultados/t06_resultado.txt
