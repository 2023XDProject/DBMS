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
    CFileLogic *CFL_;
};

#endif // SYNTAXTREE_H
