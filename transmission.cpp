


#include "transmission.h"
#include <unistd.h>
#include <stdio.h>  
#include <string.h>

 
transmission::transmission(int sockfd)
{
    client_fd  = sockfd;
}

int transmission::send(char * buf,int len )
{   
    cout<<"send~~~~~:"<<buf<<len<<endl;
     
   // write(client_fd,&m,4);     //操作码
    write(client_fd,&len,4);   //长度
    write(client_fd,buf,len);  //正文
   
return 0;
}
int  transmission::recv(char * buf, int *len)
{ 
    int rdlen;
    int n;
    int z;
 
    n = read(client_fd,&rdlen,4);
    if(n == 0)
    {
        cout<<"link break\n";
      return -1;
    }
    if(n != 4)
    {   
        cout<<"read len error\n";
        return -2;
    }
    
    n = read(client_fd,buf,rdlen);
    
    if(n !=rdlen)
    {
        cout<<"read content error\n";
        return -3;
    }
   
    else
    *len = rdlen;
    cout<<"recv:~~~~"<<buf<<endl;
return 0;
}