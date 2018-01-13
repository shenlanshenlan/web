 



#include "main.h"
 
 
void *work(void *); 
  
 
extern config conf;
extern pthread_pool pool;
extern sock    Sock;
int main() 
{ 
  
 try{
 
  pool.init();   // thread pool    
  Sock.init();   // work with epoll 
 }
 
catch(const char* err)
 {  
  cout<<err<<endl;    
 }

    return 0; 
}
  
 //=========================================================
 
 void *work(void *arg)    //pthread_work_test
 {  

     int   cli; 
     cli = *(int*)arg;
     http  obj(cli);


    cout<<"work"<<obj.version<<endl;
    









     /* int   cli; 
      char  buf[10240]; 
      int   n,file;                                                        // 解析协议
  

      cli = *(int*)arg;
      n = read(cli,buf,10240);                                                //获取请求 响应
      cout<<buf<<endl;
      memset(buf,0,10240);
      
       file = open("./html/a.html",O_RDONLY);
    
      n = read(file,buf,10240);
 
      write(cli,buf, n);*/
   
   return NULL ;
 }

/*
int pool_test()    //a test for pool 
{ 
   pool.init();
   int n;
   f= c;
  for ( ; ; )
  {  
      if((pool.add_work(f,NULL))==-1) 
        continue;
  }
 sleep(100);
} */   
