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

//����CPPģʽ��ȡtxt  
void TextRead_CPPmode()
{
	fstream f;
	f.open("C:\\Users\\Administrator\\Desktop\\m44", ios::in);
	//�ļ��򿪷�ʽѡ�  
	//��ios::in��������= 0x01,��//�������ļ��������򴴽�(ifstreamĬ�ϵĴ򿪷�ʽ)  
	//��ios::out������ = 0x02,��//��д���ļ��������򴴽������ļ��Ѵ��������ԭ����(ofstreamĬ�ϵĴ򿪷�ʽ)  
	//��ios::ate������ = 0x04,��//�ļ���ʱ��ָ�����ļ���󡣿ɸı�ָ���λ�ã�����in��out����ʹ��  
	//��ios::app������ = 0x08,��//��д���ļ��������򴴽������ļ��Ѵ�������ԭ�ļ����ݺ�д���µ����ݣ�ָ��λ���������  
	//��ios::trunc���� = 0x10,��//�ڶ�дǰ�Ƚ��ļ����Ƚض�Ϊ0��Ĭ�ϣ�  
	//��ios::nocreate��= 0x20,��//�ļ�������ʱ�������󣬳���in��app����ʹ��  
	//��ios::noreplace = 0x40,��//�ļ�����ʱ�������󣬳���out����ʹ��  
	//��ios::binary����= 0x80�� //�����Ƹ�ʽ�ļ�  
	vector<int> index;
	vector<double> x_pos;
	vector<double> y_pos;
	if (!f)
	{
		cout << "���ļ�����" << endl;
		return;
	}
    cout << "modeΪ1�����ַ����벢�����modeΪ2�����ж��������modeΪ3��֪�����ݸ�ʽ�����ж��벢���" << endl;
	int mode = 1;
	cin >> mode;
	if (1 == mode)
	{
		//���ֽڶ��벢���  
		char ch;
		while (EOF != (ch = f.get()))
			cout << ch;
	}
	else if (2 == mode)
	{
		//���ж�ȡ������ʾ  
		char line[128];
		int numBytes;
		f.getline(line, 128);
		cout << line << "\t" << endl;
		f.getline(line, 128);
		cout << line << "\t" << endl;
		f.seekg(0, 0);                           //�����ֽ�  
												 //seekg(����λ��);������������//�����ƶ�����������//����������  
												 //seekg(���λ��,����λ��);�� //��Բ���  
												 //tellg();                   //���ص�ǰָ��λ��  
		while (!f.eof())
		{
			//ʹ��eof()��������ļ��Ƿ������  
			f.getline(line, 128);
			numBytes = f.gcount();      //ʹ��gcount()���ʵ�ʶ�ȡ���ֽ���  
			cout << line << "\t" << numBytes << "�ֽ�" << endl;
		}
	}
	else if (3 == mode)
	{
		//���֪�����ݸ�ʽ������ֱ����>>����  
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
	//����cal_tool_xyz����
	/*
	std::vector<std::string> test_file;
	get_file_name(string("H:/������ʼ��������/V��/�м�϶���㷨"), test_file);
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
	Seek_point aseek ("V", "H:/������ʼ��������/V��/�޼�϶���㷨", "������ȡ.txt");
	aseek.print();
	aseek.show_startpoint();
	/*
// Name of MAT-file
const char* filename = "F:\\������ʼ��������\\V��\\�޼�϶���㷨\\trajectory.mat";
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