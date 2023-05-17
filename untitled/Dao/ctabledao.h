#ifndef CTABLEDAO_H
#define CTABLEDAO_H
#include "../Util/DataStructure.h"
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QDateTime>
#include <vector>

using namespace std;

class CTableDao
{
public:
    CTableDao();
    bool Create(const QString strFilePath,CTableEntity &te);//创建表，保存表信息。
    bool writeField(const QString strFilePath,vector<CFieldEntity> &cfe);//覆写所有字段
    bool AddField(const QString strFilePath, CFieldEntity &fe);    //添加字段，将字段信息保存到文件中。0:追加写入
    bool GetTables(const QString strFilepath, vector<CTableEntity> &cte);//获取文件中的表信息(.tb)
    bool AddFieldConstrain(const QString strFilePath, CFieldEntity &fe);//添加字段约束信息
    bool GetFieldConstrain(const QString strFilePath, CFieldEntity &fe);//获取字段约束信息
    bool GetFields(const QString strFilepath, vector<CFieldEntity> &fe);//获取文件中的字段信息。
    bool writeTable(const QString strFilePath, vector<CTableEntity> &te);//覆写表信息

};
#endif // CTABLEDAO_H
