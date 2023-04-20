#include "cfilehelper.h"

//创建文件，且当文件路径中的文件夹不存在时会创建文件夹
bool CFileHelper::CreateDBFile(QString strFileName){
     //qDebug()<<strFileName;
     QFile file(strFileName);
     if(file.open(QIODevice::Truncate | QIODevice::ReadWrite)){
         return true;
     }else{
         return false;
     }
}

//创建文件夹
bool CFileHelper::CreateDirector(QString strDirectorName){
    qDebug()<< strDirectorName;
    QDir dir(strDirectorName);
    if(!dir.exists()){
        dir.mkdir(strDirectorName);
        return true;
    }else{
        return false;
    }
}

//判断文件路径的有效性,看看这个文件存不存在
bool CFileHelper::IsValidFile(const QString strPath){
    QFileInfo fileInfo(strPath);
        if(fileInfo.exists())
        {
            return true;
        }
        return false;
}

//判断文件夹有效性，看看存不存在
bool CFileHelper::IsValidDirector(const QString strDirectorName){
    QDir dir(strDirectorName);
       if(dir.exists())
       {
         return true;
       }
       return false;
}
