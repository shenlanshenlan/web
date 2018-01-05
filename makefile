

obj = main.cpp conf.cpp file.cpp transmission.cpp interaction.cpp  fun.cpp -lpthread
soursce = main.cpp conf.cpp file.cpp transmission.cpp interaction.cpp fun.cpp    main.h conf.h file.h transmission.h interaction.h fun.h  conf document makefile 
run:main
	./main
main:$(obj)
	 g++ -g -o main $(obj)

save:
	scp -r /home/ki/web_file k@192.168.1.109:/home/k/
