#pragma once
#include <pthread.h>
#include "config.h"
extern config conf;
#define  MAX_PTHREADS  8
#define  MAX_JOBS      1000000
 
class job; 
class pthread_pool {
public:
   pthread_t  threads[MAX_PTHREADS];
   job  *  point;   
   job  *  reac;   
   pthread_mutex_t mutex;
   pthread_cond_t  no_empty;
   
   int job_count; 
  
   int init();
   int create_pthread();
   int add_work(void*(*function)(void *),void *arg);
   job* out_work();
   ~pthread_pool();
 
static void * p_function(void *);
static void for_SIGPIPE(int n);     
};

class job {
public:
  void  *(*work_function)(void *);
  void  *arg;
  job * next; 
};

#endif

 
