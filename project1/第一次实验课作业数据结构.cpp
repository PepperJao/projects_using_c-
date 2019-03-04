#include <iostream>
#include <string>
#include <stack>
#include "stdio.h"
#include "stdlib.h"
#include "myFunction.h"
using namespace std;



using namespace std;

//��ȡ������ch��ջ�����ȼ�
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


//��ȡ������ch��ջ�����ȼ�
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

//op�ǲ�������X.Y�ǴӲ�����ջ�ﵯ���������������������ͬ�����������r��ֵ
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

//������ı��ʽchar�л�ȡһ���ַ�ch
void GetNextchar(char&ch)
{

}

//�ж�����Ĳ������Ƿ���0��9֮��
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
//�Ӳ�����ջ�ﵯ��ͷ��������
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
