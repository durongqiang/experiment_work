#include"Base_function.h"
#include<Eigen\dense>
#include<mat.h>
#include<io.h>
/*通过图像坐标计算工具坐标系下的坐标，
其m43和m44为标定矩阵
输入为：double型图像坐标u、v
输出为：double型vctor,存储的为工具系坐标x，y，z
*/
void cal_tool_xyz(double u, double v, std::vector<double>&result) {

	using namespace Eigen;
	Matrix<double, 4, 3>m43, New_m43;
	Matrix<double, 4, 4>m44;
	Matrix<double, 3, 1>m31;

	//线结构光与相机标定内参数合并矩阵
	m43 << -1.03208168e-01, -1.18476145e-04, 8.25233590e+01,
		5.40851309e-04, -1.03020266e-01, 6.30248343e+01,
		-5.46751724e-03, 1.62764007e-03, -1.94672484e+02,
		-3.58320966e-03, 1.29578320e-05, 1.00000000e+00;

	//手眼标定结果矩阵
	m44 << 7.98116382e-01, 7.30787175e-03, -6.02458992e-01, 1.22308280e+02,
		-4.16878553e-03, 9.99969484e-01, 6.60704341e-03, 6.59130406e+00,
		6.02488890e-01, -2.76166725e-03, 7.98122491e-01, -8.14920769e+01,
		0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 1.00000000e+00;

	m31 << u, v, 1.00000;//归一化矩阵
	New_m43 = m44 * m43;

	//将结果保存进result当中
	result.push_back((New_m43 * m31)(0));
	result.push_back((New_m43 * m31)(1));
	result.push_back((New_m43 * m31)(2));
};

/*
通过输入的文件路径来获取里面的全部文件的路径名，
输入为：文件的存放地址的文件夹，当中默认后缀名为.bmp文件格式
输出内容在：名字为files的传入vector,存储的为各个文件的名字
*/
 void get_file_name(std::string path, std::vector<std::string>& files, std::string postfix)
 {
	     //文件句柄  
	     intptr_t   hFile = 0;
	    //文件信息，声明一个存储文件信息的结构体  
		    struct _finddata_t fileinfo;
	    std::string p;//字符串，存放路径
	    if ((hFile = _findfirst(p.assign(path).append("/*").append(postfix).c_str(), &fileinfo)) != -1)//若查找成功，则进入
		    {
		        do
			         {
			             //如果是目录,迭代之（即文件夹内还有文件夹）  
				          if ((fileinfo.attrib &  _A_SUBDIR))
				            {
				                //文件名不等于"."&&文件名不等于".."
					                 //.表示当前目录
					                //..表示当前目录的父目录
					                //判断时，两者都要忽略，不然就无限递归跳不出去了！
					                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
										get_file_name(p.assign(path).append("/").append(fileinfo.name), files, postfix);
				           }
			            //如果不是,加入列表  
				            else
				            {
				                files.push_back(p.assign(path).append("/").append(fileinfo.name));
				            }
			        } while (_findnext(hFile, &fileinfo) == 0);
			         //_findclose函数结束查找
				        _findclose(hFile);
			     }
	}