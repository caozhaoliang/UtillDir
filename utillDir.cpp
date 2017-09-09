#include "utillDir.hpp"

namespace Utills{


utillDir::utillDir(){}
utillDir::~utillDir(){}

/*
	@brief to judge directory exist
	@parameter absolute path
	@returns bool
*/
bool utillDir::DirectoryExists(const string file){
	if( file.empty() || file.length() == 0) {
		return false;
	}
	struct stat _stat;
	if((stat(file.c_str(),&_stat) == 0) && S_ISDIR(_stat.st_mode) ){
		return true;
	}else{
		return false;
	}
}

/*
	@brief to creat directory 
	@parameter absolute path
	@returns bool
*/
bool utillDir::CreateDirectory(const string& directory ) {
	if(directory.empty() || directory.length() == 0 ) {
		return false;
	}
	int res = mkdir(directory.c_str(),0777);
	return (res==0);
}

/*
	@brief to judge directory is empty
	@parameter absolute path
	@returns bool
*/
bool utillDir::EmptyDirectory(const string& directory ) {
	//目录是否存在
	if( !DirectoryExists(directory) ) {
		return false;
	}
	DIR* dir;
	int num = 0;
	dir = opendir(directory.c_str());
	while(dir) {
		if( readdir(dir) ) {
			++num;
		}else {
			break;
		}
	}
	closedir(dir);
	return num==2;// 当前目录(.) 和上级目录(..)
}

/*
	@brief remove directory  recursive
*/
static void dfs_remove_dir(){
	DIR* cur_dir = opendir("."); //打开当前目录
	struct dirent *ent = NULL;
	struct stat st;
	if( !cur_dir ) {
		return ;
	}
	while( (ent = readdir(cur_dir)) != NULL ) {
		stat(ent->d_name,&st);
		if(strcmp(ent->d_name,".") == 0 || strcmp(ent->d_name, "..") == 0) { //对当前目录不操作
			continue;
		}
		if( S_ISDIR(st.st_mode) ) {
			chdir(ent->d_name);//改变当前目录
			dfs_remove_dir(); //递归操作
			chdir(".."); //操作完之后回到上层目录
		}
		remove(ent->d_name); //删除文件
	}
	closedir(cur_dir); //关闭目录
}
/*
	@brief copy files
*/
bool utillDir::CopyFiles(const string srcFile, const string destFile ) {
	if( srcFile.empty() || destFile.empty() ) {
		return false;
	}
	int fin = open(srcFile.c_str(),O_RDONLY,0777);
	if( -1 == fin ) {
		return false;
	}
	int fout = open(destFile.c_str(),O_WRONLY|O_CREAT,0777);
	if( -1 == fout) {
		close(fin);
		return false;
	}
	ftruncate(fout,0); //ps: 清空文件内容
	lseek(fout,0,SEEK_SET);
	char buff[1024] = {0};
	int len = 0;
	while((len = read(fin,buff,sizeof(buff))) > 0){
		write(fout,buff,len);
	}
	close(fin);
	close(fout);
	return true;
}


/*
	@brief to remove directory 
	@parameter absolute path
	@returns bool
*/
bool utillDir::RemoveDirectory(const string& directory ){
	if( !DirectoryExists(directory) ) {
		return false;
	}
	char old_path[100];
	getcwd(old_path,100); //获取当前路径 存储
	if(chdir(directory.c_str()) == -1 ) {
		return false;
	}
	dfs_remove_dir();
	chdir(old_path);
	unlink(old_path); //删除文件，清空内存
	remove(directory.c_str());
	return true;
}



/*
	@brief to Copy directory 
	@parameter absolute path
	@returns bool
*/
bool utillDir::CopyDirectories(const string& sourceDirectory, const string& destDirectory ) {
	if( !DirectoryExists(sourceDirectory) || destDirectory.empty() ) {
		return false;
	}
	if( !DirectoryExists(destDirectory) && !CreateDirectory(destDirectory) ) {
		return false;
	}
	DIR* dir = NULL;
	struct dirent* ptr = NULL;
	struct stat buf;
	char tmp_src[512] = {0};
	char tmp_des[512] = {0};
	char* dest = const_cast<char*>(destDirectory.c_str());
	char* src = const_cast<char*>(sourceDirectory.c_str());
	if( ( dir = opendir(src) ) == NULL ) {
		closedir(dir);
		return false;
	}
	while( (ptr = readdir(dir)) != NULL ) {
		if(ptr->d_name[0] != '.' ) {
			strcpy(tmp_src,src);
			strcpy(tmp_des,dest);
			if(src[strlen(src) - 1] != '/' ) {
				strcat(tmp_src,"/");
			}
			if(dest[strlen(dest) - 1] != '/') {
				strcat(tmp_des,"/");
			}
			strcat(tmp_src, ptr->d_name);
			strcat(tmp_des, ptr->d_name);
			assert(stat(tmp_src,&buf) != -1);
			if(S_ISREG(buf.st_mode)) {
				CopyFiles(string(tmp_src), string(tmp_des));
			} else if(S_ISDIR(buf.st_mode)) {
				CopyDirectories(string(tmp_src),string(tmp_des));
			}
		}
	}
	closedir(dir);
	return true;
}

/*
	@brief to judge  file exist; 
	@parameter absolute path
	@returns bool
*/
bool utillDir::FilesExists(const string fileName ){
	if( fileName.empty() ) {
		return false;
	}
	if(access(fileName.c_str(),F_OK) == 0 ) {
		return true;
	}
	return false;
}

/*
	@brief to judge  file exist; 
	@parameter absolute path
	@returns long long
*/
long long utillDir::GetFileSize(const string fileName ){
	if( fileName.empty() ) {
		return false;
	}
	char* path = const_cast<char*>(fileName.c_str());
	long long fileSize;
	struct stat _stat;
	if( stat(path,&_stat) < 0 ) {
		return 0L;
	}else {
		fileSize = _stat.st_size;
	}
	return fileSize;
}


/*
	@brief 正则匹配
*/
static int regex_match(const char* buffer,const char* pattern) {
	int ret = 0;
	char errbuf[1024] = {0};
	regex_t reg;
	regmatch_t pm[1] = {0};
	ret = regcomp(&reg,pattern,REG_EXTENDED | REG_ICASE);
	if( ret != 0 ) {
		regerror(ret,&reg,errbuf,sizeof(errbuf));
		return -1;
	}
	if( regexec(&reg,buffer,1,pm,0) == 0 ) {
		regfree(&reg);
		return 0;
	}else{
		regfree(&reg);
		return -1;
	}
}

/*
	@brief to get file name form directory recursive 
	@parameter absolute path
	@returns bool
*/
bool utillDir::GetAllFilesFormDir(const string directory,
							const string pattern,
							vector<string>& res)
{
	if(!DirectoryExists(directory) || EmptyDirectory(directory) ) {
		return false;
	}
	if( pattern.empty() ) {
		return false;
	}
	char* dir_path = const_cast<char*>(directory.c_str());
	char des_path[512] = {0};
	char src_path[512] = {0};
	DIR* dir = NULL;
	struct dirent* ptr = NULL;
	struct stat buf;
	int i = 0,j = 0;

	if((dir = opendir(dir_path)) == NULL ){
		closedir(dir);
		return false;
	} 
	while((ptr = readdir(dir)) != NULL) {
		if( ptr->d_name[0] != '.' ) {
			strcpy(des_path,dir_path);
			if(dir_path[strlen(dir_path) - 1] != '/') {
				strcat(des_path,"/");
			}
			strcat(des_path,ptr->d_name);
			assert(stat(des_path,&buf) !=-1);
			if(S_ISREG(buf.st_mode)) {
				for(i=0; i < (int)strlen(des_path); ++i ) {
					if( des_path[i] == '/') {
						memset(src_path,0,strlen(src_path));
						j=0;
						continue;
					}
					src_path[j++] = des_path[i];
				}
				if( regex_match(src_path,pattern.c_str()) == 0) {
					res.push_back(des_path);
				}
			}
			else if( S_ISDIR(buf.st_mode) ) {
				GetAllFilesFormDir(string(des_path),pattern,res);
			}
		}
	}
	closedir(dir);
	return true;
}


/*
	@brief to create file
	@parameter absolute path
	@returns bool
*/
bool utillDir::CreateFiles(const string fileName){
	int fout = open(fileName.c_str(), O_RDWR | O_CREAT,0777);
	if( -1 == fout) {
		return false;
	}
	close(fout);
	return true;
}


/*
	@brief to move files 
	@parameter absolute path
	@returns bool
*/
bool utillDir::MoveFiles(const string src, const string des){
	if( src.empty()  ) {
		return false;
	}
	int ret = rename(src.c_str(),des.c_str());
	return (0 == ret);
}



}