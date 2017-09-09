#include <iostream> 
#include <cstring>

using namespace std;

namespace Utills{

string subStrByflags(const string src,const string start,const string end) {
	string temp = src;
	size_t posStart = temp.find(start);
	size_t posEnd = temp.find(end);
	if( posStart!=string::npos && posEnd !=string::npos && posEnd > posStart) {
		return temp.substr(posStart+1,posEnd-posStart+1)
	}
	return "";
}









}