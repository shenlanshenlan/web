

#include "conf.h"
#include <iostream>
#include <string.h>  //string 自动释放
#include <stdio.h>
#include <stdlib.h>

conf::conf()    //默认配置
{ 
   char buf[512];
   int  buflen=512;
   memset(&addr,0,sizeof(addr));
  
   addr = NULL;
   port = 9811;  //默认端口号
   int  i;
   file  o;
   o.fread((char *)"./conf",buf,&buflen);
    
   char *p;
   p = strstr(buf,"=");  //第一个等号
   p++;

   memset(file_share_path,0,512); 
 
   for(i=0 ;i<512;i++)
   {  
      if( *p  == '\n')
       break;
      file_share_path[i] = *p;
      p++;
   }
    len = strlen(file_share_path); 
    //创建共享文件夹
    i= o.makedir(file_share_path);
    if(i == 0)
    {
      cout<<"Create a shared folder\n"
            "/home/share\n"<<flush;
    }
} 
/*  返回二维指针键值对    
*         
*/

char ** conf::readfile()
{   
      int conf_fd; 
      char lin[MAXLIN];
//open file
         conf_fd = open(CONFIG,O_RDONLY);
         if(conf_fd<0)
         {  
            cout<<"config file non exist"<<endl;
                        return NULL;     
         }
 

}
 













 
//******socker***////
_socket::_socket(conf *p)  
{  
    int err; 

     addr.sin_family = AF_INET;
     addr.sin_port = htons(p->port);
     addr.sin_addr.s_addr = htonl(INADDR_ANY);
     fd= socket(AF_INET, SOCK_STREAM, 0);
    
    //  cout<<fd; 输出当前描述符
     err = bind(fd,(struct sockaddr *)&addr,sizeof(addr));
     if(err <0)
     {cout<<"bind err\n"<<endl; 
       exit(0);
     }
     listen(fd,20);
}

int _socket::get_sock_fd(){
 return fd;
}
 
