
make: build link run

build:
	g++ -c -I "./include" ./src/Test.cpp -o ./lib/test.o
	g++ -c -I "./include" ./src/Node.cpp -o ./lib/Node.o
	g++ -c -I "./include" ./src/List.cpp -o ./lib/List.o
	g++ -c -I "./include" ./src/UI.cpp -o ./lib/UI.o
	g++ -c -I "./include" ./src/YoneticiList.cpp -o ./lib/YoneticiList.o


link:
	g++ ./lib/test.o ./lib/Node.o ./lib/UI.o ./lib/List.o ./lib/YoneticiList.o -o ./bin/program

run:
	./bin/program