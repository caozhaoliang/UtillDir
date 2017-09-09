#include "utillStr.hpp"
#include <stdlib.h>
#include <assert.h>

using namespace std;

namespace Utills{

FilePath::FilePath(){}

FilePath::FilePath(const string& _path){
	m_path = _path;
}
FilePath::~FilePath(){
}

string FilePath::GetFilePath(){
	return m_path;
}

/*  
	@brief for get file's name from path
*/
string FilePath::GetFileNameFromPath(const string _path=""){
	string tmp;
	if( !_path.empty() && _path!=""){
		tmp=_path;
	}else{
		tmp = m_path;
	}
	size_t pos;
	if( (pos = tmp.find_last_of("/")) != string::npos){
		return tmp.substr(pos+1);
	}
	return "";
}

/*  
	@brief for get directory from path
*/
string FilePath::GetDirectoryFromPath(const string _path = ""){
	string tmp;
	if( !_path.empty() && _path!=""){
		tmp=_path;
	}else{
		tmp = m_path;
	}
	size_t pos;
	if( (pos = tmp.find_last_of("/")) != string::npos){
		return tmp.substr(0,pos);
	}
	return "";
}

/*  
	@brief for Divide the path by flag
*/
int FilePath::DividePathByFlags(string _path, const string flag, vector<string>& ves ){
	string tmp;
	if( !_path.empty() && _path!=""){
		tmp=_path;
	}else{
		tmp = m_path;
	}
	int i=0;
	char* token = strtok(const_cast<char*>(tmp.c_str()),flag.c_str());
	while(token){
		ves.push_back(string(token));
		i++;
		token = strtok(NULL,flag.c_str());
	}
	return i;
}


/*  
	@brief for get a section string
*/
string FilePath::GetPathSection(string _path,int position){
	string tmp;
	if( !_path.empty() && _path!="" ){
		tmp=_path;
	}else{
		tmp = m_path;
	}

	vector<string> v_res;
	int pnum = 0;
	int count = DividePathByFlags(tmp,"/",v_res);
	assert(v_res.size() == count);
	if( abs(position) > count ) {
		return ""; 
	}
	if( position < 0 ) {
		pnum = count + position;
	}else {
		pnum = position -1;
	}
	int i =0;
	for(vector<string>::iterator it= v_res.begin(); it!=v_res.end();++it,++i ) {
		if( i == pnum ) {
			return *it;
		}
	}
	return "";

}






}