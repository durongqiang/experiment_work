#include"UseCNN.h"
#include<iostream>
#include<windows.h>  
#include<stdio.h> 
#include<sstream>
//��ʼ���ڲ������ֵ�
void UseCNN::init_type_dict() {
	type_dict.emplace(0, "��ߺ���");
	type_dict.emplace(1, "��ͨλ������");
	type_dict.emplace(2, "���ڴ�׺�");
	type_dict.emplace(3, "��϶����");
};

//����cnnģ���ļ�������cnnģ�͵���Ԥ����ͼƬ����
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
	//�ؼ����裬CreateProcess�����������������MSDN  

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

		//buffer�о���ִ�еĽ�������Ա��浽�ı���Ҳ����ֱ�����
		stemp << buffer;

		//�����ַ����ļ��������뻺�����Ļ������洢
		std::stringstream stemp1;
		stemp1 << buffer;
		stemp1 >> out_type;
		//std::cout << out_type << std::endl;
		//��ӡ�ڴ����򣬿���ʹ��ָ����в�������
		//Sleep(0.1);

	}
	return   TRUE;

}

//ʹ��CNNģ�ͽ���Ԥ�⣬ģ���Ѿ�����Ĭ����Ĭ��Ϊ��E:/savemodel/model.ckpt
//���ģ�Ͳ���Ĭ���ļ�����use_cnn_model.py�ļ������޸�
//���use_cnn_model.py·�������޸ģ����滻�����������C:/Users/Administrator/Desktop/use_cnn_model.py
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


//����CNN��ѵ������
void UseCNN::train_CNN(std::string train_file_path, std::string save_model_path) {
	std::cout << "ѵ��ģ����Ҫ���ļ�·���ʹ洢ģ�͵�·��" << std::endl
		     << "�洢ģ�͵�·����Ҫ��.ckpt�ļ����ͽ�β�����Բ�����洢��ַ��" << std::endl
		     << "Ĭ��Ϊ��E:/savemodel/model.ckpt" << std::endl;
	std::string ttest = "python  C:/Users/Administrator/Desktop/train_cnn.py  " + train_file_path +"  "+ save_model_path;
	char* input_char1;
	const int len = ttest.length();
	input_char1 = new char[len + 1];
	strcpy(input_char1, ttest.c_str());
	std::cout << "����ģ�͵�ѵ����ʱ���ܾ�" << std::endl;
	//����ģ�͵�ѵ����ʱ���ܾ�
	if(system_hide1(input_char1))
		std::cout<<"ģ���Ѿ�ѵ����"<<std::endl;
	delete[] input_char1;

};

//���г�ʼ����δ�����ļ�·������Ҫ��������
UseCNN::UseCNN() {
	init_type_dict();
}

/*
����ģ�͵�ѵ����Ҫ�õ�����py�ļ������̵��д�ӡ��ģ��ѵ���Ĺ��̾�����ʱ��Ƚϳ�
������Ҫ��ӡ�м�������������˽�ģ��ѵ��ʱ��
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
	//�ؼ����裬CreateProcess�����������������MSDN  
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

		//buffer�о���ִ�еĽ�������Ա��浽�ı���Ҳ����ֱ�����

		std::cout << buffer << std::endl;
		//��ӡ�ڴ����򣬿���ʹ��ָ����в�������
		Sleep(10);

	}
	return   TRUE;

};

//���е�����Ƭ�Ľ��Ԥ��
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

//�õ�Ԥ���������и�ֵ
int  UseCNN::predict_result() {
	if (init_num) {
		std::cout << "ͼƬԤ����Ϊ��" << type_dict[type] << std::endl;
		return type;
	}
	else
		std::cout << "δ��ʼ��UseCNN,��Ҫ����һ����Ƭ����Ԥ��" << std::endl;
	    //throw exception1
};

UseCNN::~UseCNN()
{
}

