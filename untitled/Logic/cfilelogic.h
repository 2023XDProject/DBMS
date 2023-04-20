/*
 * 文件处理逻辑类。
 */
#ifndef CFILELOGIC_H
#define CFILELOGIC_H
#include <string>
#include <QCoreApplication>
#include <QDebug>

using namespace std;

class CFileLogic{

public:
    CFileLogic();
    string GetNowDBFile();//获取当前数据库描述文件路径
    string GetDBFile();//获取存放所有数据库描述文件路径
    string GetDBFolder(const string strDBName);//获取数据库文件夹路径
    string GetTableFile(const string strDBName);//获取数据库表描述文件路径
    string GetTbDefineFile(const string strDBName,const string strTableName);//获取表定义文件路径
    string GetTbRecordFile(const string strDBName,const string strTableName);//获取记录文件路径
    string GetAbsolutePath(const string strRelativePath);//将相对路径改成绝对路径
    QString GetQStringPath(string strRelativePath);//将string类型的文件路径转化为QString类型的
private:
    string nowDBFile_;//当前数据库描述文件路径
    string DBFile_;//存放所有数据库描述文件路径
    string DBPath_;//“数据库路径//（不含数据库名）”
    string DBFolderPath_;//
    string TableFile_;

};

#endif // CFILELOGIC_H
