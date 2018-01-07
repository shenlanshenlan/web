


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


   pthread_create(&tid,NULL,p_fun,NULL);  //thread a
 
      for(int i =0;i<5;i++)  //create five thread b
         pthread_create(&tid,NULL,p_fun2,NULL);
   

   
   sleep(30);   //wait exit
  
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
        while(global != 2 )         // 条件测试如果为真 则进入等待(阻塞) 直到有信号发生
        {      
         cout<<"cond_wait"<<endl;
         pthread_cond_wait(&condition,&mutex);   
        }
    
    cout<<"1end"<<endl;           //否则 执行

  pthread_mutex_unlock(&mutex);
  return NULL;
}
void * p_fun2( void  *)   //改变条件
{     
   pthread_mutex_lock(&mutex);
    
   global--;
   cout<<"b "<<global<<endl;
   pthread_cond_signal(&condition); //send signal   //A
            //此时如果不解锁 等待线程将无法获取锁
   
   pthread_mutex_unlock(&mutex);

   pthread_cond_signal(&condition); //send signal   //B
 
  return NULL;
}



/*
* 问题   当 pthread_cond_wait() 函数从阻塞返回时  是否与其他线程 共同竞争mutex
*        如果是:  if wait 竞争不到锁时  将会错过对该次 <条件改变> 的检测及处理
*                竞争到锁的其他线程将 修改变量 并重新 cond_signal
*      
*        例：  global=0
*             线程 A 检测 global   while(a !=2) wait() 
*
*                 B 对   global=2  and cond_signal;
*                                    当global = 2  wait() 没有获得mutex 所以仍阻塞       
*                 C 对   global=4  and cond_signal;
*                                     此时 global == 4  导致 wait() 错过检测   
*/                
 