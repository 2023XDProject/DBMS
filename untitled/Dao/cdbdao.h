/*
 * 数据库数据操作类。
 */
#ifndef CDBDAO_H
#define CDBDAO_H
#include "../Util/DataStructure.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <vector>

using namespace std;

class CDBDao{

public:
    CDBDao();
    bool CreateDB(const QString strFilepath,CDBEntity db,bool bAppend = true);//将数据库信息保存到文件中
    bool GetDatabase(const QString strFilepath, CDBEntity &db);//从文件中获取数据库信息
private:
    vector<CDBEntity> CDBEntitys_;

};

#endif // CDBDAO_H
