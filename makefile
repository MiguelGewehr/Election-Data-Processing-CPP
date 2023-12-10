main: main.o 
	g++ -std=c++17 -o main main.o 

main.o: main.cpp 
	g++ -std=c++17 -c -o main.o main.cpp