#include <iostream>

using namespace std;



void ShowUserInterface();
int main(){
ShowUserInterface();
}


void ShowUserInterface(void ){//用户界面
	int number=0;
	char FileAddress;

	cout<<"1.压缩文件"<<endl;
	cout<<"2.解压文件"<<endl;
	cout<<"3.退出"<<endl;
	cout<<"请输入操作："<<endl;
	cin>>number;

	if (number==1){//输入1进行压缩文件
        cout<<"请输入目标文件路径："<<endl;
        cin>>FileAddress;
	}

	else if (number==2){//输入2进行解压文件
        cout<<"请输入目标文件路径："<<endl;
        cin>>FileAddress;
	}

	else if(number==3) {
	}

    else {
        cout<<"输入有误，请重新输入："<<endl;
        return ShowUserInterface();
    }

}

/*------------------------------------------------------------------------------------------------*/

//建堆



