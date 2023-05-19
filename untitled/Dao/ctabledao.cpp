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

//获取文件中的表信息(.db)
bool CTableDao::GetTables(const QString strFilePath, vector<CTableEntity> &cte){
    QFile file(strFilePath);
    if(file.open(QIODevice::ReadOnly)){
        QDataStream in(&file);
        QString temp1;
        int temp2;
        QDateTime time;
        CTableEntity te;
        //QTextStream out(&file);
        //name,fieldNum,recordNum,Tdfpath,Trdpath,Crtime,Mtime
        while(!in.atEnd()){
            in>>temp1;
            te.setName(temp1.toStdString());
            in>>temp2;
            te.setField_num(temp2);
            in>>temp2;
            te.setRecord_num(temp2);
            in>>temp1;
            te.setTdf(temp1.toStdString());
            in>>temp1;
            te.setTrd(temp1.toStdString());
            in>>time;
            te.setCrtime(time);
            in>>time;
            te.setMtime(time);
            cte.push_back(te);
        }
        file.close();
        return true;
    }else{
        return false;
    }
}

//添加字段，将字段信息保存到（.tdf）文件中。
bool CTableDao::AddField(const QString strFilePath, CFieldEntity &fe){
    QFile file(strFilePath);
    //追加写入
    if(file.open(QIODevice::WriteOnly| QIODevice::Append)){
        QDataStream out(&file);
        //QTextStream out(&file);
        //order,name,type,param,IntegrityNum,Mtime
        out<<fe.getOrder()<<QString::fromStdString(fe.getName())<<fe.getType()
          <<fe.getIntegrityNum();
        if(fe.getType()==4){
            out<<fe.getParam();
        }
        out<<fe.getMtime();
        file.close();
        return true;
    }else{
        return false;
    }

}

//覆写所有字段
bool CTableDao::writeField(const QString strFilePath,vector<CFieldEntity> &cfe){
    QFile file(strFilePath);
    //追加写入
    if(file.open(QIODevice::WriteOnly)){
        QDataStream out(&file);
        //QTextStream out(&file);
        //order,name,type,param,IntegrityNum,Mtime
        for(int i=0;i<cfe.size();++i){
            out<<cfe[i].getOrder()<<QString::fromStdString(cfe[i].getName())<<cfe[i].getType()
              <<cfe[i].getIntegrityNum();
            if(cfe[i].getType()==4){
                out<<cfe[i].getParam();
            }
            out<<cfe[i].getMtime();
        }
        file.close();
        return true;
    }else{
        return false;
    }

}

////添加字段约束信息到(.tic)文件中
//bool CTableDao::AddFieldConstrain(const QString strFilePath,CFieldEntity &fe){
//    QFile file(strFilePath);
//    if(file.open(QIODevice::WriteOnly| QIODevice::Append)){
//        //QDataStream out(&file);
//        QTextStream out(&file);
//        //name,fieldNum,recordNum,Tdfpath,Trdpath,Crtime,Mtime
//        for(int i=0;i<fe.getIntegrityNum();++i){
//            out<<QString::fromStdString("constrain_"+fe.getName()+"_"+to_string(i+1))<<QString::fromStdString(fe.getName())
//              <<fe.getIntegrityType();
//            if(fe.getIntegrityType()>=1000){
//                out<<QString::fromStdString(fe.getIntegrity(0));
//            }
//        }
//        file.close();
//        return true;
//    }else{
//        return false;
//    }
//}

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

//获取字段约束信息
bool CTableDao::GetFieldConstrain(const QString strFilePath, CFieldEntity &fe){

}

//获取文件中的字段信息。
bool CTableDao::GetFields(const QString strFilepath,vector<CFieldEntity> &fe){
    CFieldEntity temp;
    QFile file(strFilepath);
    if(file.open(QIODevice::ReadOnly)){
        //out<<fe.getOrder()<<QString::fromStdString(fe.getName())<<fe.getType()
        //<<fe.getIntegrityNum()<<fe.getParam()<<fe.getMtime();
        QDataStream in(&file);
        //order,name,type,IntegrityNum,param,Mtime
        int order,type;//字段顺序
        QString name; // 名称
        QDateTime mtime; // 最后修改时间
        while(!file.atEnd()){
            in>>order>>name;
            temp.setOrder(order);
            temp.setName(name.toStdString());
            in>>type;
            temp.setType(type);
            in>>order;
            temp.setIntegrityType(order);
            if(type==4){
                in>>order;
                temp.setParam(order);
            }
            in>>mtime;
            temp.setMtime(mtime);
            fe.push_back(temp);
        }
        file.close();
        return true;
    }else{
        return false;
    }
}

//覆写表信息
bool CTableDao::writeTable(const QString strFilePath, vector<CTableEntity> &cte){
    QFile file(strFilePath);
    if(file.open(QIODevice::WriteOnly)){
        QDataStream out(&file);
        //QTextStream out(&file);
        //name,fieldNum,recordNum,Tdfpath,Trdpath,Crtime,Mtime
        for(int i=0;i<cte.size();++i){
            out<<QString::fromStdString(cte[i].getName())<<cte[i].getField_num()<<cte[i].getRecord_num()
              <<QString::fromStdString(cte[i].getTdf())<<QString::fromStdString(cte[i].getTrd())
             <<cte[i].getCrtime()<<cte[i].getMtime();
        }
        file.close();
        return true;
    }else{
        return false;
    }
}

//删除表
bool CTableDao::dropTable(const QString strFilePath){
    QFile file(strFilePath);
    if (file.exists()){
        if(file.remove()){
           return true;
        }
        else{
           return false;
        }
    }
}

//删除文件夹
bool CTableDao::dropFloder(const QString strFilePath){
        if (strFilePath.isEmpty()){
              return false;
        }
        QDir dir(strFilePath);
        if(!dir.exists())
        {
            return true;
        }
        dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //设置过滤
        QFileInfoList fileList = dir.entryInfoList(); // 获取所有的文件信息
        foreach (QFileInfo file, fileList)
        { //遍历文件信息
            if (file.isFile())
            { // 是文件，删除
                file.dir().remove(file.fileName());
            }else
            { // 递归调用函数，删除子文件夹
                dropFloder(file.absoluteFilePath());
            }
        }
        return dir.rmpath(dir.absolutePath()); // 这时候文件夹已经空了，再删除文件夹本身
}
