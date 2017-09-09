#include <iostream> 
// #include "utillDir.hpp"
#include "utillStr.hpp"

using namespace std;
using namespace Utills;

int main()
{
	string filepath = "/opt/kds/mobile-stock/demo_curl/pthread/test.txt";
	FilePath fp(filepath);
	fp.test();

	return 0;

}


int main2()
{
	// utillDir ut;
	// string fileName = "/opt/kds/mobile-stock/demo_curl/pthread/test.txt";
	// string fileName2 = "/opt/kds/mobile-stock/demo_curl/pthread/test2.txt";
	// string fileDir = "/opt/kds/mobile-stock/demo_curl/pthread/test";
	// string fileDir2 = "/opt/kds/mobile-stock/demo_curl/pthread/test2";
	/*for test files*/
	// if(!ut.FilesExists(fileName)){
	// 	std::cout<<"FilesExists"<<std::endl;
	// 	ut.CreateFiles(fileName);
	// }
	// if(!ut.DirectoryExists(fileDir)) {
	// 	std::cout<<"DirectoryExists"<<std::endl;
	// 	ut.CreateDirectory(fileDir);
	// 	if( ut.EmptyDirectory(fileDir) ){
	// 		std::cout<<"EmptyDirectory"<<std::endl;
	// 		ut.CopyFiles(fileName,fileDir+"/test.log");
	// 		ut.MoveFiles(fileName,fileDir+"/test.txt");
	// 		cout<< "getfilesize" << ut.GetFileSize(fileDir+"/test.log")<<endl;
	// 	}
	// }

	// /*for test CopyDirectories*/
	// if( !ut.DirectoryExists(fileDir2) ) {
	// 	std::cout<<"DirectoryExists2"<<std::endl;
	// 	ut.CreateDirectory(fileDir2);
	// 	if( ut.EmptyDirectory(fileDir2) ) {
	// 		std::cout<<"EmptyDirectory2"<<std::endl;
	// 		ut.CopyDirectories(fileDir,fileDir2 );
	// 	}
	// }

	// /*for delete directory*/
	// if( ut.DirectoryExists(fileDir) ) {
	// 	ut.RemoveDirectory(fileDir);
	// }
	// if( ut.DirectoryExists(fileDir2) ) {
	// 	ut.RemoveDirectory(fileDir2);
	// }
	// /*create file*/
	// if(!ut.FilesExists(fileName2)) {
	// 	ut.CreateFiles(fileName2);
	// }
	/* for test GetAllFilesFormDir*/
	// vector<string> ves;
	// string dir = "/opt/kds/mobile-stock/demo_curl/pthread/test/";
	// if( ut.DirectoryExists(dir) ) {
	// 	cout << "DirectoryExists"<<endl;
	// 	ut.GetAllFilesFormDir(dir,".*.cpp",ves);
	// }
	// for(vector<string>::iterator it=ves.begin(); it!=ves.end(); ++it) {
	// 	cout<< *it<< endl;
	// }
	return 0;
}