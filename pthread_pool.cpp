#include "pthread_pool.h"
#include <unistd.h>
#include <signal.h>
pthread_pool pool;    //global 
/* 初始化
*/
int pthread_pool::init() {
signal(SIGPIPE,for_SIGPIPE); 
pthread_mutex_init(&mutex,NULL); 
pthread_cond_init(&no_empty,NULL);
point = NULL;   
reac  = NULL;  
job_count = 0;
 
create_pthread();

cout<<"pool init "<<endl;
 
return 0;
}
  
int pthread_pool::create_pthread()
{
    int i;
    for(i =0;i<MAX_PTHREADS; i++)
{
  pthread_create(&threads[i],NULL,p_function,&pool);
    
}
 
return 0;
}
 
 /* 线程函数   
 *
 */
void * pthread_pool::p_function(void * obj)
{   
 class pthread_pool*pool = (class pthread_pool*)obj;     
  job * cur_job = NULL;
while(1)
   {   
      pthread_mutex_lock(&pool->mutex);
         while((pool->point)==NULL)
         {         
          pthread_cond_wait(&pool->no_empty,&pool->mutex);        
         }
           cur_job =pool->out_work();
         
          pthread_mutex_unlock(&pool->mutex); 
          pthread_cond_signal(&pool->no_empty); 
           
          cur_job->work_function(cur_job->arg);//work run
        delete cur_job; 
     }
    
} 

int pthread_pool::add_work(void *(*function)(void *),void *arg)
{      

      if(job_count == MAX_JOBS)
       return  -1;  //增加线程

         job * node = new job;             
         node->work_function = function;
         node->arg = arg; 
         
  pthread_mutex_lock(&mutex);
         
    if(point == NULL) //empty
    {   
        point = node;    
         
        node->next = point;         
    }else
    {         
        node->next = point->next;    //新节点指向   队列头
        point->next = node;          //添加到当前节点的下一个
        point = node;                //重新定位指针
     } 
    job_count++;    
   pthread_mutex_unlock(&mutex);
   pthread_cond_signal(&no_empty);  
   return 0;
  
}
job * pthread_pool::out_work()
{    
   
      job * out ;

     if(point == point->next)   
     {   out = point ;
         point = NULL;
         job_count=0;
        return out;        
     } 
    else{
     out = point->next;
     point->next = out->next;
     job_count--;
    }

 
     return out;
}

pthread_pool::~pthread_pool()
{  

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&no_empty);
}

void pthread_pool::for_SIGPIPE(int n) 
{ 
 cout<<"socket close SIGPIPE"<<endl;
}
 
