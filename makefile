
obj = main.o config.o sock.o
run:main
	./main

main:$(obj)
	g++ -o main $(obj)

main.o:main.cpp
	g++ -c -o main.o main.cpp
config.o:config.cpp
	g++ -c -o config.o config.cpp
sock.o:sock.cpp
	g++ -c -o sock.o sock.cpp

