/*
 * 文件处理工具类。
 */
#ifndef CFILEHELPER_H
#define CFILEHELPER_H
#include <string>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QDebug>

using namespace std;

class CFileHelper{
public:
    CFileHelper(){};
    bool CreateDBFile(QString  strFileName);//创建文件，且当文件路径中的文件夹不存在时会创建文件夹
    bool IsValidFile(const QString strPath);//判断文件路径的有效性,看看这个文件存不存在
    bool IsValidDirector(const QString strDirectorName);//判断文件夹有效性，看看存不存在
    bool CreateDirector(QString strDirectorName);//创建文件夹
};

#endif // CFILEHELPER_H
