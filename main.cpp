#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream> 
#include "config.h"
#include "sock.h"
#include "pthread_pool.h"
#include "protocol.h" 

#define   PATHLEN 100
#define E(a) printf(a);
extern config conf;
extern pthread_pool pool;
extern sock    Sock;

int main() {  
 try{ 
  pool.init();   // thread pool    
  Sock.init();   // work with epoll 
 }
catch(const char* err) {  
  cout<<err<<endl;    
 }
return 0; 
}
void *work(void *arg) {  
 int   cli; 
 cli = *(int*)arg;
 k::request     msg(cli);
 k::response    res(&msg);
return NULL ;
}

 
