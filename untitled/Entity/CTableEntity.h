#ifndef CTABLEENTITY_H
#define CTABLEENTITY_H
#include <string>
#include "../Util/DataStructure.h"

using namespace std;

class CTableEntity{
    CTableEntity(){};
    CTableEntity(string name,int record_num,int field_num,string tdf,string trd,QDateTime crtime,QDateTime mtime){
        TB_.name=name; // 名称
        TB_.record_num= record_num; // 记录数
        TB_.field_num =field_num; // 字段数
        TB_.tdf =tdf; // 表定义文件路径
        TB_.trd =trd; // 记录文件路径
        TB_.crtime =crtime; // 表格创建时间
        TB_.mtime =mtime; // 最后修改时间
    }
    string getName(){return TB_.name;}
    int getRecord_num(){return TB_.record_num; }
    int getField_num(){return TB_.field_num;}
    string getTdf(){return TB_.tdf;}
    string getTrd(){return TB_.trd;}
    QDateTime getCrtime(){return TB_.crtime;}
    QDateTime getMtime(){return TB_.mtime;}

private:
     TableBlock TB_;
};

#endif // CTABLEENTITY_H
