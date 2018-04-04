#include"Use_python.h"
#include<iostream>
#include<windows.h>  
#include<stdio.h> 
#include<sstream>
bool system_hide(char* CommandLine, float *a , float*b )
{
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
	int cnt = 0;
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
		if (a != NULL) {
			stemp >> *a;
		}
		if (b != NULL) {
			stemp >> *b;
		}
		//std::cout << *a << *b << std::endl;
		//int af;
		//std::stringstream stemp1;
		//stemp1 << buffer;
		//stemp1 >> af;
		//std::cout << af << std::endl;
		//打印内存区域，可以使用指针进行参数返回
		//Sleep(0.1);

	}
	return   TRUE;

}