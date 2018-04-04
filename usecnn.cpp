#include"UseCNN.h"
#include<iostream>
#include<windows.h>  
#include<stdio.h> 
#include<sstream>
//初始化内部类型字典
void UseCNN::init_type_dict() {
	type_dict.emplace(0, "错边焊缝");
	type_dict.emplace(1, "普通位置任意");
	type_dict.emplace(2, "存在打底焊");
	type_dict.emplace(3, "间隙过大");
};

//调用cnn模型文件，对其cnn模型调用预测器图片类型
bool UseCNN::use_py_cnn(char* CommandLine, int & out_type) {
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
		stemp1 >> out_type;
		//std::cout << out_type << std::endl;
		//打印内存区域，可以使用指针进行参数返回
		//Sleep(0.1);

	}
	return   TRUE;

}

//使用CNN模型进行预测，模型已经存在默认在默认为：E:/savemodel/model.ckpt
//如果模型不在默认文件，打开use_cnn_model.py文件进行修改
//如果use_cnn_model.py路径发生修改，请替换本函数里面的C:/Users/Administrator/Desktop/use_cnn_model.py
UseCNN::UseCNN(std::string img_path)
{
	init_type_dict();
	std::string ttest = "python  C:/Users/Administrator/Desktop/use_cnn_model.py  " + img_path ;
	char* input_char1;
	const int len = ttest.length();
	input_char1 = new char[len + 1];
	strcpy(input_char1, ttest.c_str());
	use_py_cnn(input_char1,type);
	init_num++;
	delete[] input_char1;
}


//进行CNN的训练过程
void UseCNN::train_CNN(std::string train_file_path, std::string save_model_path) {
	std::cout << "训练模型需要的文件路径和存储模型的路径" << std::endl
		     << "存储模型的路径需要以.ckpt文件类型结尾，可以不输入存储地址。" << std::endl
		     << "默认为：E:/savemodel/model.ckpt" << std::endl;
	std::string ttest = "python  C:/Users/Administrator/Desktop/train_cnn.py  " + train_file_path +"  "+ save_model_path;
	char* input_char1;
	const int len = ttest.length();
	input_char1 = new char[len + 1];
	strcpy(input_char1, ttest.c_str());
	std::cout << "进行模型的训练，时间会很久" << std::endl;
	//进行模型的训练，时间会很久
	if(system_hide1(input_char1))
		std::cout<<"模型已经训练好"<<std::endl;
	delete[] input_char1;

};

//进行初始化，未输入文件路径，需要后续输入
UseCNN::UseCNN() {
	init_type_dict();
}

/*
进行模型的训练需要用到调用py文件，过程当中打印出模型训练的过程经过，时间比较长
所以需要打印中间过程量，粗略了解模型训练时间
*/
bool UseCNN::system_hide1(char* CommandLine) {
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

		std::cout << buffer << std::endl;
		//打印内存区域，可以使用指针进行参数返回
		Sleep(10);

	}
	return   TRUE;

};

//进行单张照片的结果预测
void UseCNN::predict(std::string input_img_path) {
	init_type_dict();
	std::string ttest = "python  C:/Users/Administrator/Desktop/use_cnn_model.py  " + input_img_path;
	char* input_char1;
	const int len = ttest.length();
	input_char1 = new char[len + 1];
	strcpy(input_char1, ttest.c_str());
	use_py_cnn(input_char1, type);
	init_num++;
	delete[] input_char1;
}

//得到预测结果并进行赋值
int  UseCNN::predict_result() {
	if (init_num) {
		std::cout << "图片预测结果为：" << type_dict[type] << std::endl;
		return type;
	}
	else
		std::cout << "未初始化UseCNN,需要输入一张照片进行预测" << std::endl;
	    //throw exception1
};

UseCNN::~UseCNN()
{
}

