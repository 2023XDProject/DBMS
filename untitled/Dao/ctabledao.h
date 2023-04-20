#ifndef CTABLEDAO_H
#define CTABLEDAO_H
#include "../Util/DataStructure.h"
#include <QString>

using namespace std;

class CTableDao
{
public:
    CTableDao();
    bool Create(const QString strFilePath,CTableEntity &te);//创建表，保存表信息。
    //bool AddField(const QString strFilePath, CFieldEntity &fe);//添加字段，将字段信息保存到文件中。
    //int GetTables(const QString strFilepath, TABLEARR &arr);//获取文件中的表信息
    bool GetFields(const QString strFilepath, CTableEntity &te);//获取文件中的字段信息。
    bool AlterTable(const QString strFilePath, CTableEntity &te);//修改表结构
};

#endif // CTABLEDAO_H
