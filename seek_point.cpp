#include"Seek_point.h"
#include"Base_function.h"
#include<fstream>
#include<sstream>
#include<iostream>
Seek_point::Seek_point(std::string input_type, std::string input_file_path, std::string file_txt_path)
{
	type = input_type;
	file_path = input_file_path;
	get_file_name(file_path, each_file_path);
	cal_total_tool_xyz(total_tool_xyz);
	cal_total_really_xyz(file_txt_path, total_really_xyz);
	cal_point();

}


//����ÿ��ͼ�Ĺ�������ϵ�µ�����xyz�����������������ܵ�total_xyz�ڡ�
//����vector��Ƕ��vector������Ϊ�������xyz
void Seek_point::cal_total_tool_xyz(std::vector<std::vector<double> >&total_xyz) {
	std::size_t count = each_file_path.size();
	for (std::size_t i = 0; i < count; i++) {

		Start_point temp(type, each_file_path[i]);
		total_xyz.push_back(temp.get_tool_xyz());
	}

}


/*
��������ͼƬ������ȡ���Ľǵ����ʵ����ϵ�µ�xyz�������浽�൱��
����Ϊfile_name.txt��ʽ���൱�д洢����ʵ��������Ĵ洢��
�������ʵ����洢����
�������Ϊvoid
*/
void Seek_point::cal_total_really_xyz(std::string txt_path,
	                      std::vector<std::vector<double> >& total_really_xyz)
{
	std::string txtpath = file_path + "/" + txt_path;//����txt�ļ��ľ���·��
	std::fstream     f(txtpath);//����һ��fstream�ļ�������
	std::string      line; //��������ÿһ��
	int cnt = 0;
	while (getline(f, line))//���Զ���\n���з�ȥ�� 
	{
		if (line.empty())
			break;
		std::stringstream each_line(line);
		double x, y, z;
		each_line >> x >> y >> z;
		std::vector<double> temp_vector;//������Ƭxyz�洢��
		temp_vector.push_back(total_tool_xyz[cnt][0]+x);//��ʵ��x
		temp_vector.push_back(total_tool_xyz[cnt][1]+y);//��ʵ��y
		temp_vector.push_back(total_tool_xyz[cnt][2]+z);//��ʵ��z
		total_really_xyz.push_back(temp_vector);//������Ƭxyz�洢�����൱��
		++cnt;
	}
};

void Seek_point::print() {
	std::size_t count = each_file_path.size();
	for (std::size_t i = 0; i < count; i++) {
		std::cout<<each_file_path[i]<<std::endl;

	}
	for (std::size_t i = 0; i < count; i++) {
		std::cout <<"��"<<i+1<<"�����"
			<<"x: "<<total_tool_xyz[i][0] <<"  "
			<< "y: " << total_tool_xyz[i][1]<<"  "
			<< "z: " << total_tool_xyz[i][2]
			<< std::endl;

	}


};


/*
����ô�ʵ�鵱�еĺ�����ʼ��λ��
����洢��startpoint�ڴ洢
*/
void Seek_point::cal_point() {
	std::vector<double> p1, p2, p3;
	if (total_really_xyz.size() == 6) {
		for (int i = 0; i < 3; i++)
			p1.push_back((total_really_xyz[0][i] + total_really_xyz[1][i]) / 2);
		for (int i = 0; i < 3; i++)
			p2.push_back((total_really_xyz[2][i] + total_really_xyz[3][i]) / 2);
		for (int i = 0; i < 3; i++)
			p3.push_back((total_really_xyz[4][i] + total_really_xyz[5][i]) / 2);
	}
	else {
		p1 = total_really_xyz[0];
		p2 = total_really_xyz[1];
		p3 = total_really_xyz[2];
	}
	if ((p1[0] - p2[0]) != 0) {
		double k = (p1[1] - p2[1]) - (p1[0] - p2[0]);
		double b = p1[1] - k * p1[0];
		double x0 = (p3[0] / k + p3[1] - b) / (k + 1 / k);
		double y0 = k * x0 + b;
		double z01 = ((p1[2] - p2[2]) / (p1[1] - p2[1]))*(y0 - p1[1]) + p1[2];
		double z02 = ((p1[2] - p2[2]) / (p1[0] - p2[0]))*(x0 - p1[0]) + p1[2];
		double z0 = (z01 + z02) / 2;
		startpoint.push_back(x0);
		startpoint.push_back(y0);
		startpoint.push_back(z0);
	}
	else {
		double x0 = p1[0];
		double y0 = p3[1];
		double z0 = ((p3[1] - p1[1]) / (p2[1] - p1[1]))*(p2[2] - p1[2]) + p1[2];
		startpoint.push_back(x0);
		startpoint.push_back(y0);
		startpoint.push_back(z0);
	}
};


void Seek_point::show_startpoint() {
	std::cout << "Ѱλ�õ���ʼ���ӵ�����Ϊ   "
		<< "x: " << startpoint[0] << "  "
		<< "y: " << startpoint[1] << "  "
		<< "z: " << startpoint[2]
		<< std::endl;
};

Seek_point::~Seek_point()
{
}