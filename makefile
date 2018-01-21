
obj = main.o config.o sock.o pthread_pool.o protocol.o -lpthread 
.o =  main main.o config.o sock.o pthread_pool.o protocol.o
test =  condition_test.cpp -lpthread
debug = main.cpp config.cpp sock.cpp pthread_pool.cpp protocol.cpp


run:main 
	sudo ./main

main:$(obj) 
	g++ -o main $(obj)

main.o:main.cpp
	g++ -c -o main.o main.cpp
config.o:config.cpp
	g++ -c -o config.o config.cpp
sock.o:sock.cpp
	g++ -c -o sock.o sock.cpp
pthread_pool.o:pthread_pool.cpp
	g++ -c -o pthread_pool.o pthread_pool.cpp

protocol.o:protocol.cpp
	g++ -c -o protocol.o protocol.cpp


gdb:debug  
	gdb debug

debug:$(debug)
	g++ -g -o debug $(debug) -lpthread    

cleandug:debug 
	rm debug

t:test
	./test
test:$(test)
	g++ -o test $(test)
clean:$(.o)
	sudo rm $(.o) 
