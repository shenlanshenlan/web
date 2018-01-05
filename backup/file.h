
/*****文件传输类****/

#ifndef _file_h
#define _file_h

#include "main.h" 
 
class  file    //  文件传输 
{ 
public:
 static    void*  fsend(void *);
 static    void*  frecv(void *);
     int  fread(char *path ,char *buf, int * len);
     int  makedir(char *path);
     int  removedir(char *path);
     int  remove1(char *path);
     int  f_is_exist(char *path);
     
private:

     char m_path[512];
     int  m_pathlen;
     int  setpath(char *p_path,int len);   
     int  m_open();
     
static  void *tr_file(void *p);

};


/*****目录类******/


class share_dir    //仅仅构造    目录路径及长度
{ 
public:
   char * dir_path;
   char   dir[1024];
   int    dir_len;
 
   void setpath(char * path);
private:
   int updata_dir(); 
};

struct pth_info
{  
    pthread_t  tid;
    char *  filename;
    
};
#endif
 

 