#include <iostream>

using namespace std;



void ShowUserInterface();
int main(){
ShowUserInterface();
}


void ShowUserInterface(void ){//�û�����
	int number=0;
	char FileAddress;

	cout<<"1.ѹ���ļ�"<<endl;
	cout<<"2.��ѹ�ļ�"<<endl;
	cout<<"3.�˳�"<<endl;
	cout<<"�����������"<<endl;
	cin>>number;

	if (number==1){//����1����ѹ���ļ�
        cout<<"������Ŀ���ļ�·����"<<endl;
        cin>>FileAddress;
	}

	else if (number==2){//����2���н�ѹ�ļ�
        cout<<"������Ŀ���ļ�·����"<<endl;
        cin>>FileAddress;
	}

	else if(number==3) {
	}

    else {
        cout<<"�����������������룺"<<endl;
        return ShowUserInterface();
    }

}

/*------------------------------------------------------------------------------------------------*/

//����



