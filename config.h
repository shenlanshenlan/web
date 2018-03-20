#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#define  CONFIGPATH "./config"

using namespace std;
class config { 
 public: 
    string  default_dir;
    int     listen_port;
    int     max_pthreads;
    char    cwd[256];
            config();
 virtual int init(); 
};
