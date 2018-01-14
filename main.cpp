 



#include "main.h"
 
 
void *work(void *); 
  
 
extern config conf;
extern pthread_pool pool;
extern sock    Sock;
int main() 
{ 
  
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
     cli = *(int*)arg;
     http      msg(cli);
     msg.response();
 
   return NULL ;
 }

 
