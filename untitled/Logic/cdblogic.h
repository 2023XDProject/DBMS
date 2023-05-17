/*
 * 数据库业务逻辑类。包含数据库创建和查询
 */
#ifndef CDBLOGIC_H
#define CDBLOGIC_H
#include "cfilelogic.h"
#include "../Dao/cdbdao.h"
#include "../Util/cfilehelper.h"
#include <qDebug>

using namespace std;

class CDBLogic{

public:
    CDBLogic();
    ~CDBLogic();
    bool createRuankoFile();//创建数据库描述文件
    bool CreateDatabase(CDBEntity &db);//创建数据库
    bool GetDatabase(CDBEntity &db);//查询数据库
    string getDefaDBFile();//获取数据库描述文件绝对路径
    string getDBFolder(const string strDBName);//获取数据库文件夹路径
    bool createDataDBFolder();//创建data文件夹
 private:
   CFileLogic *CFL_;
   CDBDao *CDBD_;
   CDBEntity *CDBE_;
   CFileHelper *CFH_;
};

#endif // CDBLOGIC_H
