
/*  配置类 */ 
#ifndef _CONF_H
#define _CONF_H

#include "main.h"
 
class conf               
{
public:
  char  *addr;             
  int    port;             
  char   file_share_path[512];   
  int    len;
  conf();
private:
   char **readfile();   
   void   readline(int ,char *);
}; 
 
 
/*****通信******/
class _socket     //return a addr fd;
{ 
public:
  _socket(conf *p);   //需要配置 指针对象 初始化
 
  int  fd;               //套接字描述符
  struct sockaddr_in addr;
 
  int get_sock_fd();
  
};


 #endif 