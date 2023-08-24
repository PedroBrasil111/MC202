all: testes

lab05: lab05.o ultron.o
	gcc lab05.o ultron.o -g -lm -o lab05

lab05.o: lab05.c ultron.h
	gcc -std=c99 -Wall -Werror=vla -c lab05.c

ultron.o: ultron.c ultron.h
	gcc -std=c99 -Wall -Werror=vla -c ultron.c

testes: lab05
	./lab05 < ./lab05testes/in/t01_in.txt > ./lab05testes/meuout/t01_meuout.txt
	./lab05 < ./lab05testes/in/t02_in.txt > ./lab05testes/meuout/t02_meuout.txt
	./lab05 < ./lab05testes/in/t03_in.txt > ./lab05testes/meuout/t03_meuout.txt
	./lab05 < ./lab05testes/in/t04_in.txt > ./lab05testes/meuout/t04_meuout.txt
	./lab05 < ./lab05testes/in/t05_in.txt > ./lab05testes/meuout/t05_meuout.txt
	./lab05 < ./lab05testes/in/t06_in.txt > ./lab05testes/meuout/t06_meuout.txt
	./lab05 < ./lab05testes/in/t07_in.txt > ./lab05testes/meuout/t07_meuout.txt
	./lab05 < ./lab05testes/in/t08_in.txt > ./lab05testes/meuout/t08_meuout.txt
	diff ./lab05testes/out/t01_out.txt ./lab05testes/meuout/t01_meuout.txt > ./lab05testes/resultados/t01_resultado.txt
	diff ./lab05testes/out/t02_out.txt ./lab05testes/meuout/t02_meuout.txt > ./lab05testes/resultados/t02_resultado.txt
	diff ./lab05testes/out/t03_out.txt ./lab05testes/meuout/t03_meuout.txt > ./lab05testes/resultados/t03_resultado.txt
	diff ./lab05testes/out/t04_out.txt ./lab05testes/meuout/t04_meuout.txt > ./lab05testes/resultados/t04_resultado.txt
	diff ./lab05testes/out/t05_out.txt ./lab05testes/meuout/t05_meuout.txt > ./lab05testes/resultados/t05_resultado.txt
	diff ./lab05testes/out/t06_out.txt ./lab05testes/meuout/t06_meuout.txt > ./lab05testes/resultados/t06_resultado.txt
	diff ./lab05testes/out/t07_out.txt ./lab05testes/meuout/t07_meuout.txt > ./lab05testes/resultados/t07_resultado.txt
	diff ./lab05testes/out/t08_out.txt ./lab05testes/meuout/t08_meuout.txt > ./lab05testes/resultados/t08_resultado.txt
