


#include <iostream> 
#include <pthread.h>
#include <unistd.h>
using namespace std;



void * p_fun( void  *);
void * p_fun2( void  *);


int global=5;
pthread_mutex_t  mutex;      //互斥锁
pthread_cond_t   condition;  //条件变量
int main() 
{ 

   pthread_t   tid; 
   //init
   pthread_mutex_init(&mutex,NULL);
   pthread_cond_init(&condition,NULL);


   pthread_create(&tid,NULL,p_fun,NULL);

  
      for(int i =0;i<5;i++)  //create five threads
   {
        
   pthread_create(&tid,NULL,p_fun2,NULL);
   }

   
   sleep(30);
  
   cout<<global<<flush;

 //free
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&condition);
   return 0; 
}

void * p_fun( void  *)   //等待条件
{   
   pthread_mutex_lock(&mutex);
       cout<<"a"<<endl;
        while(global >2 )  //
        {      
         cout<<"cond_wait"<<endl;
         pthread_cond_wait(&condition,&mutex);   
        }
    
    cout<<"1end"<<endl;
  pthread_mutex_unlock(&mutex);
  return NULL;
}
void * p_fun2( void  *)   //改变条件
{     
   pthread_mutex_lock(&mutex);
    
   global--;
   cout<<"b "<<global<<endl;
   pthread_cond_signal(&condition); //send sig
            //此时如果不解锁 等待线程将无法获取锁
   
   pthread_mutex_unlock(&mutex);

 
  return NULL;
}
