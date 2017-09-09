#ifndef _UTILLSTR_HPP__
#define _UTILLSTR_HPP__
#include <iostream> 
#include <cstring>
#include <vector>

using namespace std;

namespace Utills{

class FilePath{

public:
	FilePath();
	FilePath(const string& _path);
	~FilePath();
public:
	string GetFilePath();	//返回文件路径
	string GetFileNameFromPath(const string _path);		//从文件路径中获取文件名
	string GetDirectoryFromPath(const string _path);		//从文件路径中获取目录名称
	int DividePathByFlags(string _path,const string flag,vector<string>& ves);		//将文件路径按照flag切分
	string GetPathSection(string _path,int position);		//获取文件路径中的区块
	static void test(){
		cout<<"test"<<endl;
	}


private:
	string m_path;

};

}


#endif