#ifndef  _MY_FUNCTION_
#define  _MY_FUNCTION_
#include <stack>
using namespace std;
int isp(char ch);    //获取并返回操作符 ch 的栈内优先级
int osp(char ch);   // 获取并返回操作符 ch 的栈外优先级
bool  cal(char op, double x, double y, double & r);   // 计算r = x op y， 计算成功，返回true.
void GetNextchar(char & ch);   // 从输入的表达式中获取一个字符
bool isdigit(char ch);     // 判断ch是否为数字0-9
bool IsOperator(char ch);     //判断ch是否为操作符
bool Get2Operands(stack<double> & opnd,  double &x, double &y);  //从操作数栈中取2个操作数
#endif

