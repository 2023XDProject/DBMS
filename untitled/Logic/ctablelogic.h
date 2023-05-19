#ifndef CTABLELOGIC_H
#define CTABLELOGIC_H
#include "../Dao/ctabledao.h"
#include "../Util/cfilehelper.h"
#include "cfilelogic.h"
#include "../Util/DataStructure.h"
#include <QString>
#include <vector>

using namespace std;

class CTableLogic
{
public:
    CTableLogic();
    ~CTableLogic();
    bool CreateTable(const QString strDBName,CTableEntity &te);//创建表
    bool AddField(const QString strDBName,const string tableName,CFieldEntity &fe);//添加字段
    bool alterField(const QString strDBName,const string tableName,vector<CFieldEntity> &cfe);//写入修改后的字段
    bool GetField(const QString strDBName,const QString tableName,vector<CFieldEntity> &fe);//获取字段信息
    bool addFieldConstrait(const QString strDBName,const string tableName,CFieldEntity &fe);//添加字段约束
    bool GetTables(const QString strDBName,vector<CTableEntity> &cte);//获取表信息
    bool writeTables(const QString strDBName,vector<CTableEntity> &cte);//覆写表信息
    bool dropTable(const QString strDBName,const string tableName);//删除表

private:
    CTableDao *CTD_;
    CFileLogic *CFL_;
    CFileHelper *CFH_;
};

#endif // CTABLELOGIC_H
