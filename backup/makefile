

obj = main.cpp conf.cpp file.cpp transmission.cpp interaction.cpp  fun.cpp -lpthread
soursce = main.cpp conf.cpp file.cpp transmission.cpp interaction.cpp fun.cpp    main.h conf.h file.h transmission.h interaction.h fun.h  conf document makefile 
run:main
	./main
main:$(obj)
	 g++ -o -g main $(obj)

save:backup
	cp $(soursce) ./backup
backup:
	mkdir backup
