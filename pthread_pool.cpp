
#include "pthread_pool.h"
#include <unistd.h>
pthread_pool pool;    //global


 

/* 初始化
*/
int pthread_pool::init()
{
cout<<"pool init"<<endl;
pthread_mutex_init(&mutex,NULL);
pthread_cond_init(&no_empty,NULL);
front = NULL;
reac  = NULL;
job_count = 0;
int i;
for(  i = 0;i<MAX_PTHREADS;++i)
{
  pthread_create(&threads[i],NULL,p_function,&pool);
    
}
 cout<<i<<endl;
  sleep(1);
return 0;
}
  

 /* 线程函数   
 *
 */
void * pthread_pool::p_function(void * obj)
{   
class pthread_pool*pool = (class pthread_pool*)obj;     

while(1)
   {   
      pthread_mutex_lock(&pool->mutex);
         while(pool->job_count==0)
         {
             
          pthread_cond_wait(&pool->no_empty,&pool->mutex);        
         }

         job * cur_job =pool->out_work();

         pthread_mutex_unlock(&pool->mutex);

      cur_job->work_function(cur_job->arg);//work run
       delete cur_job;
    }
    
} 

int pthread_pool::add_work(void *(*function)(void *),void *arg)
{      

     if(job_count > MAX_JOBS)
       return  -1; 

         job * j = new job;             
         j->work_function = function;
         j->arg = arg; 
         
  pthread_mutex_lock(&mutex);
         
    if(front == NULL && reac == NULL ) //empty
    {   
        front = j;     
        j->next=front;         
    }else
    {            
        j->next  = front->next;
        front->next = j;
        front = j;
    } 
    job_count++;
   pthread_mutex_unlock(&mutex);
   pthread_cond_signal(&no_empty);  
   cout <<"add"<<endl;
   return 0;
  
}
job * pthread_pool::out_work()
{
    if(job_count == 0)
    { 
      return NULL; 
    }
     job * out ;
     out = front->next;
     front->next = out->next;
     job_count--;

     return out;
}
pthread_pool::~pthread_pool()
{  

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&no_empty);
}

 