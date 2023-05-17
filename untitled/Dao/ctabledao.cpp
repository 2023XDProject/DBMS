#include "ctabledao.h"

CTableDao::CTableDao()
{

}

//创建表，保存表信息
bool CTableDao::Create(const QString strFilePath,CTableEntity &te){
    QFile file(strFilePath);
    if(file.open(QIODevice::WriteOnly| QIODevice::Append)){
        QDataStream out(&file);
        //QTextStream out(&file);
        //name,fieldNum,recordNum,Tdfpath,Trdpath,Crtime,Mtime
        out<<QString::fromStdString(te.getName())<<te.getField_num()<<te.getRecord_num()
          <<QString::fromStdString(te.getTdf())<<QString::fromStdString(te.getTrd())
         <<te.getCrtime()<<te.getMtime();
        file.close();
        return true;
    }else{
        return false;
    }

}

//添加字段，将字段信息保存到（.tdf）文件中。
bool CTableDao::AddField(const QString strFilePath, CFieldEntity &fe){
    QFile file(strFilePath);
    if(file.open(QIODevice::WriteOnly| QIODevice::Append)){
        QDataStream out(&file);
        //QTextStream out(&file);
        //order,name,type,param,IntegrityNum,Mtime
        out<<fe.getOrder()<<QString::fromStdString(fe.getName())<<fe.getType()
          <<fe.getIntegrityNum()<<fe.getParam()<<fe.getMtime();
        file.close();
        return true;
    }else{
        return false;
    }
}

//添加字段约束信息到(.tic)文件中
bool CTableDao::AddFieldConstrain(const QString strFilePath,CFieldEntity &fe){
    QFile file(strFilePath);
    if(file.open(QIODevice::WriteOnly| QIODevice::Append)){
        //QDataStream out(&file);
        QTextStream out(&file);
        //name,fieldNum,recordNum,Tdfpath,Trdpath,Crtime,Mtime
        for(int i=0;i<fe.getIntegrityNum();++i){
            out<<QString::fromStdString("constrain_"+fe.getName()+"_"+to_string(i+1))<<QString::fromStdString(fe.getName())
              <<fe.getIntegrityType();
            if(fe.getIntegrityType()>=1000){
                out<<QString::fromStdString(fe.getIntegrity(0));
            }
        }
        file.close();
        return true;
    }else{
        return false;
    }
}
