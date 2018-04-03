#include"Start_point.h"
#include<iostream>
#include"Base_function.h"
#include<time.h>

/*
初始化单张图片，构建单张图片的图片类
*/
Start_point::Start_point(std::string input_type, std::string input_file_name)
{
	type = input_type;
	file_name = input_file_name;
	get_uv();
	cal_tool_xyz(u, v, tool_xyz);
};


/*
得到图片给当中的图像坐标u和v的值
*/
void Start_point::get_uv() {

	std::string temp = "python  C:/Users/Administrator/Desktop/cal_uv.py  " + file_name + " " + type;
	char* input_char;
	const int len = temp.length();
	input_char = new char[len + 1];
	strcpy(input_char, temp.c_str());
	//std::cout << input_char << std::endl;
	//测试命令行，检测测试的结果是否准确
	
	/*
	clock_t startTime, endTime;
	startTime = clock();
	endTime = clock();
	std::cout << "Totle Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC
		<< "s" << std::endl;
	*/
	//运行时间检测函数
	system_hide(input_char, &u, &v);

	//std::cout << u << std::endl;
	//std::cout << v << std::endl;
	delete[] input_char;
};

//输出图像的uv坐标
void Start_point::show_uv() {
	std::cout << "图像的u: " << u << std::endl;
	std::cout << "图像的v: " << v << std::endl;

}

//得到图像的工具坐标下真实坐标
std::vector<double> Start_point::get_tool_xyz() 
{
	return tool_xyz;
};

////输出角点工具坐标下坐标
void Start_point::show_xyz() {

	std::cout << "图像的工具坐标系下坐标X: " << tool_xyz[0] << std::endl;
	std::cout << "图像的工具坐标系下坐标Y: " << tool_xyz[1] << std::endl;
	std::cout << "图像的工具坐标系下坐标Z: " << tool_xyz[2] << std::endl;
};


Start_point::~Start_point()
{

}