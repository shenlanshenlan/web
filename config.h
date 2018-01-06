
#ifndef _CONFIG_H
#define _CONFIG_H

 
#include <iostream>
#include <string>

using namespace std;


class config
{ 
 public: 
        
 virtual int init(){   return 0;} 
 
    string  page_file_path;
    int     listen_port;   

};
#endif