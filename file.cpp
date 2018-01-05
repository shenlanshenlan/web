


#include "file.h"
  
 extern   transmission *_T;

void * file::fsend(void * path)
{   
    
    int   n;  
    int   filefd;
    int   sockfd; 
    int   connfd;
    int   buflen=FILEBUF;
    char  buf[FILEBUF];
 
    pth_info * info;
    info = creat_pth_info();
    info->filename =(char *)path ;
    info->tid = pthread_self();
    
    //获取文件长度信息
    unsigned int filelen=0;
    signal(SIGPIPE,for_SIGPIPE); 
    struct stat file;
    if(stat((char*)path,&file)==-1)
     cout<<"stat failed"<<endl;
    
    if(S_ISREG(file.st_mode)) //普通文件
    {   
        filelen = file.st_size;
          
     memset(buf,0,1024);
          unsigned int * l;
          int    * p;   
          p = (int *)buf;
         *p = gettb();  
          l =(unsigned int *)++p;         
          *l =filelen;  
         _T->send(buf,8);     //发送端口号和文件长度
 
      filefd = open((char*)path,O_RDONLY);
      sockfd = create_connect(*(int*)buf);
       
    sockaddr_in cliaddr;
    socklen_t   clilen;
 connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen); 
 char  parameter[8];
      *(int *)parameter=connfd; 
      *(int *)(parameter+4)=filefd; 
  pthread_cleanup_push(atexit,parameter);  //处理函数
  for( ; ; )
    {  
 
        n = read(filefd,buf,buflen); 
        if(n==0 || n== -1)
       { 
        cout<<"finish";   
        break;
       }   
      write(connfd,buf,n);       
    } 
   
    close(filefd);
    close(sockfd);
    info->tid = 0;
     return NULL; 
    pthread_cleanup_pop(0);
    }
    else
    {
        _T->send((char*)"222 exist",9);
        return NULL;
    }     
   
    }
void* file::frecv(void * p){
      
     
      int port,filefd,sockfd,len,connfd,n;
      char * parameter;
      char buf[FILEBUF];
  
      parameter =(char *)p;
      port = *(int *)parameter;
      filefd = *(int *)(parameter+4);
      sockfd = create_connect( port);
     
   
       
         sockaddr_in cliaddr;
         socklen_t   clilen;  
     _T->send((char *)&port,4);
 connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
    cout<<"t5"<<endl; 
     cout<<"[message] uploading... ..."<<endl;
       for(  ;   ; ) 
       {
           n = read(connfd,buf,FILEBUF);
            if(n == 0 )
               break;      
          
           write(filefd,buf,n);
        }
      close(filefd);
      close(sockfd);
      freetb(port);
      cout<<"[message] upload finish"<<endl;
    return NULL;
  }



int file::m_open()
{  
     int fd;
     fd= open(m_path,O_RDONLY);
     if(fd<0)
     {
       cout<<"file open failed\n";
        
       return -1;
     }
      else
     {
     
       return fd;    
     }
}
int file::fread(char *path,char *buf,int *len)
{   
    int filefd;
    int n;
    setpath(path,strlen(path));

    if((filefd = m_open()) < 0 )
    return -1;  
     
    n = read(filefd,buf,*len);
    *len = n;
    return 0;
}
int  file::setpath(char *p_path,int len)
{ 
     memset(m_path,0,512);
     strcpy(m_path,p_path); 
     m_pathlen = strlen(m_path);
     if(m_pathlen<1)
      return -1;
      else 
      return 0;   
}

int file::makedir(char *path)
{ 
    return   mkdir(path,S_IRUSR|S_IWUSR|S_IXUSR);
}
int file::removedir(char *path)
{ 
    return   rmdir(path);
}
int file::remove1(char *path) 
{
    return   remove(path);     
}     

int file::f_is_exist(char *path)    
{   
    int err = open(path,O_RDONLY);
     if(err == -1)
     { close(err);
        
      return  -1;  
     }      
      else 
      { 
      
      close(err);  
     return  0;

      }
}

/**************dir***************/

int share_dir::updata_dir()  //传输目录
{     DIR * p_dir;
      struct dirent   * _dp;
      int n;
 
      memset(dir,0,1024);
       p_dir = opendir(dir_path);
      if(p_dir == NULL)
       { 
          strcpy(dir,(char *)"path open failed"); 
          cout<<"path open failed";
          dir_len =16;
          closedir(p_dir);
          return -1;    
       }
    for( ; ;)
    {
        _dp= readdir(p_dir);

       if(_dp == NULL)
          break;
    
       n = strlen(_dp->d_name);  
       strcat(dir,_dp->d_name);
       strcat(dir,"\n");     
    }
    dir_len = strlen(dir);
    closedir(p_dir);
    return 0;
}

void share_dir ::setpath(char *path)
{  
    dir_path = path;
    updata_dir();
}

////////////////////////////////
 

