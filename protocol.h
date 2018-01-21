
 
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
namespace k
{ 

using  namespace std;
 

#define ELEMENT 300
#define MSGLEN   18192
#define MAXPAGELEN  14096

#define E(a) printf(a);
 
 
class request
{
public:
    int cli;
    
    char   * req_type;
    char   * url;
    char   * data;
    char   * cli_addr;  

        request(int);  
private:
     char    *elements[ELEMENT]; 
     char    msg[MSGLEN]; 
}; 
 
 class response
{         
 public:   
    char    msg[MSGLEN]; 
    char    page[MAXPAGELEN];
  
              response(request*); 
         };  
 

 

}
 #endif