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

//添加字段和字段约束
bool CTableLogic::AddField(const QString strDBName, CTableEntity&te,CFieldEntity &fe){
     QString temp=CFL_->GetQStringPath(CFL_->GetTbDefineFile(strDBName.toStdString(),te.getName()));
     CTD_->AddField(temp,fe);
}

//添加字段约束
bool CTableLogic::addFieldConstrait(const QString strDBName, CTableEntity&te,CFieldEntity &fe){
    QString temp=CFL_->GetQStringPath(CFL_->GetTbConstraitFile(strDBName.toStdString(),te.getName()));
    CTD_->AddFieldConstrain(temp,fe);
}
