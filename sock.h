#ifndef SOCK_H
#define SOCK_H

#include <iostream>
#include <string> 
#include <sys/epoll.h>
#include <netdb.h>

#define MAXEPOLLFD  10000
#define PORT       80
using namespace std;



class sock
{  
   int listen_fd;
   int epoll_fd;



 public:
          int init();
          int create_listen();          
 
  
};
#endif   