
 
#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <fcntl.h>
     
#include "config.h"

extern config conf;

#define ELEMENT 30
#define MSGLEN  8192
#define MAXPAGELEN 4096

#define E(a) printf(a);
 
using namespace std; 
 
class http 
{
public:
    int cli;
    
    char   * req_type;
    char   * url;
    char   * version;
      
    char  *elements[ELEMENT];
 
 

    char    msg[MSGLEN]; 
    char    res_msg[MSGLEN];
   

        http(int);
    int response();
 


private:




};

 #endif