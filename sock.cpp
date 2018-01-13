
#include "sock.h"


void * work(void *); 
void *(*work_run)(void *);

int err;
extern class pthread_pool pool;
sock  Sock;  

int sock::init() 
{   
   
   create_listen();
   
   memset(clients,-1,sizeof(clients)); 
  
   setnonblcoking(&listen_fd); 

   event.data.fd = listen_fd;
   event.events = EPOLLIN | EPOLLET;

   epoll_fd = epoll_create(MAXEPOLLFD);   //epoll

   if(epoll_fd < 0)
    throw("epoll_fd create err");
    err = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,listen_fd,&event);
   if(err <0)
    throw("epoll_ctl err");
    run();

 cout<<"sock_init "<<endl;
 return 0;
}

int sock::run() 
{   
   cout<<"sock running "<<endl;
    struct sockaddr addr;
           socklen_t len;  
      int  client;
 while(1)
  { 
      int i,n;
      
      n = epoll_wait(epoll_fd,events,MAXEPOLLFD,-1);
       
   for(i =0; i < n;i++)   
    { 
        
      if(events[i].data.fd == listen_fd) //new connected
        {       
             client=accept(listen_fd,&addr,&len); 
            if(client< 0)
 			  continue;
  
              setnonblcoking(&client);
              event.data.fd = client;
              event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;  
              epoll_ctl(epoll_fd,EPOLL_CTL_ADD,client,&event);                 
 							cli_add(client);
           
        } 
      else if(events[i].events & EPOLLRDHUP)  //closed
        {                  
            close(events[i].data.fd);              
            epoll_ctl(epoll_fd,EPOLL_CTL_DEL,events[i].data.fd,NULL);
 						cli_del(client);  
            cout<<"closed"<<endl;   
        }
      else  if(events[i].events & EPOLLIN  )   //can read
         {
             work_run = work;
             pool.add_work(work_run,get_cli_point(events[i].data.fd));
             cout<<"read"<<endl;
         }
      } 
  }
}

int sock::cli_add(int cli)    //save cli_add
{
   int i;
   for(i =0;i<MAXCLIENTS;i++)
	{  
	    if(clients[i] == -1)
	    { 
		clients[i] = cli;
		return 0;
	    }
	}
  return -1;
}
int sock::cli_del(int cli)
{ 
	int i;
  for(i=0;i<MAXCLIENTS;i++)
  	{
      if(clients[i] == cli)
       {
	 			 clients[i] =  -1;
	      return 0;
       }
    }
	return -1;	
}
int * sock::get_cli_point(int cli)
{   
   int i;
   for(i=0;i<MAXCLIENTS;i++)
   {
      if( clients[i]==cli)    
    		{ 
          return &clients[i];
				}
		}  	 
	return NULL;     
}	    

int sock::setnonblcoking(int * fd)
{ 
  int flags;

   flags = fcntl(*fd,F_GETFL,0);
   fcntl(*fd,F_SETFL,flags | O_NONBLOCK);
 return 0;
}

int sock::create_listen()  //return listen file descriptor 
{
     int fd;
     int err;  
     struct sockaddr_in addr;
     addr.sin_family = AF_INET;
     addr.sin_port = htons(PORT);
     addr.sin_addr.s_addr = htonl(INADDR_ANY);
     fd= socket(AF_INET, SOCK_STREAM, 0);
 
     err = bind(fd,(struct sockaddr *)&addr,sizeof(addr));
     if(err <0)
     { 
        throw("bind err");
     }
     err = listen(fd,20);
      if(err <0)
     { 
        throw("listen err");
     }
     listen_fd = fd;
     
     
 return fd;
}

 
