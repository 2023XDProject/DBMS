#pragma once//预处理指令，保证头文件只被编译一次，防止头文件被重复引用
#ifndef CRECORDLOGIC_H
#define CRECORDLOGIC_H

#include <string>
#include <vector>
//#include "Global.h"
//#include "RecordEntity.h"
//#include "FieldEntity.h"

#endif // CRECORDLOGIC_H

using namespace std;

class CRecordLogic
{
private:
    string trdPath;
    string tdfPath;
    string dbName;
    string tbName;
public:
    CRecordLogic(string dbname,string tableName);
    ~CRecordLogic(void);

    int AddRecord(CRecordEntity &record,vector<CFieldEntity> &fieldList);
    int DeleteRecord(int id);
    int DeleteAllRecord();
    int ModifyRecord(CRecordEntity &record);
    vector<CRecordEntity> GetRecordList();
    vector<CRecordEntity> ConditionQuery(vector<CFieldEntity> m_list,
                                        vector<string> compare,
                                        vector<string> values);

    int IsUnique(string &value,string &field);
    int IsNull(string &value);
    int IntegrityVerify(CRecordEntity &record,CFieldEntity &field);
    int IntegrityVerify(string &val,CFieldEntity &field);
};

