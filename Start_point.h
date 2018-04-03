#ifndef START_POINT_H
#define START_POINT_H
#include<string>
#include"Use_python.h"
#include<vector>
class Start_point
{
public:
	Start_point(std::string, std::string);
	~Start_point();
	void show_uv();
	std::vector<double> get_tool_xyz();
	void show_xyz();

private:
	std::string type;
	std::string file_name;
	float u=0, v=0;
	std::vector<double> tool_xyz;
	void get_uv();
};

#endif
