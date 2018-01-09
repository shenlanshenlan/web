 



#include "main.h"
 
config  Conf;
sock    Sock;
 
void *(*f )(void*);
void *c(void *); 

extern pthread_pool pool;
int main() 
{ 







    
   pool.init();
   int n=0;
   f= c;
  for ( ; ; )
  {  
 
      if((pool.add_work(f,NULL))==-1) 
      break;
      n++;
  }

 
cout<<"~~~~~~~~~~~~~~~~~"<<pool.job_count<<":"<<n<<"sleep"<<endl;

 sleep(10);

   return 0; 
}
 
 void *c(void *) 
 {
    // cout<<pthread_self()<<endl;        
     return NULL;
 }
