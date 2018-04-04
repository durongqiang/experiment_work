#ifndef USECNN_H
#define USECNN_H
#include<map>
#include<string>
class UseCNN
{
public:
	UseCNN();
	UseCNN(std::string);
	void train_CNN(std::string, std::string="E:/savemodel/model.ckpt");
	~UseCNN();
	void predict(std::string);
	int  predict_result();
	int  get_type() { return type; }
private:
	std::map<int, std::string>type_dict;
	int type;
	int init_num = 0;
	void init_type_dict();
	bool use_py_cnn(char* , int &);
	bool system_hide1(char* );
};

#endif // !USECNN_H

