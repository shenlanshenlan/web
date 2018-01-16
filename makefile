
obj = main.o b.o  
run:main
	./main
 
main:$(obj)
	g++ -o main $(obj)

main.o:main.cpp
	g++ -c -o main.o main.cpp
 
b.o:b.cpp
	g++ -c -o b.o b.cpp
 
