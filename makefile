
src := main.cpp
src += config.cpp
src += sock.cpp
src += pthread_pool.cpp
src += protocol.cpp

obj :=$(src:.cpp=.o)

.cpp.o:
	g++ --std=c++11 -g -c  -o $@ $<
all:$(obj)
	g++ --std=c++11 -g -o main $(obj) -lpthread
clean:$(.o)
	sudo rm *.o) 
	sudo rm main
