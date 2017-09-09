#ifndef _UTILLDIR_HPP__
#define _UTILLDIR_HPP__
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <regex.h>
#include <assert.h>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

using namespace std;

namespace Utills{

class utillDir{
public:
	bool DirectoryExists(const string file);
	bool CreateDirectory(const string& directory );
	bool EmptyDirectory(const string& directory );
	bool RemoveDirectory(const string& directory );
	bool CopyDirectories(const string& sourceDirectory,
							 const string& destDirectory );
	bool CopyFiles(const string srcFile, const string destFile );
	bool FilesExists(const string fileName );
	long long GetFileSize(const string fileName );
	bool GetAllFilesFormDir(const string directory,
							const string pattern,
							vector<string>& res);
	bool MoveFiles(const string src, const string des);
	bool CreateFiles(const string fileName);



public:
	utillDir();
	~utillDir();

private:


};









}






#endif