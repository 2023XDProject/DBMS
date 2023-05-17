#include "cdbdao.h"

CDBDao::CDBDao()
{
}

//将数据库信息保存到文件中
bool CDBDao::CreateDB(const QString strFilepath,CDBEntity db,bool bAppend){
    QFile file(strFilepath);
    if(bAppend==true){
        if(file.open(QIODevice::WriteOnly| QIODevice::Append)){
            QDataStream out(&file);
            //type,name,filepath,crtime
            out<<db.getBaseType()<<QString::fromStdString(db.getBaseName())
              <<QString::fromStdString(db.getBaseFilepath())
             <<db.getBaseCrtime().toString();
            file.close();
            return true;
        }else{
            return false;
        }
    }else{
        if(file.open(QIODevice::WriteOnly)){
            QDataStream out(&file);
            //type,name,filepath,crtime
            out<<db.getBaseType()<<QString::fromStdString(db.getBaseName())
              <<QString::fromStdString(db.getBaseFilepath())
             <<db.getBaseCrtime().toString();
            file.close();
            return true;
        }else{
            return false;
        }
    }
}

//从文件中获取数据库信息(没写完)
bool CDBDao::GetDatabase(const QString strFilepath,vector<int> &dbs){
    QFile file(strFilepath);
        if(file.open( QIODevice::ReadOnly)){
            QDataStream in(&file);
            //type,name,filepath,crtime
            bool type; // 数据库类型：true系统数据库，false用户自定义数据库
            QString name; // 数据库名称
            QString filepath; // 数据库文件路径
            QString crtime;
            if(file.exists()){
//              in>>type>>name>>filepath>>crtime;
//              db.setBaseType(type);
//              db.setBaseName(name.toStdString());
//              db.setBaseFilepath(filepath.toStdString());
//              db.setBaseCrtime(QDateTime::fromString(crtime,"yyyy-MM-dd hh:mm:ss"));
            }
            return true;
        }else{
            return false;
        }
}
