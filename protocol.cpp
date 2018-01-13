

#include "protocol.h"



http::http(int cli)    
{ 

     int  i, s, n;
         
     char *v[10], *p;
       s=1;
    cout <<"http"<<endl;  
    for(i =0 ; i<512 ; i++)
    {   
       n = read(cli,&head[i],1);   
       p = &head[i]; 
      if( *p == ' ')
      {  
         *p = '\0';
          v[s] =&head[i+1];
          s++;      
      }else if ( *p == '\0')
            {       
                break;
            }    
      req_type = head;
      url = v[1];
      version = v[2];
 
    }
     

   for(i= 0 ;i<5 ;i++)
   {
      cout <<v[i];
   }


}