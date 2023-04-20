/*
 *
 */
#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H
#include <regex>
#include <QString>
#include "DataStructure.h"

using namespace std;

class SyntaxTree
{
public:
    SyntaxTree();
    bool creatCDBEntity(QString text,CDBEntity &te);//根据sql语句构造CDBEntity
    bool creatCTableEntity(QString text,CTableEntity &ct);//根据sql语句构造CTableEntity



};

#endif // SYNTAXTREE_H
