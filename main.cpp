 
#define xingke cout<<"xingke"<<endl;

//
#include "main.h"
 
 

 #define ff(xx)  xx(sss,10)
 #define xx(name,value) name=value 
 


extern config conf;
extern pthread_pool pool;
extern sock    Sock;
int main() 
{  
    int sss;
     ff(xx); 
 cout <<sss;
 try{ 
 
  pool.init();   // thread pool    
  Sock.init();   // work with epoll 
  
 }
 
catch(const char* err)
 {  
  cout<<err<<endl;    
 }

    return 0; 
}
  
 //=========================================================
 
 void *work(void *arg)    
 {  
     int   cli; 
    /*if(arg == NULL)
     {
      cout<<"client-close"<<endl;
      return NULL;
     }*/

      cli = *(int*)arg;
      k::request     msg(cli);
      k::response    res(&msg);
  
   return NULL ;
 }

 
