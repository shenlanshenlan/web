
#ifndef _CONFIG_H
#define _CONFIG_H

#define CONFIGPATH "./config"
 
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

      

using namespace std;


class config 
{ 
 public: 
  
    string  default_dir;
    int     listen_port;
    int     max_pthreads;
    char    cwd[256];
    
               
            config();
 virtual int init(); 

};
#endif