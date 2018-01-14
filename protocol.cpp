

#include "protocol.h"



http::http(int client)    
{ 
  
     int  i, s, n;      
     char  *p;

     cli = client;
     s=1;    


    memset(elements,0,ELEMENT);
    elements[0] = msg;
    for(i =0 ; i<512 ; i++)
    {   
       n = read(cli,&msg[i],1);   
       p = &msg[i]; 

      if( *p == ' '|| *p == '\n')
      {  
         *p = '\0';
          elements[s] = &msg[i+1];   
          s++;
          continue;
      } 
       if ( *p == '\0')
            {       
                break;
            }    
      }

  /*  
 for(i=0;i<30;i++)
 {     
     if(elements[i] == NULL)
       break;
       printf("%d: %s\n",i,elements[i]);  
 } */
     req_type =elements[0];
     url      =elements[1];
   
} 

 
int http::response()
{    
      //各浏览器版本兼容问题/ 协议不一样啊
 
         memset(res_msg,0,MSGLEN);

         string    pagepath; 
         char      content[MAXPAGELEN];  
         int       file,n;
         int       msg_len=0;
         
         memset(content,0,MAXPAGELEN);
      write(1,url,strlen(url));
      write(1,"\n",1);
    
    if(strcmp(url,"/")==0)   //default_page
    {   
           
        pagepath=  conf.default_dir;
        pagepath = pagepath + '/';  
        pagepath = pagepath + "index.html";           
    }else
    {  
        pagepath=  conf.default_dir;
        pagepath = pagepath + url;   
    }   

       
     
       file = open((const char *)pagepath.data(),O_RDONLY);  
     if(file  > 0)     
      { 
        strcat(res_msg,"HTTP/1.0 200 OK\n");
        n = read(file,content,MAXPAGELEN);
        close(file);
      } else
      {
        strcat(res_msg,"HTTP/1.0 404 Not Found\n");
        n=0;  
        
      }  
         time_t tm;
         time(&tm);
         strcat(res_msg,ctime(&tm));
         strcat(res_msg,"Content-Type: text/html;\n");
         




        strcat(res_msg,"Content-Length:");                //length 
     
        char len[100];  

       
        sprintf(len,"%d",(n));
         
        strcat(res_msg,len);                               //length 
 
        strcat(res_msg,"\n");  //换行符？？？？？？？？
        strcat(res_msg,"\n");
        strcat(res_msg,content);
        strcat(res_msg,"\0"); 
          int s;
      
         s = write(cli,res_msg,strlen(res_msg));  
             write(1,res_msg,strlen(res_msg));  


         
  return 0;
}   