

#include "protocol.h"

namespace k
{

request::request(int client)    
{ 
     int  i, s, n;      
     char  *p;

     cli = client;
     s=1;    
     
    if(client <0)
      {
        cout<<"client fd ERR!";
      }


    memset(elements,0,ELEMENT);
    elements[0] = msg;
    for(i =0 ; i<512 ; i++)
    {   
      if(s==ELEMENT)
           break;
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

 for(i=0;i<30;i++)  // cout
 {     
     if(elements[i] == NULL)
       break;
       printf("%d: %s\n",i,elements[i]);  
 } 
     req_type =elements[0];
     url      =elements[1];
} 

 
response::response(request * req)
{      
         string    pagepath;      
         int       file,n,e;
         int       msg_len=0;

        memset(msg,0,MSGLEN);
        memset(page,0,MAXPAGELEN);

 
    if(strcmp(req->url,"/")==0)   //default_page
    {        
        pagepath = conf.default_dir;
        pagepath = pagepath + '/';  
        pagepath = pagepath + "index.html";           
    }else
    {  
        pagepath=  conf.default_dir;
        pagepath = pagepath +req->url;   
    }   
 
       file = open((const char *)pagepath.data(),O_RDONLY);  
     if(file  > 0)     
      { 
        strcat(msg,"HTTP/1.0 200 OK\n");
        n = read(file,page,MAXPAGELEN);
        close(file);
      } else
      {
        strcat(msg,"HTTP/1.0 404 Not Found\n");
        n=0;    
      }  
         time_t tm;
         time(&tm);
         strcat(msg,ctime(&tm));
         strcat(msg,"Content-Type: text/html;\n");
 
         strcat(msg,"Content-Length:");             
     
         char len[100];       
         sprintf(len,"%d",(n));       
         strcat(msg,len);                         
 
        strcat(msg,"\n");   
        strcat(msg,"\n");
        strcat(msg,page);
        strcat(msg,"\0"); 
           
  
        e=0;
        while(1)
        {
          n = write(req->cli,msg,strlen(msg));
          e+=n;  
          if(e==strlen(msg))
             break;
        }
}   

}//namespace
