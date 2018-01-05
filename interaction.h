/******交互******/
#ifndef  INTERACTION_H
#define  INTERACTION_H
#include "main.h"
 
using namespace std;
class transmission;
   
 
class interaction  //包含传输对象 T 
{
public:
   char  request[100];         //获取的命令
   int   r_len;               //命令长度
   transmission *t;            //传输对象
   int  mask;                  //请求码
   int  masklen;
    interaction(transmission *o);                   
      void recvrequest( );  //获取请求
private:
      int  analysis(char *str,int len); //解析  并返回 命令码  （扩展）
 
};
 

 #endif