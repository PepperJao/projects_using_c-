#ifndef  _MY_FUNCTION_
#define  _MY_FUNCTION_
#include <stack>
using namespace std;
int isp(char ch);    //��ȡ�����ز����� ch ��ջ�����ȼ�
int osp(char ch);   // ��ȡ�����ز����� ch ��ջ�����ȼ�
bool  cal(char op, double x, double y, double & r);   // ����r = x op y�� ����ɹ�������true.
void GetNextchar(char & ch);   // ������ı��ʽ�л�ȡһ���ַ�
bool isdigit(char ch);     // �ж�ch�Ƿ�Ϊ����0-9
bool IsOperator(char ch);     //�ж�ch�Ƿ�Ϊ������
bool Get2Operands(stack<double> & opnd,  double &x, double &y);  //�Ӳ�����ջ��ȡ2��������
#endif

