all: testes

lab11:
	gcc -std=c99 -Wall -Werror=vla -g -lm lab11.c -o lab11

testes: lab11
	./lab11 < ./lab11testes/in/t01_in.txt > ./lab11testes/meuout/t01_meuout.txt
	./lab11 < ./lab11testes/in/t02_in.txt > ./lab11testes/meuout/t02_meuout.txt
	./lab11 < ./lab11testes/in/t03_in.txt > ./lab11testes/meuout/t03_meuout.txt
	./lab11 < ./lab11testes/in/t04_in.txt > ./lab11testes/meuout/t04_meuout.txt
	./lab11 < ./lab11testes/in/t05_in.txt > ./lab11testes/meuout/t05_meuout.txt
	diff ./lab11testes/out/t01_out.txt ./lab11testes/meuout/t01_meuout.txt > ./lab11testes/resultados/t1_resultado.txt
	diff ./lab11testes/out/t02_out.txt ./lab11testes/meuout/t02_meuout.txt > ./lab11testes/resultados/t2_resultado.txt
	diff ./lab11testes/out/t03_out.txt ./lab11testes/meuout/t03_meuout.txt > ./lab11testes/resultados/t3_resultado.txt
	diff ./lab11testes/out/t04_out.txt ./lab11testes/meuout/t04_meuout.txt > ./lab11testes/resultados/t4_resultado.txt
	diff ./lab11testes/out/t05_out.txt ./lab11testes/meuout/t05_meuout.txt > ./lab11testes/resultados/t5_resultado.txt
