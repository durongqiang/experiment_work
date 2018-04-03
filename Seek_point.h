#ifndef SEEK_POINT_H
#define SEEK_POINT_H
#include"Start_point.h"
#include<vector>
#include<string>
class Seek_point
{
public:
	Seek_point()=default;
	Seek_point(std::string, std::string, std::string);
	void print();
	std::vector<double> get_startpoint() { return startpoint; }
	void show_startpoint();
	~Seek_point();

private:
	std::string type;
	std::string file_path;
	std::vector<std::string> each_file_path;
	std::vector<std::vector<double> >total_tool_xyz;
	std::vector<std::vector<double> >total_really_xyz;
	std::vector<double> startpoint;
	void cal_total_tool_xyz(std::vector<std::vector<double> >&);
	void cal_total_really_xyz(std::string , std::vector<std::vector<double> >&);
	void cal_point();
};


#endif
