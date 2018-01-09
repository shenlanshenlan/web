
#ifndef _CONFIG_H
#define _CONFIG_H

#define CONFIPATH "./config"
 
#include <iostream>
#include <string>

using namespace std;


class config
{ 
 public: 
        
             config();
 virtual int init(); 
 
    string  page_file_path;
    int     listen_port;
    int     max_pthreads;   

};
#endif