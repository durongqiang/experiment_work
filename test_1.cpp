#include<iostream>
#include<windows.h>   
#include<string>
#include"Start_point.h"

int main(int argc,char* argv[])
{
	int i;
	Start_point class_test("V", "H:/焊缝起始点搜索法/V型/无间隙三点法/Laser0001.bmp");
	// float a1, b1;
	/*
	std::string buffer1 = "6.5 3.4\n";
	std::string b = "python C:/Users/Administrator/Desktop/cal_uv.py H:/焊缝起始点搜索法/V型/无间隙三点法/Laser0001.bmp V";
	char* c;
	const int len = b.length();
	c = new char[len + 1];
	strcpy(c, b.c_str());
	system_hide(c);
	delete[] c;
	*/
	//system("exit");
	//std::cout << a1 <<std::endl<< b1 << std::endl;
	class_test.show_uv();
	system("pause");

	return 0;
}