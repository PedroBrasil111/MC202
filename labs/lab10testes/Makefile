all: testes

lab10: lab10.o hash.o
	gcc lab10.o hash.o -g -lm -o lab10

lab10.o: lab10.c hash.h
	gcc -std=c99 -Wall -Werror=vla -g -lm -c lab10.c

hash.o: hash.c hash.h
	gcc -std=c99 -Wall -Werror=vla -g -lm -c hash.c

testes: lab10
	./lab10 < ./lab10testes/in/t01_in.txt > ./lab10testes/meuout/t01_meuout.txt
	./lab10 < ./lab10testes/in/t02_in.txt > ./lab10testes/meuout/t02_meuout.txt
	./lab10 < ./lab10testes/in/t03_in.txt > ./lab10testes/meuout/t03_meuout.txt
	./lab10 < ./lab10testes/in/t04_in.txt > ./lab10testes/meuout/t04_meuout.txt
	./lab10 < ./lab10testes/in/t05_in.txt > ./lab10testes/meuout/t05_meuout.txt
	./lab10 < ./lab10testes/in/t06_in.txt > ./lab10testes/meuout/t06_meuout.txt
	diff ./lab10testes/out/t01_out.txt ./lab10testes/meuout/t01_meuout.txt > ./lab10testes/resultados/t1_resultado.txt
	diff ./lab10testes/out/t02_out.txt ./lab10testes/meuout/t02_meuout.txt > ./lab10testes/resultados/t2_resultado.txt
	diff ./lab10testes/out/t03_out.txt ./lab10testes/meuout/t03_meuout.txt > ./lab10testes/resultados/t3_resultado.txt
	diff ./lab10testes/out/t04_out.txt ./lab10testes/meuout/t04_meuout.txt > ./lab10testes/resultados/t4_resultado.txt
	diff ./lab10testes/out/t05_out.txt ./lab10testes/meuout/t05_meuout.txt > ./lab10testes/resultados/t5_resultado.txt
	diff ./lab10testes/out/t06_out.txt ./lab10testes/meuout/t06_meuout.txt > ./lab10testes/resultados/t6_resultado.txt
