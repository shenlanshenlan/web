
#include "config.h"

config  conf;

config::config() 
{
 init();
}
      
int config::init()
{
   fstream  conf;
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
          break;          
          conf.close();
        }
      }  
   }
   else
   {    
     cout<<"config open failed"<<endl;
    _exit(0); 
   }
   
   cout<<"config init "<<endl;
return 0;
}