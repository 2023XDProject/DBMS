/*
 *
 */
#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H
#include <Regex>
#include <QString>
#include <QDebug>
#include <stdlib.h>
#include "DataStructure.h"
#include "../Logic/cfilelogic.h"

using namespace std;

class SyntaxTree
{
public:
    SyntaxTree();
    ~SyntaxTree();
    bool creatCDBEntity(string text,CDBEntity &te);//根据sql语句构造CDBEntity
    bool creatCTableEntity(string text,string dbName,CTableEntity &ct,vector<CFieldEntity> &cfe);//根据sql语句构造CTableEntity

    bool addTableField(string text,string dbName, int& fieldNum,vector<CFieldEntity> &cfe);//根据sql语句添加字段
    bool renameTableField(string text,string& fieldName,string& newName);//根据sql语句重命名字段
    bool modifyTableField(string text,string& fieldName,int& type,int& param,string& constraint);//根据sql语句修改字段
    bool dropTableField(string text,vector<string>& column);//根据sql语句重命名字段
    CFileLogic *CFL_;
};

#endif // SYNTAXTREE_H
