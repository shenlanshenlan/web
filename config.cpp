
#include "config.h"

config  conf;

config::config() 
{
 init();
}
      
int config::init()
{
   fstream  conf,pagedir;
   string   content,value;
   int      index;
 
  
   conf.open(CONFIGPATH);   
  
     if(conf.good())        
   { 
     while(1)                   //init 
     { 
        conf>>content;
        if(content.find("default_dir") != -1)   //
           {              
             index = content.find('=');        
             default_dir = content.substr(index+1);
           }
        if(content.find("max_pthreads") != -1)   //
           {  
             index = content.find('=');
             value = content.substr(index+1);
             max_pthreads = atoi(value.data() );  
           }    
 
           //... ... more
        
        if(conf.eof())
        { 
          conf.close();
          break;          
        }
      }  
   }
   else
   {    
     cout<<"config open failed"<<endl;
    _exit(0); 
   }
   

    memset(cwd,0,256);
    getcwd(cwd,256);
 
      string a;
      a=default_dir;
      default_dir = cwd;
      default_dir = default_dir +a; 
    
      DIR * pdir;

 

   pdir = opendir((const char *)default_dir.data());

    if(pdir != NULL)
    {
       cout<<"default_dir "<<default_dir<<endl;
       closedir(pdir);
    }else
    {   
        mkdir((const char *)default_dir.data(),S_IRUSR|S_IWUSR|S_IXUSR);
        cout<<"create default_dir "<<default_dir<<endl; 
    }
   cout<<"config init "<<endl;
return 0;
}