
#ifndef _CONFIG_H
#define _CONFIG_H

#define CONFIGPATH "./config"
 
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
using namespace std;


class config 
{ 
 public: 
  
    string  default_dir;
    int     listen_port;
    int     max_pthreads;
               
            config();
 virtual int init(); 

};
#endif