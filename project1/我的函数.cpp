#include "myFunction.h"
#include <iostream>
#include <stack>
#include "stdio.h"
#include "math.h"
using namespace std;

int isp(char ch)    //��ȡ�����ز����� ch ��ջ�����ȼ�
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
int osp(char ch)  // ��ȡ�����ز����� ch ��ջ�����ȼ�
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
bool  cal( char op, double x, double y, double & r)   // ����r = x op y�� ����ɹ�������true.
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
void GetNextchar(char & ch)   // ������ı��ʽ�л�ȡһ���ַ�
{
	//ch = getchar();
	cin>>ch;
	return ;
}
bool isdigit(char ch)   // �ж�ch�Ƿ�Ϊ����0-9
{
	return ch>='0'&&ch<='9';
}
bool IsOperator(char ch)     //�ж�ch�Ƿ�Ϊ������
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
bool Get2Operands(stack<double> & opnd,  double &x, double &y)   //�Ӳ�����ջ��ȡ2��������
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