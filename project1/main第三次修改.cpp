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
		cout<<"�Ƿ����(Y/N)?"<<endl;
		fflush(stdin);
	    ch=getchar();
	}while(ch == 'Y' || ch == 'y');
	return 0;   
}

void ShowUserInterface(void ){
	cout<<"----------��ӭʹ�ü��׼�����---------------------------------------"<<endl;
	cout<<"ʹ��˵����"<<endl;
	cout<<"���ʽ�ɰ�����"<<endl; 
	cout<<"1.��(+)����(-)����(*)����(/)����ģ��%�� ������(&)�ͳ˷�(^) �������"<<endl; 
	cout<<"2.���š�" <<endl<<endl;
	cout<<"��������ʽ���ԡ�=����β����" <<endl; 
}

void Calculator(void ){
	stack<double> OPND;   //  ������ջ���壻
    stack<char>   OPTR; //  ������ջ���壻
    char ch;
    OPTR.push('='); 
    char prior_char = '=';    //prior_char ��ʾ��ǰ�����ַ���ǰһ���ַ�����Ϊ��������ֵ'0'
    
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
			    cout<<"������ʽ�г��ַǷ��ַ�!"<<endl; 
			    return ; 
		     } 
			else {
				  //�±���һ��b��ʾ����������������ŵ���� 
				   if(( prior_char == '='|| prior_char =='(' ) && (ch=='+'||ch=='-')){
				      OPND.push(0);   
				   }
				   
				   if (isp(OPTR.top())<osp(ch)){ 
				       //ջ�����ȼ�����ջ�����ȼ�
					   //�������
					   OPTR.push(ch);
					   prior_char = ch; 
					   GetNextchar(ch); 
				   }
				   else{
					   	if(isp(OPTR.top()) > osp(ch)){//ջ�����ȼ�����վ�����ȼ� 
					   	   double x=0.0,y=0.0,r=0.0;
				           if(!Get2Operands(OPND,x,y)){
				           	  cout<<"���ʽ����"<<endl; 
				           	  return ; 
				           }
				           cal(OPTR.top(),x,y,r);				    
				           OPTR.pop(); 
				           OPND.push(r); 
					    }
					    else{//ջ�����ȼ�����ջ�����ȼ� 
					       OPTR.pop(); 
					       if(ch == ')') {
						       prior_char = ch; 
							   GetNextchar(ch);
						   } 
					    } 
				   } 
		   }
		if (OPTR.empty()){  
		  cout<<"������ʽ�д�!"<<endl;  
		  return ;  
		  }   
   }
	if(OPND.size()!= 1) { 
		cout<<"������ʽ�д�!"<<endl;
	  	return ; 
	} 
	cout<<OPND.top()<<endl;
	return ;
}




