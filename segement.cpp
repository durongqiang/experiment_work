#include"Segement.h"
#include"Base_function.h"
#include<windows.h>  
#include<stdio.h> 
#include<sstream>
#include<iostream>

//构建 分类字典
void Segement::init_weld_type_dict() {
	weld_type_dict.emplace(3, "V型焊缝");
	weld_type_dict.emplace(2, "角型焊缝");
	weld_type_dict.emplace(1, "对接焊缝");
	weld_type_dict.emplace(0, "搭接焊缝");
};

//调用segment.py模型文件，对其图片进行分割
bool Segement::get_weld_type(char* CommandLine, int & out_type,double&u,double&v) {
		SECURITY_ATTRIBUTES   sa;
		HANDLE   hRead, hWrite;
		std::stringstream stemp;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = TRUE;
		if (!CreatePipe(&hRead, &hWrite, &sa, 0))
		{
			return   FALSE;
		}
		STARTUPINFO   si;
		PROCESS_INFORMATION   pi;
		si.cb = sizeof(STARTUPINFO);
		GetStartupInfo(&si);
		si.hStdError = hWrite;
		si.hStdOutput = hWrite;
		si.wShowWindow = SW_HIDE;
		si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
		//关键步骤，CreateProcess函数参数意义请查阅MSDN  

		if (!CreateProcess(NULL, CommandLine, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
		{
			return   FALSE;
		}
		CloseHandle(hWrite);
		char   buffer[4096] = { 0 };
		DWORD   bytesRead;
		while (true)
		{

			memset(buffer, 0, strlen(buffer));
			if (ReadFile(hRead, buffer, 4096, &bytesRead, NULL) == NULL)
				break;

			//buffer中就是执行的结果，可以保存到文本，也可以直接输出
			stemp << buffer;

			//采用字符流文件进行输入缓冲区的缓冲结果存储
			std::stringstream stemp1;
			stemp1 << buffer;
			stemp1 >> out_type>>u>>v;
			//std::cout << out_type << std::endl;
			//打印内存区域，可以使用指针进行参数返回
			//Sleep(0.1);

		}
		return   TRUE;
};


Segement::Segement(std::string input_path)
{
	init_weld_type_dict();

	image_path = input_path;
	std::string segementPy = "python  C:/Users/Administrator/Desktop/segment.py  " + image_path;
	char* input_img_char;
	const int len = segementPy.length();
	input_img_char = new char[len + 1];
	strcpy(input_img_char, segementPy.c_str());
	get_weld_type(input_img_char,  weld_type,u,v);
	delete[] input_img_char;

	cal_tool_xyz(u, v, img_xyz);
}

//得到图片分割的识别类型
int Segement::imgage_type() {
	std::cout << "图片识别类型为：" << 
		weld_type_dict[weld_type]<< std::endl;
	return weld_type;
}

void Segement::print_toolxyz() {
	if (!img_xyz.empty()) {
		std::cout << "工作坐标系下坐标为" <<std::endl
			<< "x：" << img_xyz[0]
			<< "   y：" << img_xyz[1]
			<< "   z：" << img_xyz[2]
			<< std::endl;
	}
}
Segement::~Segement()
{

}