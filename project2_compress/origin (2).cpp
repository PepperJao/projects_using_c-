#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
#include <algorithm>
#include <time.h>
using namespace std;


typedef long long LL;
const int FILE_LENGTH = 1000;
const long long MAX_MEMORY = 3 * 1024 * 1024;//每次从文件读取的最大位数
const int KIND_OF_CHARACTER = 260;//number of kinds of character
const int HUFFMAN_CODE_LENGTH = 1000;//哈夫曼编码的最大长度
int OFFSET = 20;//the position of the size of original file in compressed file
int nBits = 8;//store compress file in 8 bits
char FileAddress[FILE_LENGTH];

void CountKinds(); //for test
int BuildHuffmanTree();
int GetCompressInformation();
void DecompressFile();
void CompressFile(const char *filePath, const char *outPutFilePath, int numberOfNode);
void BitToInt(ofstream &outPut, char *HTstr, LL len);
int compression();
int decompression();
LL originalFileSize; //源文件大小
int numberOfNode;   //字符种类数
int bitsAdded;


struct Node {
    char c; // character
    int parent, lChild, rChild;//children node
    int iNode; //the serial number of node
    LL number; //number of corresponding character
    friend bool operator < (Node a, Node b) {
        return a.number > b.number;
    }
    char Huffmancode[HUFFMAN_CODE_LENGTH]; //bits string
}node[KIND_OF_CHARACTER];

char HuffmanCode[KIND_OF_CHARACTER][HUFFMAN_CODE_LENGTH];
//LL characters[KIND_OF_CHARACTER];



int main() {

    int number=0;

	cout<<"1.压缩文件"<<endl;
	cout<<"2.解压文件"<<endl;
	cout<<"3.退出"<<endl;
	cout<<"请输入操作："<<endl;
	cin>>number;

	if (number==1){//输入1进行压缩文件
        cout<<"请输入目标文件路径："<<endl;
        cin>>FileAddress;
        compression();
	}

	else if (number==2){//输入2进行解压文件
        cout<<"请输入目标文件路径："<<endl;
        cin>>FileAddress;
        decompression();
	}

	else if(number==3) {
	}

    else {
        cout<<"输入有误，请重新输入："<<endl;
        return main();
    }
}




int compression(){

    //扫描文件以计算每个字符的频率。
    char filePath[FILE_LENGTH];
    strcpy(filePath, FileAddress);//将文件名赋给char数组
    //char filePath[FILE_LENGTH] = "graph.txt";

    char compressFilePath[FILE_LENGTH] = "result.txt";

    ifstream readIn;
    readIn.open(filePath, ios::binary);//二进制方式打开
    if (readIn.is_open() == 0) {
        cout << "OPEN FAILED!" << endl;
        exit(0);
    }
     //获取文件大小

    readIn.seekg(0, ios::end);
    LL fileSize = (LL)readIn.tellg();
    readIn.seekg(0, ios::beg);
    cout<<"fileSize" <<fileSize<<endl;
    //read data in batches, 每次读取MAX_MEMORY 个字符数
    int nTimes = (int)(fileSize / MAX_MEMORY);
    if (fileSize % MAX_MEMORY != 0) nTimes++;
    int kindsOfCharacter = 0;
    cout<<nTimes<<endl;
    for (int i = 1; i <= nTimes; i++) {
        char *str = (char *)calloc(1, (MAX_MEMORY+10)*sizeof(char));

        LL numberOfCharacter = MAX_MEMORY;
        if (i == nTimes) {
            numberOfCharacter = fileSize % MAX_MEMORY;
        }
        readIn.read(str, numberOfCharacter * sizeof(char));
        str[numberOfCharacter] = '\0';
        cout<<strlen(str)<<endl;

        //count the frequency of each character.
        int lenStr = strlen(str);
        for (LL j = 0; j < lenStr; j++) {
            node[str[j]].number++;
            node[str[j]].c = str[j];
        }

        free(str);
    }


    //建造 Huffman tree
    int numberOfNode = BuildHuffmanTree();

    //用哈夫曼编码压缩文件
    CompressFile(filePath, compressFilePath, numberOfNode);
    //outPut.close();
   // readIn.close();
   }

int BuildHuffmanTree(){//压缩文件创建哈夫曼树

    Node* HT = (Node *)malloc((2 * KIND_OF_CHARACTER) * sizeof(Node));//apply 2 * KIND_OF_CHARACTER 存储哈夫曼树的节点

    priority_queue<Node> q;//将所有字符放入优先级队列中
    int  numberOfNode = 0;
    for (int i = 0; i < KIND_OF_CHARACTER; i++) {
        if (node[i].number != 0) {
            node[i].iNode = numberOfNode;
            node[i].c = i;
            q.push(node[i]);
            HT[numberOfNode] = node[i];
            numberOfNode++;
        }
    }
    cout << numberOfNode << endl;
    int jNode = numberOfNode;
    while (q.size() > 1){

        Node leftNode = q.top();//获取两个最小权重节点并设置它们的父节点
        q.pop();
        Node rightNode = q.top();
        q.pop();
        //cout <<" ##"<< leftNode.number <<endl;
        //cout <<" **"<< rightNode.number <<endl;
        int l = leftNode.iNode;
        int r = rightNode.iNode;
        HT[l].parent = jNode;
        HT[r].parent = jNode;
        //set parent's  information
        HT[jNode].c = ' ';
        HT[jNode].iNode = jNode;
        HT[jNode].lChild = l;
        HT[jNode].rChild = r;
        HT[jNode].number = leftNode.number + rightNode.number;
        q.push(HT[jNode]);
        jNode++;
    }
    HT[jNode-1].parent = -1;
   /* for (int i = 0; i < jNode; i++){
        cout << i << " " << HT[i].c <<  " " << HT[i].number<< endl;
    }*/
    //get each character's Huffman code
    for (int i = 0; i < numberOfNode; i++) {
        int k = 0;
        int l = i;
        char ch = HT[i].c;
        for (int j = HT[i].parent; j != -1; j = HT[j].parent) {
            if (HT[j].lChild == l) {
                HuffmanCode[ch][k] = '0';
            }
            else {
                HuffmanCode[ch][k] = '1';
            }
            l = j;
            k++;
        }
        //反转霍夫曼码
        for (int j = 0; j < k / 2; j++) {
            char temp = HuffmanCode[ch][j];
            HuffmanCode[ch][j] = HuffmanCode[ch][k-1-j];
            HuffmanCode[ch][k-1-j] = temp;
        }
        HuffmanCode[ch][k] = '\0';
        cout << ch << " " <<HuffmanCode[ch] << endl;

    }
    cout<<numberOfNode<<endl;
    free(HT);
    return numberOfNode;
}


void CompressFile(const char *filePath, const char *outPutFilePath, int numberOfNode){
    //再次在输入文件中扫描字符
    ifstream readIn;
    readIn.open(filePath, ios::binary);
    if (readIn.is_open() == 0) {
        cout << "OPEN FAILED!" << endl;
        exit(0);
    }

    //write Huffman code file
    //Information: number of bits added, OFFSET, size of original file. the number of kinds of character
    ofstream outPut;
    outPut.open(outPutFilePath, ios::binary);
    if (outPut.is_open() == 0) {
        cout << "OPEN FAILED!" << endl;
        exit(0);
    }

    //get size of file
    readIn.seekg(0, ios::end);
    LL fileSize = (LL)readIn.tellg();
    readIn.seekg(0, ios::beg);
    //write some information in compressed file

    outPut.seekp(OFFSET, ios::beg);
    outPut.write((char *)&fileSize, sizeof(LL));
    outPut.write((char *)&numberOfNode, sizeof(int));
    //record the character and its Huffman code
    for (int i = 0; i < KIND_OF_CHARACTER; i++) {
        if (node[i].number != 0) {
            outPut.write((char *)&i, sizeof(char));
            int bits = strlen(HuffmanCode[i]);
            outPut.write((char *)&bits, sizeof(int));
            outPut.write((char *)&HuffmanCode[i], bits*sizeof(char));
        }
    }


    //read data in batches, 每次读取 MAX_MEMORY characters and encode
    int nTimes = (int)(fileSize / MAX_MEMORY);
    if (fileSize % MAX_MEMORY != 0) nTimes++;
    int kindsOfCharacter = 0;
    char *HTstr = (char *)calloc(1, (MAX_MEMORY+HUFFMAN_CODE_LENGTH)*sizeof(char));
    int len = 0;
    LL lenT = 0;
    for (int i = 1; i <= nTimes; i++) {
        char *str = (char *)calloc(1, (MAX_MEMORY+10)*sizeof(char));
        LL numberOfCharacter = MAX_MEMORY;
        if (i == nTimes) {
            numberOfCharacter = fileSize % MAX_MEMORY;
        }
        readIn.read(str, numberOfCharacter * sizeof(char));
        str[numberOfCharacter] = '\0';
        for (LL j = 0; j < numberOfCharacter; j++) {
            char ch = str[j];
            lenT += strlen(HuffmanCode[ch]);
            strcpy(HTstr+len, HuffmanCode[ch]);
            len += strlen(HuffmanCode[ch]);

            //write compressed file in batches
            //when the length of encode string is greater than limited memory
            if (len > MAX_MEMORY) {
               // cout<<"****"<<endl;
                LL leftBits = len % nBits;
                LL changeLength = len - leftBits;
                BitToInt(outPut, HTstr, changeLength);

                //if no left bits, no need to keep it.
                strcpy(HTstr,  HTstr+changeLength);
                len = strlen(HTstr);
            }
        }
        free(str);
    }
    //cout<<strlen(HTstr)<<" "<<HTstr<<endl;
    //if there are left bits, change int integer
    if (len != 0) {
        BitToInt(outPut, HTstr, len);
        //store tail???
    }
    free(HTstr);
    readIn.close();
    outPut.close();
}


void DecompressFile(ifstream &readIn, ofstream &writeOut, int maxEncodingLength){
	//获取已压缩文件大小
	streampos curPos = readIn.tellg();
	readIn.seekg(0, ios::end);
	LL compressedFileSize = (LL)(readIn.tellg() - curPos);
	readIn.seekg(curPos, ios::beg);
	cout << "size of compressed file : " << compressedFileSize << endl;
	//read data in batches, each time read MAX_MEMORY characters
	int nTimes = (int)(compressedFileSize / MAX_MEMORY);
	if (compressedFileSize % MAX_MEMORY != 0) nTimes++;
	char *str = (char *)calloc(1, (MAX_MEMORY + HUFFMAN_CODE_LENGTH)* sizeof(char));
	int lenOfChar = 0;
	for (int j = 1; j <= nTimes; j++) {
		LL numberOfCharacter = MAX_MEMORY;
		if (j == nTimes) {
			numberOfCharacter = compressedFileSize % MAX_MEMORY;
		}
		char *strTemp = (char *)calloc(1, (2*HUFFMAN_CODE_LENGTH) * sizeof(char));
		char *buf = (char *)calloc(1, (MAX_MEMORY + HUFFMAN_CODE_LENGTH)* sizeof(char));

		readIn.read(buf, numberOfCharacter * sizeof(char));
		//cout<<buf<<endl;
		//printf("%d\n", ascII);
        int lenOfStrTemp = 0;
		for (int k = 0; k < numberOfCharacter; k++) {
			// convert it to binary bits
			unsigned char ascII = buf[k];
			char huffmanString[3*nBits];

			for (int i = nBits - 1; i >= 0; i--) {
				huffmanString[i] = ascII % 2 + '0';
				ascII = ascII / 2;
			}
			//if read last character, then minus bits which is added
			if ((j == nTimes) && (k == numberOfCharacter - 1)) {
               // printf("ascII:%d\n", ascII);
				nBits = nBits - bitsAdded;
			}
			huffmanString[nBits] = '\0';

			// cout<<huffmanString<<endl;
			strcpy(strTemp + lenOfStrTemp, huffmanString);
			lenOfStrTemp += strlen(huffmanString);

			//convert bit to char
			LL comparePosition = 0;
			while (1) {
				bool flag = false;
				for (int z = 0; z < numberOfNode; z++) {
					//if(strlen(node[z].Huffmancode) > strlen(strcmp)) continue;
					int lenHuffmanCode = strlen(node[z].Huffmancode);
					if (!memcmp(node[z].Huffmancode, strTemp, lenHuffmanCode)) {
						str[lenOfChar] = node[z].c;
						str[lenOfChar+1] = '\0';
						lenOfChar ++;
						//cout<<"strTempF:"<<strTemp<<endl;

                        strcpy(strTemp, strTemp+lenHuffmanCode);
                        lenOfStrTemp = strlen(strTemp);

						//cout<<"strTemp:"<<strTemp<<endl;
						flag = true;
						break;
						//comparePosition += lenHuffmanCode;
					}
				}
				if (!flag || (lenOfStrTemp == 0)) break;
			}


			//如果STR的长度大于有限内存，则写入解压缩文件
			if (lenOfChar > MAX_MEMORY) {
				writeOut.write(str, lenOfChar * sizeof(char));
				//apply a new memory will result in crash
				//free(str);
				//char *str = (char *)calloc(1, (MAX_MEMORY + HUFFMAN_CODE_LENGTH)* sizeof(char));
				strcpy(str, "");
				lenOfChar = 0;
			}
		}
		free(buf);
		free(strTemp);
	}
	//cout<<str<<endl;
	if (lenOfChar != 0){
		writeOut.write(str, lenOfChar * sizeof(char));
		free(str);
	}
}



int GetCompressInformation(ifstream &readIn){
	readIn.read((char *)&bitsAdded, sizeof(int));
	readIn.read((char *)&OFFSET, sizeof(int));
	readIn.seekg(OFFSET, ios::beg);
	readIn.read((char *)&originalFileSize, sizeof(LL));
	readIn.read((char *)&numberOfNode, sizeof(int));
	cout << originalFileSize << " " << numberOfNode << endl;
	//记录字符及其霍夫曼编码
	int maxEncodingLength = 0;
	for (int i = 0; i < numberOfNode; i++) {
		readIn.read((char *)&node[i].c, sizeof(char));
		int bits;
		readIn.read((char *)&bits, sizeof(int));
		readIn.read((char *)&node[i].Huffmancode, bits*sizeof(char));
		node[i].Huffmancode[bits] = '\0';
		cout << node[i].c << " " << node[i].Huffmancode << endl;
		if (maxEncodingLength < strlen(node[i].Huffmancode)) {
			maxEncodingLength = strlen(node[i].Huffmancode);
		}
	}
	cout << " maxEncodingLength :" << maxEncodingLength << endl;
	return maxEncodingLength;
}






int decompression(){

    char compressFilePath[FILE_LENGTH];
    strcpy(compressFilePath, FileAddress);//将要解压文件名赋给char数组
	char decompressFilePath[FILE_LENGTH] = "decompressResult.txt";

	ifstream readIn;
	readIn.open(compressFilePath, ios::binary);//二进制方式打开
	if (readIn.is_open() == 0) {
		cout << "OPEN FAILED!" << endl;
		exit(0);
	}
	ofstream writeOut;
	writeOut.open(decompressFilePath, ios::binary);
	if (writeOut.is_open() == 0) {
		cout << "OPEN FAILED!" << endl;
		exit(0);
	}

	//获取压缩文件的信息
	int maxEncodingLength = GetCompressInformation(readIn);
	//解压文件
	DecompressFile(readIn, writeOut, maxEncodingLength);
	readIn.close();
	writeOut.close();
	return 0;
}




void BitToInt(ofstream &outPut, char* HTstr, LL len) {
    //add 0 to make the length of HTstr can be divide by 7
    int k = 0;
    if (len % nBits != 0) {
        int bitsToAdd = nBits - (len % nBits);
        streampos pos = outPut.tellp();
        outPut.seekp(0, ios::beg);
        outPut.write((char *)&bitsToAdd, sizeof(int));
        outPut.write((char *)&OFFSET, sizeof(int));
        outPut.seekp(pos, ios::beg);
        for (; k < bitsToAdd; k++){
            HTstr[len+k] = '0';
        }
        HTstr[len+k] = '\0';

    }
    //char *buf = (char *)calloc(1, MAX_MEMORY * sizeof(char));
    //convert bit to char
    int pow = 1<<(nBits - 1);
    int sum = 0;
    for (LL i = 0, j = 0; i < len+k && HTstr[i]; i++) {
        if (j == nBits){
            outPut.write((char *)&sum, sizeof(char));

            j = 0;
            sum = 0;
        }
        sum = sum + (HTstr[i]-'0') * (pow >> j);
        j++;
    }

   // outPut.write(buf, strlen(buf) * sizeof(char));
    outPut.write((char *)&sum, sizeof(char));
   // free(buf);
   // cout <<sum <<endl;
}


void CountKinds(){
    int kinds = 0;
    for (int i = 0; i < KIND_OF_CHARACTER; i++) {
        if (node[i].number != 0) {
                printf("%c ", node[i].c);
            cout << node[i].c << " " << node[i].number<<endl;
            kinds++;
        }
    }
    cout << kinds << endl; //76
}



