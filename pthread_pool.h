
// 线程池
#ifndef PTHREAD_POOL
#define PTHREAD_POOL
 
#include <pthread.h>
#include "config.h"

#define  MAX_PTHREADS  6
#define  MAX_JOBS     10

class job; 
class pthread_pool
{
public:
 
   pthread_t  threads[MAX_PTHREADS];
   job  *  front;   
   job  *  reac; 
   pthread_mutex_t mutex;
   pthread_cond_t  no_empty;
   
   int job_count;         //队列计数器

   int init();
   int add_work(void*(*function)(void *),void *arg);
   job* out_work();
   ~pthread_pool();
 
static void * p_function(void *);     
 

};

class job
{
public:
  void  *(*work_function)(void *);
  void  *arg;
  job * next; 
};

#endif
