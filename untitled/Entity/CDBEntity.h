/*
 * 存放数据库基本信息,查询，修改（没有容错）数据库信息
 */
#ifndef CDBENTITY_H
#define CDBENTITY_H
#include <string>
#include "../Util/DataStructure.h"

using namespace std;

class CDBEntity{

public:
    CDBEntity(){};
    CDBEntity(bool type,string n,string f, QDateTime t){
        DB_.type=type;
        DB_.name=n;
        DB_.filepath=f;
        DB_.crtime=t;
    };

    string getBaseName(){return DB_.name;};
    bool getBaseType(){return DB_.type;};
    string getBaseFilepath(){return DB_.filepath;};
    QDateTime getBaseCrtime(){return DB_.crtime;};

    void setBaseName(string n){DB_.name=n;};
    void setBaseType(bool t){DB_.type=t;};

private:
   DatabaseBlock DB_;
};

#endif // CDBENTITY_H
