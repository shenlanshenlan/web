
obj = main.o config.o sock.o pthread_pool.o -lpthread
.o = main.o config.o sock.o pthread_pool.o
test =  condition_test.cpp -lpthread
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
pthread_pool.o:pthread_pool.cpp
	g++ -c -o pthread_pool.o pthread_pool.cpp




t:test
	./test
test:$(test)
	g++ -o test $(test)
clean:$(.o)
	rm $(.o)