
#include "sock.h"




int sock::init() 
{   
    //创建监听描述符
  create_listen();
   
  epoll_fd = epoll_create(MAXEPOLLFD);
     
        
     
 
 

 return 0;
}
  
int sock::create_listen()
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
 return fd;
}

 