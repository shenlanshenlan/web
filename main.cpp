 



#include "main.h"
 
config  Conf;
sock    Sock;
 
void *(*f )(void*);
void *c(void *); 

extern pthread_pool pool;
int main() 
{ 
   //quequ test
  

  
   pool.init();
   int n=0;
   f= c;
  for ( ; ; )
  {  
 
      if((pool.add_work(f,NULL))==-1) 
      break;
      n++;
      cout<<n<<endl;
  }

 
cout<<"============"<<pool.job_count<<":"<<n<<"sleep"<<endl;

 sleep(100);

   return 0; 
}
 
 void *c(void *) 
 {
    sleep( 1);



     cout<<pool.job_count<<endl;        
     return NULL;
 }
