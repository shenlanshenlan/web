
#include "fun.h"

 

pth_info * creat_pth_info()
{   int i;
    for(i=0;i< MAXTHREAD;i++)
    {
       if(AR[i].tid == 0)
       {
      return &AR[i];
       }
    }
    return NULL;
}
 