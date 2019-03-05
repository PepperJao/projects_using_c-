#include <iostream>
#include "stack"
#include "map"
using namespace std;

/*   只能求一位整数的加减乘除混合运算   */

map<char, pair<int, int> > priority;    // 存放各个操作符的栈内栈外优先级,first是栈内,second是栈外

void MakePriority()        // 构造运算符优先级表
{
    priority.insert(make_pair('#', make_pair(0, 0)));    // isp(#)=0, icp(#)=0
    priority.insert(make_pair('\n', make_pair(0, 0)));   // isp(\n)=0, icp(\n)=0  表达式结尾的'#'用'\n'代替,这样可以省略表达式末尾的结束符'#'
    priority.insert(make_pair('(', make_pair(1, 6)));    // isp(()=1, icp(()=6
    priority.insert(make_pair('*', make_pair(5, 4)));    // isp(*)=5, icp(*)=4
    priority.insert(make_pair('/', make_pair(5, 4)));    // isp(/)=5, icp(/)=4
    priority.insert(make_pair('%', make_pair(5, 4)));    // isp(%)=5, icp(%)=4
    priority.insert(make_pair('+', make_pair(3, 2)));    // isp(+)=3, icp(+)=2
    priority.insert(make_pair('-', make_pair(3, 2)));    // isp(-)=3, icp(-)=2
    priority.insert(make_pair(')', make_pair(6, 1)));    // isp())=6, icp())=1
}

