#include<iostream>
using namespace std;
#include<fstream>
#include"Base_function.h"
#include<vector>
#include"Start_point.h"
#include"Seek_point.h"
#include"UseCNN.h"
/*
#include<bitset>
#include<Eigen\dense>
#include<mat.h>
#include <Windows.h>
#include <opencv2/opencv.hpp>
using namespace cv;
*/

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


	//Seek_point aseek ("V", "H:/������ʼ��������/V��/�޼�϶���㷨", "������ȡ.txt");
	//aseek.print();
	//aseek.show_startpoint();



	//std::string image_name;
	//std::cin >> image_name;
	//std::string ttest = "python  C:/Users/Administrator/Desktop/use_cnn_model.py  " + image_name ;
	//char* input_char1;
	//const int len = ttest.length();
	//input_char1 = new char[len + 1];
	//strcpy(input_char1, ttest.c_str());
	//system_hide(input_char1);
	//delete[] input_char1;

	UseCNN tcnn("H:/cnnԭʼͼƬ/���ڴ�׺�/2018_0227_20_45_21_548.bmp");
	//tcnn.train_CNN("H:/cnnԭʼͼƬ", "E:/savemodel/testmodel/model.ckpt");
	tcnn.predict_result();
	std::string s;
	std::cin >>  s ;
	tcnn.predict(s);
	tcnn.predict_result();
	system("pause");
	return 0;
	
}