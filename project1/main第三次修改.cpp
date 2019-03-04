#include <iostream>
#include <string>
#include <stack>
#include "stdio.h"
#include "stdlib.h"
#include "myFunction.h"
using namespace std;

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




