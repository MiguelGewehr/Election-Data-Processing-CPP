main: main.o LeitorDeArquivo.o Eleicao.o Candidato.o Federacao.o Partido.o 
	g++ -std=c++17 -o main main.o Eleicao.o Partido.o Candidato.o LeitorDeArquivo.o

main.o: main.cpp LeitorDeArquivo.h Eleicao.h Candidato.h Federacao.h Partido.h
	g++ -std=c++17 -c -o main.o main.cpp

LeitorDeArquivo.o: LeitorDeArquivo.cpp LeitorDeArquivo.h Eleicao.h
	g++ -std=c++17 -c -o LeitorDeArquivo.o LeitorDeArquivo.cpp

Eleicao.o: Eleicao.cpp Eleicao.h Partido.h Candidato.h
	g++ -std=c++17 -c -o Eleicao.o Eleicao.cpp

Candidato.o: Candidato.cpp Candidato.h Partido.h Federacao.h
	g++ -std=c++17 -c -o Candidato.o Candidato.cpp

Federacao.o: Federacao.cpp Federacao.h
	g++ -std=c++17 -c -o Federacao.o Federacao.cpp

Partido.o: Partido.cpp Partido.h
	g++ -std=c++17 -c -o Partido.o Partido.cpp



