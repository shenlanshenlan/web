

#include "conf.h"
#include <iostream>
#include <string.h>  //string 自动释放
#include <stdio.h>
#include <stdlib.h>

conf::conf()    //默认配置
{ 
    memset(file_share_path, 0 ,512); 
    init();
    if(file_share_path[0] == '\0') //默认共享目录
    {     
        char * usr_path = getenv("HOME"); 
        strcat(file_share_path,usr_path);
        strcat(file_share_path,"/share");  
    } 
    if(file::makedir(file_share_path)==0) 
      {
         cout<<"Create a shared folder\n"
             <<file_share_path<<endl;
      } 
 

  /*  v1
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
 
   for(i=0 ;i<512;i++)    {
      cout<<"Create a shared folder\n"
            "/home/share\n"<<flush;
    }*/
 /*  {  
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
    } */
} 

int conf::init() 
{ 
     char key[50];  
     char value[50];
     int  file_fd;
     int  n;
     int  i;
     file_fd = open((char *)"./conf",O_RDONLY);
     if(file_fd<0)
     {
       return -1;
     }
 
 while(1)
 { 
      memset(key,0,50);
      memset(value,0,50);

      for(i = 0; i<50; i++)
      {
      n =  read(file_fd,&key[i],1);
      if(n == 0)
      {
        close(file_fd);
        return 0;
      }
        if(key[i]  == '=')
        {
           key[i]  = '\0';
           break;
        }               
      }
      for(i = 0; i<50; i++) 
      {
       n = read(file_fd,&value[i],1);
         if(n == 0)
         { 
           close(file_fd);
           return 0;
         }
        if(value[i]  == '\n')
        {
           value[i]  = '\0';
           break;
        }   

      }            
   //   key and value 
 
   if(strcmp(key,"file_share_path")==0)
        {  
           strcpy(file_share_path,value);
        }
   if(strcmp(key,"listen_port")==0)
        {  
           listen_port=atoi(value);
        }
  if(strcmp(key,"Max_pathread")==0)  
        {
            Max_pthread = atoi(value);
        }
  if(strcmp(key,"Max_connect")==0)
        {
            Max_connect = atoi(value);
        }  
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
Socket::Socket(conf *p)  
{  
    int err; 
      cout<<p->listen_port<<endl;
     addr.sin_family = AF_INET;
     addr.sin_port = htons(p->listen_port);
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

int Socket::get_sock_fd(){
 return fd;
}
 
