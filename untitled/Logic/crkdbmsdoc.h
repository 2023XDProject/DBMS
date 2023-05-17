/*
 * 文档类，实现程序中与界面相关的逻辑操作，以及对数据进行维护和管理。
 * 语法树也将在这里实现
 */
#ifndef CRKDBMSDOC_H
#define CRKDBMSDOC_H
#include "cdblogic.h"
#include "../Util/syntaxtree.h"
#include "ctablelogic.h"
#include <vector>

using namespace std;

class CRKDBMSDoc{

public:
    CRKDBMSDoc();
    ~CRKDBMSDoc();
    bool OnNewDocument();//新建文档，创建默认数据库(完成)
    CDBEntity GetDBEntity(string DBName);//获取数据库
    CDBEntity GetDBEntity();
    bool loadDataBase();//加载数据库
    bool newDocument(string strName);//新建数据库(完成)
    CTableEntity* CreateTable(string strName);//创建表
    //CFieldEntity* AddField(CFieldEntity &field);//添加字段
    void LoadTables(void);//加载表
    //CRecordEntity* InsertRecord(CRecordEntity &record); //插入记录
    void LoadRecord(void);//查询所有记录
    bool matchQSLType(QString text);//匹配sql语句类型

private:
    QString DBName;//当前数据库名
    CDBLogic *CDBL_;
    CTableLogic *CTL_;
    SyntaxTree *STree_;
    vector<CDBEntity>  allDB_;//所有数据库信息
};

#endif // CRKDBMSDOC_H
