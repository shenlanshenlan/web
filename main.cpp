 



#include "main.h"
 
config  Conf;
sock    Sock;
 
void *(*f )(void*);
void *c(void *); 
 int global=0;
extern pthread_pool pool;
int main() 
{ 
   //quequ test
  

  
   pool.init();
   int n;
   f= c;
 
  for ( ; ; )
  {  
      if((pool.add_work(f,NULL))==-1) 
        continue;
  }
 
 

 
 sleep(100);

   return 0; 
}
 
 void *c(void *) 
 {    global+=1;
      cout<<global<<endl;
         
     return NULL;
 }
