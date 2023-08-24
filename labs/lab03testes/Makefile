all: testes

lab03: lab03.o represa.o
	gcc lab03.o represa.o -g -lm -o lab03

lab03.o: lab03.c represa.h
	gcc -std=c99 -Wall -Werror -c lab03.c

represa.o: represa.c represa.h
	gcc -std=c99 -Wall -Werror -c represa.c

testes: lab03
	./lab03 < ./lab03testes/in/t01_in.txt > ./lab03testes/meuout/t01_meuout.txt
	./lab03 < ./lab03testes/in/t02_in.txt > ./lab03testes/meuout/t02_meuout.txt
	./lab03 < ./lab03testes/in/t03_in.txt > ./lab03testes/meuout/t03_meuout.txt
	./lab03 < ./lab03testes/in/t04_in.txt > ./lab03testes/meuout/t04_meuout.txt
	./lab03 < ./lab03testes/in/t05_in.txt > ./lab03testes/meuout/t05_meuout.txt
	./lab03 < ./lab03testes/in/t06_in.txt > ./lab03testes/meuout/t06_meuout.txt
	./lab03 < ./lab03testes/in/t07_in.txt > ./lab03testes/meuout/t07_meuout.txt
	./lab03 < ./lab03testes/in/t08_in.txt > ./lab03testes/meuout/t08_meuout.txt
	./lab03 < ./lab03testes/in/t09_in.txt > ./lab03testes/meuout/t09_meuout.txt
	./lab03 < ./lab03testes/in/t10_in.txt > ./lab03testes/meuout/t10_meuout.txt
	diff ./lab03testes/out/t01_out.txt ./lab03testes/meuout/t01_meuout.txt > ./lab03testes/resultados/t01_resultado.txt
	diff ./lab03testes/out/t02_out.txt ./lab03testes/meuout/t02_meuout.txt > ./lab03testes/resultados/t02_resultado.txt
	diff ./lab03testes/out/t03_out.txt ./lab03testes/meuout/t03_meuout.txt > ./lab03testes/resultados/t03_resultado.txt
	diff ./lab03testes/out/t04_out.txt ./lab03testes/meuout/t04_meuout.txt > ./lab03testes/resultados/t04_resultado.txt
	diff ./lab03testes/out/t05_out.txt ./lab03testes/meuout/t05_meuout.txt > ./lab03testes/resultados/t05_resultado.txt
	diff ./lab03testes/out/t06_out.txt ./lab03testes/meuout/t06_meuout.txt > ./lab03testes/resultados/t06_resultado.txt
	diff ./lab03testes/out/t08_out.txt ./lab03testes/meuout/t08_meuout.txt > ./lab03testes/resultados/t08_resultado.txt
	diff ./lab03testes/out/t10_out.txt ./lab03testes/meuout/t10_meuout.txt > ./lab03testes/resultados/t10_resultado.txt
	diff ./lab03testes/out/t07_out.txt ./lab03testes/meuout/t07_meuout.txt > ./lab03testes/resultados/t07_resultado.txt
	diff ./lab03testes/out/t09_out.txt ./lab03testes/meuout/t09_meuout.txt > ./lab03testes/resultados/t09_resultado.txt