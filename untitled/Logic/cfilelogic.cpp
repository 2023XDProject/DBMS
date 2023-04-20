#include "cfilelogic.h"
#include "qdir.h"

CFileLogic::CFileLogic(){
    DBPath_=QDir::currentPath().replace(QString("/"),QString("\\")).toStdString();
    //qDebug()<<QString::fromStdString(DBPath_);
    nowDBFile_=DBPath_+"\\ruanko.tb";
    DBFile_=DBPath_+"\\ALLDB.tb";
}

//获取当前数据库描述文件路径
string CFileLogic::GetNowDBFile(){
    //qDebug()<<QString::fromStdString(DBFile_);
    return  nowDBFile_;
}

//获取存放所有数据库描述文件路径
string CFileLogic::GetDBFile(){
    return DBFile_;
}

//获取数据库文件夹路径
string CFileLogic::GetDBFolder(const string strDBName){
     return  DBPath_+"\\data\\"+strDBName;
}

//获取数据库表描述文件路径
string CFileLogic::GetTableFile(const string strDBName){
     return DBPath_+"\\data\\"+strDBName+"\\"+strDBName+".tb";
}

//获取表定义文件路径
string CFileLogic::GetTbDefineFile(const string strDBName,const string strTableName){

}

//获取记录文件路径
string CFileLogic::GetTbRecordFile(const string strDBName,const string strTableName){

}

//将相对路径改成绝对路径
string CFileLogic::GetAbsolutePath(const string strRelativePath){
    QDir temDirs(QString::fromStdString(strRelativePath));
    QString filePath = temDirs.absolutePath();
    filePath.replace(QString("/"),QString("\\"));
}

/*
 * 将string类型的文件路径转化为QString类型的
 * 例如："D:\\practicalTraining\\data\\Ruanko"（string类型）
 * 转换为："D:/practicalTraining/data/Ruanko"（QString类型）->可以用来打开QFile
 * 为什么呢，因为我看QString不爽，能不用我就不用（烦）
 */
QString CFileLogic::GetQStringPath(string strRelativePath){
     return QString::fromStdString(strRelativePath).replace(QString("\\"),QString("/"));
}
