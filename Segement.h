#ifndef SEGEMENT_H
#define SEGEMENT_H
#include<string>
#include<map>
#include<vector>
class Segement
{
public:
	Segement(std::string);
	int imgage_type();
	void print_toolxyz();
	~Segement();

private:
	std::string image_path;
	int weld_type;
	double u, v;
	std::map<int, std::string> weld_type_dict;
	std::vector<double> img_xyz;
	void init_weld_type_dict();
	bool get_weld_type(char* , int&, double&, double&);
	
};


#endif
