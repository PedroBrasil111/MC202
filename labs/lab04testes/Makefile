all: testes

lab04:
	gcc -std=c99 -Wall -Werror=vla -g -lm lab04.c -o lab04

testes: lab04
	./lab04 < ./lab04testes/in/t01_in.txt > ./lab04testes/meuout/t01_meuout.txt
	./lab04 < ./lab04testes/in/t02_in.txt > ./lab04testes/meuout/t02_meuout.txt
	./lab04 < ./lab04testes/in/t03_in.txt > ./lab04testes/meuout/t03_meuout.txt
	./lab04 < ./lab04testes/in/t04_in.txt > ./lab04testes/meuout/t04_meuout.txt
	./lab04 < ./lab04testes/in/t05_in.txt > ./lab04testes/meuout/t05_meuout.txt
	./lab04 < ./lab04testes/in/t06_in.txt > ./lab04testes/meuout/t06_meuout.txt
	./lab04 < ./lab04testes/in/t07_in.txt > ./lab04testes/meuout/t07_meuout.txt
	diff ./lab04testes/out/t01_out.txt ./lab04testes/meuout/t01_meuout.txt > ./lab04testes/resultados/t01_resultado.txt
	diff ./lab04testes/out/t02_out.txt ./lab04testes/meuout/t02_meuout.txt > ./lab04testes/resultados/t02_resultado.txt
	diff ./lab04testes/out/t03_out.txt ./lab04testes/meuout/t03_meuout.txt > ./lab04testes/resultados/t03_resultado.txt
	diff ./lab04testes/out/t04_out.txt ./lab04testes/meuout/t04_meuout.txt > ./lab04testes/resultados/t04_resultado.txt
	diff ./lab04testes/out/t05_out.txt ./lab04testes/meuout/t05_meuout.txt > ./lab04testes/resultados/t05_resultado.txt
	diff ./lab04testes/out/t06_out.txt ./lab04testes/meuout/t06_meuout.txt > ./lab04testes/resultados/t06_resultado.txt
	diff ./lab04testes/out/t07_out.txt ./lab04testes/meuout/t07_meuout.txt > ./lab04testes/resultados/t07_resultado.txt
