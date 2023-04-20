#include "cdbdao.h"

CDBDao::CDBDao()
{
}

//将数据库信息保存到文件中
bool CDBDao::CreateDB(const QString strFilepath,CDBEntity db,bool bAppend){
    QFile file(strFilepath);
    if(bAppend==true){
        if(file.open(QIODevice::Truncate | QIODevice::WriteOnly|QIODevice::Append)){
            QTextStream out(&file);
            //type,name,filepath,crtime
            out<<db.getBaseType()<<QString::fromStdString(db.getBaseName())
              <<QString::fromStdString(db.getBaseFilepath())
             <<db.getBaseCrtime().toString();
            return true;
        }else{
            return false;
        }
    }else{
        if(file.open(QIODevice::Truncate | QIODevice::ReadOnly)){
            QTextStream out(&file);
            //type,name,filepath,crtime
            out<<db.getBaseType()<<QString::fromStdString(db.getBaseName())
              <<QString::fromStdString(db.getBaseFilepath())
             <<db.getBaseCrtime().toString();
            return true;
        }else{
            return false;
        }
    }
}

//从文件中获取数据库信息(没写完)
bool CDBDao::GetDatabase(const QString strFilepath, CDBEntity &db){
    QFile file(strFilepath);
        if(file.open(QIODevice::Truncate | QIODevice::ReadWrite|QIODevice::Append)){
            QTextStream in(&file);
            //type,name,filepath,crtime
            bool type; // 数据库类型：true系统数据库，false用户自定义数据库
            string name; // 数据库名称
            string filepath; // 数据库文件路径
            QDateTime crtime;

//            in>>type>>QString::fromStdString(db.getBaseName())
//              >>QString::fromStdString(db.getBaseFilepath())
//             >>db.getBaseCrtime().toString();
            return true;
        }else{
            return false;
        }
}
