#include"Start_point.h"
#include<iostream>
#include"Base_function.h"
#include<time.h>

/*
��ʼ������ͼƬ����������ͼƬ��ͼƬ��
*/
Start_point::Start_point(std::string input_type, std::string input_file_name)
{
	type = input_type;
	file_name = input_file_name;
	get_uv();
	cal_tool_xyz(u, v, tool_xyz);
};


/*
�õ�ͼƬ�����е�ͼ������u��v��ֵ
*/
void Start_point::get_uv() {

	std::string temp = "python  C:/Users/Administrator/Desktop/cal_uv.py  " + file_name + " " + type;
	char* input_char;
	const int len = temp.length();
	input_char = new char[len + 1];
	strcpy(input_char, temp.c_str());
	//std::cout << input_char << std::endl;
	//���������У������ԵĽ���Ƿ�׼ȷ
	
	/*
	clock_t startTime, endTime;
	startTime = clock();
	endTime = clock();
	std::cout << "Totle Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC
		<< "s" << std::endl;
	*/
	//����ʱ���⺯��
	system_hide(input_char, &u, &v);

	//std::cout << u << std::endl;
	//std::cout << v << std::endl;
	delete[] input_char;
};

//���ͼ���uv����
void Start_point::show_uv() {
	std::cout << "ͼ���u: " << u << std::endl;
	std::cout << "ͼ���v: " << v << std::endl;

}

//�õ�ͼ��Ĺ�����������ʵ����
std::vector<double> Start_point::get_tool_xyz() 
{
	return tool_xyz;
};

////����ǵ㹤������������
void Start_point::show_xyz() {

	std::cout << "ͼ��Ĺ�������ϵ������X: " << tool_xyz[0] << std::endl;
	std::cout << "ͼ��Ĺ�������ϵ������Y: " << tool_xyz[1] << std::endl;
	std::cout << "ͼ��Ĺ�������ϵ������Z: " << tool_xyz[2] << std::endl;
};


Start_point::~Start_point()
{

}