


#include <iostream> 
#include <vector>
 //template   namespace  and  stl 
 

 #include "tem.cpp"   //template .h file

 namespace k1   //1命名空间k1
 { 
  void fun()
     { 
     
   std::cout<<"k1"<<std::endl;
      }
 }
namespace k2    //名空间k2
{
   void fun()
   {
   std::cout<<"k2"<<std::endl;
    }   
}

 

///////////////////////////////////////////////////////////////
int main() 
{  
   
using k1::c;    
    char f='g';
    int e = 10;
    c(e,f);         //模板函数调用

using k1::in;

   in<int,char>  da;    //实例
                        //此处的两个类型  指定了 class A 和 class B 的具体类型   
   in<int,char>  *ds;
   ds = new in<int,char>; //指针实例化  此处 <> 中的类型 必须和指针声明时的类型相同
 
   typedef in<double,char>   hh;  //特化的 in 类 作为类型
 
  
     using  std::vector;        //命名空间  使用std 的  vector
     vector<int>::iterator p;

     k1::in<int,int>::kk lp;    //详解  k1命名空间的 in类 的内嵌 类 kk  的对象 lp
    

   hh gg; 

//namespace
  
   k1::fun();
   k2::fun();
  

   return 0;
}  
 