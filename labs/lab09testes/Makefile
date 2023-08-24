all: testes

lab09:
	gcc -std=c99 -Wall -Werror=vla -g -lm lab09.c -o lab09

testes: lab09
	./lab09 < ./lab09testes/in/t01_in.txt > ./lab09testes/meuout/t01_meuout.txt
	./lab09 < ./lab09testes/in/t02_in.txt > ./lab09testes/meuout/t02_meuout.txt
	./lab09 < ./lab09testes/in/t03_in.txt > ./lab09testes/meuout/t03_meuout.txt
	./lab09 < ./lab09testes/in/t04_in.txt > ./lab09testes/meuout/t04_meuout.txt
	./lab09 < ./lab09testes/in/t05_in.txt > ./lab09testes/meuout/t05_meuout.txt
	diff ./lab09testes/out/t01_out.txt ./lab09testes/meuout/t01_meuout.txt > ./lab09testes/resultados/t01_resultado.txt
	diff ./lab09testes/out/t05_out.txt ./lab09testes/meuout/t05_meuout.txt > ./lab09testes/resultados/t05_resultado.txt
	diff ./lab09testes/out/t02_out.txt ./lab09testes/meuout/t02_meuout.txt > ./lab09testes/resultados/t02_resultado.txt
	diff ./lab09testes/out/t03_out.txt ./lab09testes/meuout/t03_meuout.txt > ./lab09testes/resultados/t03_resultado.txt
	diff ./lab09testes/out/t04_out.txt ./lab09testes/meuout/t04_meuout.txt > ./lab09testes/resultados/t04_resultado.txt
