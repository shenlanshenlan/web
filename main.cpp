 



#include "main.h"
 
config  Conf;
sock    Sock;
 
void *(*f )(void*);
void *c(void *); 
 int global=0;
extern pthread_pool pool;
int main() 
{ 
 try{

  Sock.init();
 

 
 }
 
catch(const char* err)
 {  
  cout<<err<<endl;    
 }
 

    return 0; 
}
  
 //=========================================================

 void *c(void *)    //pthread_work_test
 {    global+=1;
      cout<<global<<endl;
         
     return NULL;
 }


int pool_test()    //a test for pool 
{ 
   pool.init();
   int n;
   f= c;
  for ( ; ; )
  {  
      if((pool.add_work(f,NULL))==-1) 
        continue;
  }
 sleep(100);
}