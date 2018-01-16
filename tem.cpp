#ifndef TEM
#define TEM
#include <iostream>
 
/*使用模板的文件不能独立编译
必须被包含于调用它的编译单中
并且必须位于调用之前
（可以先声明再，定义.意义不大）

 添加预编译宏防止重复包含

*/
namespace k1   //命名空间1
{
template <class T,class Y>   //模板函数
void c(T a,Y b)
{
 
 std::cout << a <<b<<std::endl;
}    


template<class A ,class B>   //模板类 声明
class  in
{ 
 public:
     class kk
     {
       int  a;
     };
   
   A    x;
   B    l;
     in();     
};
 
template<class A,class B>    //模板类 定义
   in<A,B>::in()             
{
  std::cout << "s";
}

 
}
#endif