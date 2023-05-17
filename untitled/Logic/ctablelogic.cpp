#include "ctablelogic.h"

CTableLogic::CTableLogic():CTD_(new CTableDao()),CFL_(new CFileLogic()){

}

CTableLogic::~CTableLogic(){
    delete CTD_;
}

/*
 * 创建表
 * @param:QString strDBName:表所在的数据库名称
 *        CTableEntity &te:表信息实体
 */
bool CTableLogic::CreateTable(const QString strDBName,CTableEntity &te){
     //向表描述文件写入表信息
     QString temp=CFL_->GetQStringPath(CFL_->GetTableFile(strDBName.toStdString()));
     //创建（.tdf）文件，写入字段信息
     CTD_->Create(temp,te);
}

//添加字段
bool CTableLogic::AddField(const QString strDBName,string tableName,CFieldEntity &fe){
     QString temp=CFL_->GetQStringPath(CFL_->GetTbDefineFile(strDBName.toStdString(),tableName));
     CTD_->AddField(temp,fe);
}

//添加字段约束
bool CTableLogic::addFieldConstrait(const QString strDBName,const string tableName,CFieldEntity &fe){
    QString temp=CFL_->GetQStringPath(CFL_->GetTbConstraitFile(strDBName.toStdString(),tableName));
    CTD_->AddFieldConstrain(temp,fe);
}

//获取字段信息
bool CTableLogic::GetField(const QString strDBName,const QString tableName,vector<CFieldEntity> &fe){
    string temp=CFL_->GetTbDefineFile(strDBName.toStdString(),tableName.toStdString());
    CTD_->GetFields(QString::fromStdString(temp),fe);
}

//写入修改后的字段
bool CTableLogic::alterField(const QString strDBName,const string tableName,vector<CFieldEntity> &cfe){
    string temp=CFL_->GetTbDefineFile(strDBName.toStdString(),tableName);
        CTD_->writeField(QString::fromStdString(temp),cfe);
}

//获取表信息
bool CTableLogic::GetTables(const QString strDBName,vector<CTableEntity> &cte){
     string temp=CFL_->GetTableFile(strDBName.toStdString());
     CTD_->GetTables(QString::fromStdString(temp),cte);
}

//覆写表信息
bool CTableLogic::writeTables(const QString strDBName,vector<CTableEntity> &cte){
       string temp=CFL_->GetTableFile(strDBName.toStdString());
       CTD_->writeTable(QString::fromStdString(temp),cte);
}
