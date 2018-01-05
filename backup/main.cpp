
#include "main.h"
 

 

/******************全局对象***************/
conf  _conf;                     //c++中全局变量的初始化 早于main函数
_socket _socket(&_conf);         //初始化网络配置
int      listenfd;               //监听描述符
int   file_port = 9812;
transmission *_T;


struct port_table
{
   int  port;
   int i;
};
port_table  TB[100]; 
pth_info    AR[MAXTHREAD]; 
 
/***********主函数*********/
int main()
{          
    signal(SIGPIPE,for_SIGPIPE);
    memset(AR,0,sizeof(AR));
    listenfd = _socket.get_sock_fd();   //创建套接字 描述符  
    int connfd;
    int err;
    sockaddr_in cliaddr;
    socklen_t   clilen;
    memset(TB,-1,sizeof(TB));
  for(   ;   ;  ) { 
    connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen); 
     if( fork() != 0 )
     {
          cout<<"processID:"<<getpid()<<"begin"<<endl;
          close(listenfd);

    // 返回一个已经链接的链接
    // 改为 多种并发服务器
   
      transmission    T(connfd);              //    对象
       _T = &T;
      share_dir       DIR;                    //    目录对象
      interaction     I(&T);                  //    传输对象
      file            F;                      //    文件对象
    
      T.send((char *)"/",1); 

      char   _buf[1024];     // (重建路径) 临时缓冲区
    /*******交互**********/ 
      for(  ;  ;  )
      {   
         I.recvrequest();    
          memset(  _buf,0,1024);  
         switch(I.mask)
         {
    case 0:                        // make dir
                    memset(  _buf,0,1024);
                    strcat(  _buf,_conf.file_share_path);
                    strcat(  _buf,I.request+6); 
                   
                    err =   F.makedir(  _buf);
                 if(err == 0)
                {
                   T.send((char *)"ok",2);
                }
                else
                {
                  T.send((char *)"err",3);
                }

                   break;
    case 1:
                   cout<<"mask 1\n";
                   break ;
    case 2:                  // request dir
                
                memset(  _buf,0,1024);
                strcat(  _buf,_conf.file_share_path);
                strcat(  _buf,I.request+4); 
                DIR.setpath(  _buf);
                T.send(DIR.dir,DIR.dir_len);
               break; 
    case 3:                   //exit
               goto quit;
               break;
    case 4:                            
         //   rmdir("/home/k/share/u");
           
                memset(  _buf,0,1024);
                strcat(  _buf,_conf.file_share_path);
                strcat(  _buf,I.request+6); 
                
                err =   F.removedir(  _buf); 
             if(err == 0)
              {
               T.send((char *)"ok",2);
              }
                else
              {
                  T.send((char *)"err",3);
              }
                break;
    case 5:     //移除文件
             
           
            strcat(  _buf,_conf.file_share_path);
            strcat(  _buf,I.request+3); 
 
            err =   F.remove1(  _buf); 
         if(err == 0) 
          {
           T.send((char *)"ok",2);
          }
            else
          {
              T.send((char *)"err",3);
          } 
            break;

    case 6:                      //download
              

            // 确定文件文件存在
                memset(  _buf,0,1024);
                strcat(  _buf,_conf.file_share_path);
                strcat(  _buf,I.request+9); 
                if( F.f_is_exist(_buf)  == 0  )
            {   
                int  fd;  
                pthread_t  tid;   
                
                char  parameter[1024];
                  memset(parameter,0,1024);            
                  strcat(parameter,_buf);  
               pthread_create(&tid,NULL,F.fsend,parameter);  //线程创建
             break;
                 }else{
                   T.send((char*)"111 exist",9);
                   break;
                 }
       
          break;
    case 7:
                memset(  _buf,0,1024);
                strcat(  _buf,_conf.file_share_path);
                strcat(  _buf,I.request+11); 
                 
                _buf[strlen(_buf)-1]='\0';  
             if( F.f_is_exist(_buf)  == 0  )
                {  
                  T.send((char *)"file create failed",18); 
                }else
                { 
                  int  filefd;
                  
                  filefd = creat(_buf,S_IRUSR|S_IWUSR);
                  if(filefd<0)
                  {
                     T.send((char *)"file create failed",18);
                     break;
                  }
                  filefd = open(_buf,O_WRONLY,S_IWUSR);
                      if(filefd<0)
                  {
                     T.send((char *)"file create failed",18);
                     break;
                  }
             
                  pthread_t  tid;                        
                  char  parameter[8];                            
                  strcat(parameter,_buf);  
                  int port = gettb();
               
                  *(int*)parameter = port;
                  *(int*)(parameter+4) = filefd;
        pthread_create(&tid,NULL,F.frecv,parameter);  //线程创建   
                  

                }  
       break;
    case-1:
            goto quit;

       }
   }
     quit:  
       {   
          cout<<"processID:"<<getpid()<<"end"<<endl; 
           close(connfd);
          _exit(1);   
       }
     }else{ 
       close(connfd);
       continue;
     }
   }
}
int gettb()
{  
  int i;
  for(i = 0;i<100;i++)
   {  if(TB[i].i ==-1)
       {  
          TB[i].i = true;
          TB[i].port =file_port+i; 
          return  file_port+i;
        } 
        
      }    
      return -1; 
}
int freetb(int port)
{  int n= port -file_port;
  if(n<0)
   return -1;
   TB[n].i= false;
   return 0;
  }
  
  int create_connect( int port ){
     int fd;
     int err; 
     struct sockaddr_in addr;
     addr.sin_family = AF_INET;
     addr.sin_port = htons(port);
     addr.sin_addr.s_addr = htonl(INADDR_ANY);
     fd= socket(AF_INET, SOCK_STREAM, 0);
    
    //  cout<<fd; 输出当前描述符
     err = bind(fd,(struct sockaddr *)&addr,sizeof(addr));
     if(err <0)
     {cout<<"bind err\n"<<endl; 
      return -1;
     }
     listen(fd,20);
     return fd;
    }

void for_SIGPIPE(int n)//该信号引起线程被终止
{ 
  pthread_cancel(pthread_self());
}
void atexit(void *p){
 
    int *f,*c;
   
     f =(int*)p;
     c =(int*)(f+1);
    close(*f);
    close(*c); 
cout<<"pthread quit"<<endl;
}