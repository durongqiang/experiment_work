#include<iostream>
using namespace std;
#include<fstream>
#include"Base_function.h"
#include<vector>
#include"Start_point.h"
#include"Seek_point.h"
#include"UseCNN.h"
#include"Segement.h"
#include<sstream>
/*
#include<bitset>
#include<Eigen\dense>
#include<mat.h>
#include <Windows.h>
#include <opencv2/opencv.hpp>
using namespace cv;
*/

int main(int argc, char* argv[]) {

	//Seek_point aseek ("V", "H:/������ʼ��������/V��/�޼�϶���㷨", "������ȡ.txt");
	//aseek.print();
	//aseek.show_startpoint();


	//UseCNN tcnn("H:/cnnԭʼͼƬ/���ڴ�׺�/2018_0227_20_45_21_548.bmp");
	//tcnn.train_CNN("H:/cnnԭʼͼƬ", "E:/savemodel/testmodel/model.ckpt");
	//tcnn.predict_result();
	//std::string s;
	//std::cin >>  s ;
	//tcnn.predict(s);
	//tcnn.predict_result();

	Segement aft("C:/Users/Administrator/Desktop/2018_0227_20_42_20_968.bmp");
	aft.print_toolxyz();
	aft.imgage_type();
	system("pause");
	return 0;
	
}