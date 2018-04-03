#include"Base_function.h"
#include<Eigen\dense>
#include<mat.h>
#include<io.h>
/*ͨ��ͼ��������㹤������ϵ�µ����꣬
��m43��m44Ϊ�궨����
����Ϊ��double��ͼ������u��v
���Ϊ��double��vctor,�洢��Ϊ����ϵ����x��y��z
*/
void cal_tool_xyz(double u, double v, std::vector<double>&result) {

	using namespace Eigen;
	Matrix<double, 4, 3>m43, New_m43;
	Matrix<double, 4, 4>m44;
	Matrix<double, 3, 1>m31;

	//�߽ṹ��������궨�ڲ����ϲ�����
	m43 << -1.03208168e-01, -1.18476145e-04, 8.25233590e+01,
		5.40851309e-04, -1.03020266e-01, 6.30248343e+01,
		-5.46751724e-03, 1.62764007e-03, -1.94672484e+02,
		-3.58320966e-03, 1.29578320e-05, 1.00000000e+00;

	//���۱궨�������
	m44 << 7.98116382e-01, 7.30787175e-03, -6.02458992e-01, 1.22308280e+02,
		-4.16878553e-03, 9.99969484e-01, 6.60704341e-03, 6.59130406e+00,
		6.02488890e-01, -2.76166725e-03, 7.98122491e-01, -8.14920769e+01,
		0.00000000e+00, 0.00000000e+00, 0.00000000e+00, 1.00000000e+00;

	m31 << u, v, 1.00000;//��һ������
	New_m43 = m44 * m43;

	//����������result����
	result.push_back((New_m43 * m31)(0));
	result.push_back((New_m43 * m31)(1));
	result.push_back((New_m43 * m31)(2));
};

/*
ͨ��������ļ�·������ȡ�����ȫ���ļ���·������
����Ϊ���ļ��Ĵ�ŵ�ַ���ļ��У�����Ĭ�Ϻ�׺��Ϊ.bmp�ļ���ʽ
��������ڣ�����Ϊfiles�Ĵ���vector,�洢��Ϊ�����ļ�������
*/
 void get_file_name(std::string path, std::vector<std::string>& files, std::string postfix)
 {
	     //�ļ����  
	     intptr_t   hFile = 0;
	    //�ļ���Ϣ������һ���洢�ļ���Ϣ�Ľṹ��  
		    struct _finddata_t fileinfo;
	    std::string p;//�ַ��������·��
	    if ((hFile = _findfirst(p.assign(path).append("/*").append(postfix).c_str(), &fileinfo)) != -1)//�����ҳɹ��������
		    {
		        do
			         {
			             //�����Ŀ¼,����֮�����ļ����ڻ����ļ��У�  
				          if ((fileinfo.attrib &  _A_SUBDIR))
				            {
				                //�ļ���������"."&&�ļ���������".."
					                 //.��ʾ��ǰĿ¼
					                //..��ʾ��ǰĿ¼�ĸ�Ŀ¼
					                //�ж�ʱ�����߶�Ҫ���ԣ���Ȼ�����޵ݹ�������ȥ�ˣ�
					                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
										get_file_name(p.assign(path).append("/").append(fileinfo.name), files, postfix);
				           }
			            //�������,�����б�  
				            else
				            {
				                files.push_back(p.assign(path).append("/").append(fileinfo.name));
				            }
			        } while (_findnext(hFile, &fileinfo) == 0);
			         //_findclose������������
				        _findclose(hFile);
			     }
	}