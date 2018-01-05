
#include "interaction.h" 
#include <stdio.h> 
#include <iostream> 
#include <string.h>
#include <stdio.h>
  
 interaction ::interaction( transmission *o ) //构造
 {
   t = o;
   memset(request,0,100);
   r_len  = 0;
   mask    = -1;
 };
  
 
 int interaction::analysis(char *str,int len)
 {
     int  i,n ;
     char st[10];
     memset(st,0,10);
    for(i=0;i<len;i++)
    {  
        if(str[i] == ' '||str[i] == '\n')
        break ;
        st[i] = str[i];
    }
         
    masklen = i+1;

     if(strcmp(st,"mkdir") == 0) //创建目录
       return 0;
     if(strcmp(st,"get") == 0)
       return 1;
     if(strcmp(st,"dir") == 0)  //请求目录
       return 2;
     if(strcmp(st,"exit") ==0) 
       return 3;      
     if(strcmp(st,"rmdir") ==0)  //删除目录
       return 4;
     if(strcmp(st,"rm") ==0)     //删除文件
       return 5;
     if(strcmp(st,"dl")==0||strcmp(st,"download")==0)
       return 6;
     if(strcmp(st,"upload")==0)
       return 7;
   else 
   return -1;
 }
 void interaction::recvrequest( )
 {    
      memset(request,0,100);
      r_len  = 0;
      mask  = 0;
      int n;
      n = t->recv(request,&r_len);
      if(n == -1)
       { 
         mask = n;
         return; 
       }
   mask  = analysis(request,r_len);
 } 