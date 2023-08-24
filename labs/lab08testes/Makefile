all: testes

lab08:
	gcc -std=c99 -Wall -Werror=vla -g -lm lab08.c -o lab08

testes: lab08
	./lab08 < ./lab08testes/in/t01_in.txt > ./lab08testes/meuout/t01_meuout.txt
	diff ./lab08testes/out/t01_out.txt ./lab08testes/meuout/t01_meuout.txt > ./lab08testes/resultados/t01_resultado.txt
	./lab08 < ./lab08testes/in/t02_in.txt > ./lab08testes/meuout/t02_meuout.txt
	diff ./lab08testes/out/t02_out.txt ./lab08testes/meuout/t02_meuout.txt > ./lab08testes/resultados/t02_resultado.txt
	./lab08 < ./lab08testes/in/t03_in.txt > ./lab08testes/meuout/t03_meuout.txt
	diff ./lab08testes/out/t03_out.txt ./lab08testes/meuout/t03_meuout.txt > ./lab08testes/resultados/t03_resultado.txt
	./lab08 < ./lab08testes/in/t04_in.txt > ./lab08testes/meuout/t04_meuout.txt
	diff ./lab08testes/out/t04_out.txt ./lab08testes/meuout/t04_meuout.txt > ./lab08testes/resultados/t04_resultado.txt
	./lab08 < ./lab08testes/in/t05_in.txt > ./lab08testes/meuout/t05_meuout.txt
	diff ./lab08testes/out/t05_out.txt ./lab08testes/meuout/t05_meuout.txt > ./lab08testes/resultados/t05_resultado.txt
