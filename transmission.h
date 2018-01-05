

#ifndef    _transmission_h
#define    _transmission_h



#include "main.h"
 
using namespace std;

 
/********   传输层******/
class  transmission  //初始化获取fd  定义接受  发送两个操作
{ 
public: 
    int   client_fd;
    transmission(int sockfd);
int send(char * buf , int   len );    
int recv(char * buf , int  *len );  //返回长度

}; 



#endif