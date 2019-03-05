#include <iostream>
#include "stack"
#include "map"
using namespace std;

/*   ֻ����һλ�����ļӼ��˳��������   */

map<char, pair<int, int> > priority;    // ��Ÿ�����������ջ��ջ�����ȼ�,first��ջ��,second��ջ��

void MakePriority()        // ������������ȼ���
{
    priority.insert(make_pair('#', make_pair(0, 0)));    // isp(#)=0, icp(#)=0
    priority.insert(make_pair('\n', make_pair(0, 0)));   // isp(\n)=0, icp(\n)=0  ���ʽ��β��'#'��'\n'����,��������ʡ�Ա��ʽĩβ�Ľ�����'#'
    priority.insert(make_pair('(', make_pair(1, 6)));    // isp(()=1, icp(()=6
    priority.insert(make_pair('*', make_pair(5, 4)));    // isp(*)=5, icp(*)=4
    priority.insert(make_pair('/', make_pair(5, 4)));    // isp(/)=5, icp(/)=4
    priority.insert(make_pair('%', make_pair(5, 4)));    // isp(%)=5, icp(%)=4
    priority.insert(make_pair('+', make_pair(3, 2)));    // isp(+)=3, icp(+)=2
    priority.insert(make_pair('-', make_pair(3, 2)));    // isp(-)=3, icp(-)=2
    priority.insert(make_pair(')', make_pair(6, 1)));    // isp())=6, icp())=1
}

