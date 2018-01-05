

#ifndef  main_h
#define  main_h

#define MAX 1024 
#define MAXTHREAD  50//最大线程数 
#define FILEBUF   4096
#define CONFIG    "./conf"
#define MAXLIN     128

#include <unistd.h>      
#include <string.h>
#include <string>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <pthread.h> 
#include <stdio.h>
#include <sys/stat.h>   
#include <fcntl.h> 
#include <iostream> 
#include <signal.h>
#include <netdb.h>

#include "conf.h"
#include "file.h"
#include "transmission.h"
#include "interaction.h"
#include "fun.h"
using namespace std;  



 

int gettb();
int freetb(int port);
int create_connect(int port);
void for_SIGPIPE( int);
void atexit(void *);
#endif