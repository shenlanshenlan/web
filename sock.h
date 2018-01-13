#ifndef SOCK_H
#define SOCK_H

#include <iostream>
#include <string> 
#include <sys/epoll.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


#include "pthread_pool.h"


#define MAXEPOLLFD  1000
#define MAXCLIENTS  1000
#define PORT       80
using namespace std;



class sock
{  
   int  listen_fd;
   int  epoll_fd;
   struct epoll_event   event,events[MAXEPOLLFD]; //share
   int  clients[MAXCLIENTS]; //已建立的链接 是否必要
   

 public:
          int init();
          int create_listen();          
          int run();  
 
 private:
          int cli_add(int); //save client_fd
 					int cli_del(int); // delete client_fd when conneted closed;     
          int *get_cli_point(int);   
          int setnonblcoking(int * );
  
};
#endif    
