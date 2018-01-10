
// 线程池
#ifndef PTHREAD_POOL
#define PTHREAD_POOL
 
#include <pthread.h>
#include "config.h"
 

#define  MAX_PTHREADS  16
#define  MAX_JOBS      10000
 

class job; 
class pthread_pool
{
public:
 
   pthread_t  threads[MAX_PTHREADS];
   job  *  point;   
   job  *  reac;   
   pthread_mutex_t mutex;
   pthread_cond_t  no_empty;
   
   int job_count;         //队列计数器
  
   int init();
   int create_pthread();
   int add_work(void*(*function)(void *),void *arg);
   job* out_work();
   ~pthread_pool();
 
static void * p_function(void *);
static void for_SIGPIPE(int n);     
 
   
};

class job
{
public:
  void  *(*work_function)(void *);
  void  *arg;
  job * next; 
};

#endif

 