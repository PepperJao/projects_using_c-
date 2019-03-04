#include "myFunction.h"
#include <iostream>
#include <stack>
#include "stdio.h"
#include "math.h"
using namespace std;

int isp(char ch)    //获取并返回操作符 ch 的栈内优先级
{
	int priority = 0;
	switch(ch){
		case '=': priority=0;break;
		case '+': priority=3;break;
		case '-': priority=3;break;
		case '*': priority=5;break;
		case '/': priority=5;break;
		case '%': priority=5;break;
		case '(': priority=1;break;
		case ')': priority=8;break;
		case '^': priority=7;break;
		case '&': priority=7;break;
		default : cout<<ch<<"is not a OPERATOR!"<<endl;	
		          priority=-1;
	} 
    return priority;
}
int osp(char ch)  // 获取并返回操作符 ch 的栈外优先级
{
	int priority = 0;
	switch(ch){
		case '=': priority=0;break;
		case '+': priority=2;break;
		case '-': priority=2;break;
		case '*': priority=4;break;
		case '/': priority=4;break;
		case '%': priority=4;break;
		case '(': priority=8;break;
		case ')': priority=1;break;
		case '^': priority=6;break;
		case '&': priority=6;break;
		default : cout<<ch<<"is not a OPERATOR!"<<endl;		     
		          priority=-1;
	} 
    return priority;
}
bool  cal( char op, double x, double y, double & r)   // 计算r = x op y， 计算成功，返回true.
{
	bool flag=false;
	switch(op){
		case '+': r = x + y;
		          flag=true;
				  break;
		case '-': r = x - y;
		          flag=true;
				  break;
		case '*': r = x * y;
		          flag=true;
				  break;
		case '/': r = x / y;
		          flag=true;
				  break;
		case '%': r = (int)x % (int)y;
		          flag=true;
				  break;
				  
		case '^': r = pow(x,y);
		          flag=true;
				  break;
		case '&': r = pow(x,1/y);
		          flag=true;
				  break;
		default : r = r;
	} 
    return flag;
}
void GetNextchar(char & ch)   // 从输入的表达式中获取一个字符
{
	//ch = getchar();
	cin>>ch;
	return ;
}
bool isdigit(char ch)   // 判断ch是否为数字0-9
{
	return ch>='0'&&ch<='9';
}
bool IsOperator(char ch)     //判断ch是否为操作符
{
	bool flag = false;
	switch(ch){
		case '=': 
		case '+': 
		case '-': 
		case '*': 
		case '/': 
		case '%': 
		case '(': 
		case ')': 
		case '^': 
		case '&': flag = true;
		          break;
		default : flag = false;
	} 
    return flag;
}
bool Get2Operands(stack<double> & opnd,  double &x, double &y)   //从操作数栈中取2个操作数
{
	bool flag = true;
	if (!opnd.empty()){
		y = opnd.top();
		opnd.pop();
		if(!opnd.empty()){
			x = opnd.top();
		    opnd.pop();
		}
		else{
			flag = false;
		}	
	}
	else{
		flag = false;
	} 
	return flag;
}