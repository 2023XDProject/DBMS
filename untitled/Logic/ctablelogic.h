#ifndef CTABLELOGIC_H
#define CTABLELOGIC_H
#include "../Util/DataStructure.h"
#include <QString>

using namespace std;

class CTableLogic
{
public:
    CTableLogic();
    bool CreateTable(const QString strDBName,CTableEntity &te);//创建表
    bool AddField(const QString strDBName, CTableEntity&te,CTableEntity &fe);//添加字段
    //int GetTables(const QString strDBName, TABLEARR &arrTables);//获取表信息
};

#endif // CTABLELOGIC_H
