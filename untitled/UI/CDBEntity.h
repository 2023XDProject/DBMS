/*
 * 存放数据库基本信息
 */
#ifndef CDBENTITY_H
#define CDBENTITY_H
#include <string>
#include "windows.h"
#include "DataStructure.h"

using namespace std;

class CDBEntity{

public:
    CDBEntity();

private:
   DatabaseBlock DB_;
};

#endif // CDBENTITY_H
