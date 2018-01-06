
obj = main.o config.o
run:main
	./main

main:$(obj)
	g++ -o main $(obj)

main.o:main.cpp
	g++ -c -o main.o main.cpp
config.o:config.cpp
	g++ -c -o config.o config.cpp


