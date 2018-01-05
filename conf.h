
 
#ifndef _CONF_H
#define _CONF_H

#include "main.h"
 
class conf               
{
public:
    int    listen_port;             
    char   file_share_path[512];    
    int    Max_pthread;
    int    Max_connect;
 
   conf();  //init
   virtual  int    init(); 
private:
   char **readfile();   
   void   readline(int ,char *);
}; 
 

 
/*****通信******/
class Socket   //return a addr fd;
{ 
public:
 Socket(conf *p);   //需要配置 指针对象 初始化
 
  int  fd;               //套接字描述符
  struct sockaddr_in addr;
 
  int get_sock_fd();
  
};


 #endif 