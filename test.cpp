#include<iostream>
using namespace std;
#include<fstream>
#include"Base_function.h"
#include<vector>
#include"Start_point.h"
#include"Seek_point.h"
/*
#include<bitset>
#include<Eigen\dense>
#include<mat.h>
#include <Windows.h>
#include <opencv2/opencv.hpp>
using namespace cv;
*/

//采用CPP模式读取txt  
void TextRead_CPPmode()
{
	fstream f;
	f.open("C:\\Users\\Administrator\\Desktop\\m44", ios::in);
	//文件打开方式选项：  
	//　ios::in　　　　= 0x01,　//供读，文件不存在则创建(ifstream默认的打开方式)  
	//　ios::out　　　 = 0x02,　//供写，文件不存在则创建，若文件已存在则清空原内容(ofstream默认的打开方式)  
	//　ios::ate　　　 = 0x04,　//文件打开时，指针在文件最后。可改变指针的位置，常和in、out联合使用  
	//　ios::app　　　 = 0x08,　//供写，文件不存在则创建，若文件已存在则在原文件内容后写入新的内容，指针位置总在最后  
	//　ios::trunc　　 = 0x10,　//在读写前先将文件长度截断为0（默认）  
	//　ios::nocreate　= 0x20,　//文件不存在时产生错误，常和in或app联合使用  
	//　ios::noreplace = 0x40,　//文件存在时产生错误，常和out联合使用  
	//　ios::binary　　= 0x80　 //二进制格式文件  
	vector<int> index;
	vector<double> x_pos;
	vector<double> y_pos;
	if (!f)
	{
		cout << "打开文件出错" << endl;
		return;
	}
    cout << "mode为1，按字符读入并输出；mode为2，按行读入输出；mode为3，知道数据格式，按行读入并输出" << endl;
	int mode = 1;
	cin >> mode;
	if (1 == mode)
	{
		//按字节读入并输出  
		char ch;
		while (EOF != (ch = f.get()))
			cout << ch;
	}
	else if (2 == mode)
	{
		//按行读取，并显示  
		char line[128];
		int numBytes;
		f.getline(line, 128);
		cout << line << "\t" << endl;
		f.getline(line, 128);
		cout << line << "\t" << endl;
		f.seekg(0, 0);                           //跳过字节  
												 //seekg(绝对位置);　　　　　　//绝对移动，　　　　//输入流操作  
												 //seekg(相对位置,参照位置);　 //相对操作  
												 //tellg();                   //返回当前指针位置  
		while (!f.eof())
		{
			//使用eof()函数检测文件是否读结束  
			f.getline(line, 128);
			numBytes = f.gcount();      //使用gcount()获得实际读取的字节数  
			cout << line << "\t" << numBytes << "字节" << endl;
		}
	}
	else if (3 == mode)
	{
		//如果知道数据格式，可以直接用>>读入  
		int index_temp = 0;
		double x_pos_temp = 0, y_pos_temp = 0;
		while (!f.eof())
		{
			f >> index_temp >> x_pos_temp >> y_pos_temp;
			index.push_back(index_temp);
			x_pos.push_back(x_pos_temp);
			y_pos.push_back(y_pos_temp);
			cout << index_temp << "\t" << x_pos_temp << "\t" << y_pos_temp << endl;
		}
	}
	f.close();
}


int main(int argc, char* argv[]) {

	/*
	double a = 3.13, b = 12.34;
	vector<double> result;
	cal_tool_xyz(a, b,result);
	cout<<result[0]<<endl;
	cout << result[1] << endl;
	cout << result[2] << endl;
	*/
	//测试cal_tool_xyz函数
	/*
	std::vector<std::string> test_file;
	get_file_name(string("H:/焊缝起始点搜索法/V型/有间隙三点法"), test_file);
	int size = test_file.size();
	for (int i = 0; i < size; i++)
		     {
		         std::cout << test_file[i].c_str() << endl;
		     }
	*/

	/*
	Matrix<double, 2, 2> a,b ,c;
	a << 1, 2, 3, 4;
	b = a;
	c = a.adjoint()*b;
	std::cout << c << std::endl;
	*/
	Seek_point aseek ("V", "H:/焊缝起始点搜索法/V型/无间隙三点法", "坐标点获取.txt");
	aseek.print();
	aseek.show_startpoint();
	/*
// Name of MAT-file
const char* filename = "F:\\焊缝起始点搜索法\\V型\\无间隙三点法\\trajectory.mat";
// Open the MAT-file
MATFile* pMATFile = matOpen(filename, "r");

	// Define some variables for globally using
	int D = 0;			// Dimensions
	int M = 0;			// Rows
	int N = 0;			// Column
						///////////////////// mat2D /////////////////////
						// Get variable "mat2D" from MAT-file
	mxArray* p2D = matGetVariable(pMATFile, "mat2D");
	// Get real part of variable
	double* p2DReal = mxGetPr(p2D);
	// Get rows
	M = mxGetM(p2D);
	// Get Cols
	N = mxGetN(p2D);
	// Define a Mat to store data
	cv::Mat mat2D(M, N, CV_64FC1);
	// Storing...
	for (int i = 0; i < M; i++)
	{
		double* pData = mat2D.ptr<double>(i);
		for (int j = 0; j < N; j++)
			pData[j] = p2DReal[j*M + i];
	}

	// Show the storage mode of "mat2D" in mxArray
	cout << "mat2D in mxArray:\n";
	for (int k = 0; k < M*N; k++)
		cout << *(p2DReal++) << "\t";
	cout << "\n\n";

	// Show the storage mode of "mat2D" Mat
	cout << "mat2D in Mat:\n" << mat2D << "\n\n";
	
	*/
	system("pause");
	return 0;
	
}