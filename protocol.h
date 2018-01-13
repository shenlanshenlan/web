
 
#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <iostream>
#include <unistd.h>

using namespace std;
 
class http 
{
public:
    int cli;
         
    char   * req_type;
    char   * url;
    char   * version;

    char   head[512]; 
    void   *req_date;

    char  res_head[512];
    void      *res_date;

        http(int);
    int response(){};


private:




};

 #endif