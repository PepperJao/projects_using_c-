#include <iostream>
#include <string>
#include <stack>
#include "stdio.h"
#include "stdlib.h"
#include "myFunction.h"
using namespace std;



using namespace std;

//获取并返回ch的栈内优先级
int isp (char ch)
{
	switch (ch)
    {
          case '#':
                 return 0;
          case '(':
                 return 1;
          case '+':
          case '-':
			  return 3;
          case '*':
          case '/':
          case '%':
               return 5;
          case ')':
                return 6;
     }
}


//获取并返回ch的栈外优先级
int osp (char ch)
{ switch (ch)
    {
           case '#':
                 return 0;
          case '(':
                 return 6;
          case '+':
          case '-':
                 return 2;
          case '*':
          case '/':
          case '%':
               return 4;
         case ')':
            return 1;
     }
}

//op是操作符，X.Y是从操作数栈里弹出来的两个数，计算出不同操作符情况下r的值
bool cal(char op,double x,double y,double&r)
{
	int l = 0;
	switch(op)
	{
	case '-':
		r = x-y;
		break;
    case '+':
		r = x+y;
		break;
	case '/':
		r = x/y;
		break;
	case '%':
		(int) l= (int)x%(int)y;
		r = (double)o;
		break;
	case '*':
		r = x*y;
		break;
	case '&':
		r = extract(x,y);
		break;
	case '^':
		r = pow(x,y);
		break;
	}
	return true
	
}

//从输入的表达式char中获取一个字符ch
void GetNextchar(char&ch)
{

}

//判断输入的操作数是否在0到9之间
bool isdigit(char ch)
{
	if (((int)ch>=0)&&((int)ch<=9))
		return true;
	else return false;

}

bool IsOperator(char ch)
{
	if((ch == '=')||(ch == '+')||(ch == '-')||(ch == '(')||(ch == ')')||(ch == '*')||(ch == '^')||(ch == '%')||(ch == '&')||(ch == '/'))
		return true;
	else return false;
}

void GetNextchar(char&ch)
{
	cin>>ch;
}
//从操作数栈里弹出头两个数字
void Get2Operands(LStack & opnd,double &x,double &y)
{
	if (!opnd.empty())
		x=opnd.top();
	    opend.pop();
		y=opnd.top();
        opend.pop();
		
   	else return ERROR

}




void ShowUserInterface(void );
void Calculator(void ); 
int main(int argc, char** argv) {
	char ch='0';
	do{
		system("cls");
		Calculator();
		cout<<"是否继续(Y/N)?"<<endl;
		fflush(stdin);
	    ch=getchar();
	}while(ch == 'Y' || ch == 'y');
	return 0;   
}

void ShowUserInterface(void ){
	cout<<"----------欢迎使用简易计算器---------------------------------------"<<endl;
	cout<<"使用说明："<<endl;
	cout<<"表达式可包含："<<endl; 
	cout<<"1.加(+)、减(-)、乘(*)、除(/)、求模（%） 、开方(&)和乘方(^) 运算符；"<<endl; 
	cout<<"2.括号。" <<endl<<endl;
	cout<<"请输入表达式（以“=”结尾）：" <<endl; 
}



void Calculator(void ){
	stack<double> OPND;   //  操作数栈定义；
    stack<char>   OPTR; //  操作符栈定义；
    char ch;
    OPTR.push('='); 
    char prior_char = '=';    //prior_char 表示当前处理字符的前一个字符，如为数，则其值'0'
    
    ShowUserInterface();
    GetNextchar(ch);  //OPTR.topValue(OPTR.top());
	while(OPTR.top()!= '=' || ch != '='){
		if(isdigit(ch)||ch=='.'){	
			cin.putback(ch);
			double operand=0.0;
			cin>>operand;  
			OPND.push(operand);
			prior_char='0'; 
			GetNextchar(ch); 
		 }
		else if(!IsOperator(ch)){ 
			    cout<<"表括达式中出现非法字符!"<<endl; 
			    return ; 
		     } 
			else {
				  //下边这一句b表示的是如果带有正负号的情况 
				   if(( prior_char == '='|| prior_char =='(' ) && (ch=='+'||ch=='-')){
				      OPND.push(0);   
				   }
				   
				   if (isp(OPTR.top())<osp(ch)){ 
				       //栈内优先级低于栈外优先级
					   //处理程序
					   OPTR.push(ch);
					   prior_char = ch; 
					   GetNextchar(ch); 
				   }
				   else{
					   	if(isp(OPTR.top()) > osp(ch)){//栈内优先级高于站外优先级 
					   	   double x=0.0,y=0.0,r=0.0;
				           if(!Get2Operands(OPND,x,y)){
				           	  cout<<"表达式有误！"<<endl; 
				           	  return ; 
				           }
				           cal(OPTR.top(),x,y,r);				    
				           OPTR.pop(); 
				           OPND.push(r); 
					    }
					    else{//栈内优先级等于栈外优先级 
					       OPTR.pop(); 
					       if(ch == ')') {
						       prior_char = ch; 
							   GetNextchar(ch);
						   } 
					    } 
				   } 
		   }
		if (OPTR.empty()){  
		  cout<<"表括达式有错!"<<endl;  
		  return ;  
		  }   
   }
	if(OPND.size()!= 1) { 
		cout<<"表括达式有错!"<<endl;
	  	return ; 
	} 
	cout<<OPND.top()<<endl;
	return ;
}
