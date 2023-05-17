#include "operation.h"

Operation::Operation()
{

}

Operation::Operation(QString sql){
    target_column = new vector<QString>;
    values = new vector<QString>;
    conditions = new vector<QString>;
    this->sql = sql;//将sql赋值
    error_code = 0;
    //开始语法解析
    get_operation_type();

}

QString Operation::is_int_float_varchar_char(QString value){
    bool isInt;
    bool isFloat;
    bool isVarchar;
    bool isChar;

    value.toInt(&isInt);
    if (isInt){
        std::cout<<"int"<<std::endl;
        return "int";}
    value.toDouble(&isFloat);
    if(isFloat){
        std::cout<<"float"<<std::endl;
         return "float";}
    QRegExp is_char_varchar("'(.*)'");
    if(is_char_varchar.indexIn(value)==-1){

        std::cout<<"error"<<std::endl;
        return "error type";
    }else{
        if(is_char_varchar.cap(1).length()==1){
            isChar=true;

            std::cout<<"char"<<std::endl;
            return "char";
        }else{
            isVarchar=true;

            std::cout<<"varchar"<<std::endl;
            return "varchar";
        }
    }

}

void Operation::get_operation_type(){
    QRegExp get_type("\\s*(\\w{1,})\\s");
    int pos = get_type.indexIn(sql);
    QString lower = get_type.cap(1).toLower();
    if(lower == "select"){
        operation_type = "select";
        handle_select();
    }else if(lower=="alter"){
        operation_type = "alter";
        handle_alter();
    }else if(lower=="update"){
        operation_type = "update";
        handle_update();
    }else if(lower=="insert"){
        operation_type = "insert";
        handle_insert();
    }else if(lower=="delete"){
        operation_type = "delete";
        handle_delete();
    }else if(lower=="create"){
        operation_type = "create";
        handle_create();
    }else{
        error_code = INVALID_OPERATION_TYPE;
        std::cout<<"wrong operation type"<<std::endl;
    }
}


//处理select语句
void Operation::handle_select(){
    QRegExp get_column("\\s?\\w{6}\\s+(.{1,})\\s+(\\w{4})\\s+(\\S{1,})");
    int pos = get_column.indexIn(sql);
    QString from = get_column.cap(2).toLower();
    if(from!="from"){//判断语句中是否有from
        error_code = SELECT_FROM_NOT_EXISTS;
        std::cout<<"from不存在"<<std::endl;
    }
    std::cout<<get_column.cap(1).toStdString()<<std::endl;
    std::cout<<get_column.cap(3).toStdString()<<std::endl;
    QString all_columns = get_column.cap(1);                                //cap(1)这里是所有的列
    QString all_tables = get_column.cap(3);                                 //cap(3)这里是所有的表

    if(error_code==0){//说明前面都是正确的
        QRegExp check_where("(from|FROM)\\s+(\\S{1,})\\s+(\\w{5})");
        check_where.indexIn(sql);
        if(check_where.cap(3).toLower()!="where"){//说明sql语句中没有where
            conditions=nullptr;
            //下面检查没有where，表名的后面是否有其他符号,下面两句试试取出表名的字符串的长度并拼接到正则表达式中
            int length = all_tables.length();
            QString lenstr = QString::number(length);
            QRegExp check_chars("(from|FROM)\\s+(\\w{"+lenstr+"})\\s*;");
            check_chars.indexIn(sql);
//            QString test = check_chars.cap(1);
//            QString test_2 = check_chars_2.cap(1);
            if(check_chars.cap(2)!=all_tables){
                std::cout<<"where not exist"<<std::endl;
            }
        }else{//在这个语句块中将where后面的条件取出
            QRegExp get_conditions("(where|WHERE)\\s+(.{1,});");   //这里先不判断分号
            if(get_conditions.indexIn(sql)==-1){
                error_code = NO_SEMICOLON;
                std::cout<<"select没有分号"<<std::endl;
                return;
            }
            QString all_conditions = get_conditions.cap(2);                    //取出判断条件的字符串
            std::cout<<all_conditions.toStdString()<<std::endl;
        }
    }

    //下面还要检查表是否存在，列是否存在
    parse_column(all_columns);//将得到的字符串进行解析
}

void Operation::handle_insert(){
    QRegExp check_into("\\s*(\\w{6})\\s+(\\w{4})\\s+(\\w{1,})");  //insert into table_name （ ）values(a,b,c);
    check_into.indexIn(sql);
    if(check_into.cap(2)!="into"){//insert 后面没有into
        error_code = INSERT_ERROR;
        std::cout<<"出错"<<std::endl;
        std::cout<<check_into.cap(2).toStdString()<<std::endl;
        return;
    }
    QString all_columns;
    QString all_tables = check_into.cap(3);//cap(3)这里是插入的的表
    std::cout<<all_tables.toStdString()<<std::endl;
    bool isInsertAll = false;//判断是否指定行插入还是全部插入
    QRegExp check_iIA("(\\)\\s*values\\s*\\()");
    if(check_iIA.indexIn(sql)==-1){
        isInsertAll = true;
        std::cout<<"全部插入"<<std::endl;
    }else{
        isInsertAll = false;
        std::cout<<"指定行插入"<<std::endl;
        QRegExp get_columnName(all_tables+"\\s*(\\S{1,})\\s*values");
        get_columnName.indexIn(sql);
        all_columns = get_columnName.cap(1);//得到insert的属性名
        all_columns.remove(QChar('('),Qt::CaseSensitive);
        all_columns.remove(QChar(')'),Qt::CaseSensitive);
        std::cout<<all_columns.toStdString()<<std::endl;
    }
    QRegExp get_insertValue("values\\s*(\\S{1,})\\s*;");
    if(get_insertValue.indexIn(sql)==-1){//说明没有分号
        error_code = NO_SEMICOLON;
        std::cout<<"没有分号"<<std::endl;
    }else{//有分号
        QString values = get_insertValue.cap(1);
        if(values[0]!='(' or values[values.length()-1]!=')'){//说明括号不全
            std::cout<<"括号不全"<<std::endl;
            error_code = INCOMPLETE_PATENTHESES;
        }else{//得到所有的值（最后要按照空格分开）
            values.remove(QChar('('),Qt::CaseSensitive);
            values.remove(QChar(')'),Qt::CaseSensitive);
            std::cout<<values.toLocal8Bit().toStdString()<<std::endl;
        }
    }


    //后面要将各个结果的字符串按逗号分开，并处理
}

void Operation::handle_update(){
    QRegExp get_table("\\w{6}\\s+(\\S{1,})\\s+(set|SET)\\s+");//update table_name set a=a+1 where …… ;
    get_table.indexIn(sql);
    QString tableName = get_table.cap(1);
    QString set = get_table.cap(2);
    QString condition;//update的条件
    QString modification;//修改的属性
    if(set!="set" and set!="SET"){//说明没有set
        error_code = UPDATE_ERROR;
        std::cout<<"update没有set"<<std::endl;
        return;
    }
    //下面检查是否存在where
    QRegExp check_where("\\s+(where||WHERE)\\s+");
    if(check_where.indexIn(sql)==-1){
        condition="";
        QRegExp get_modification("(set|SET)\\s+(.*);");
        if(get_modification.indexIn(sql)==-1){
            error_code = UPDATE_ERROR;
            std::cout<<"set后面条件错误"<<std::endl;
            return;
        }else{
            modification = get_modification.cap(2);
        }
    }else{//存在where，取出修改的属性和判断条件
        // update student set sno =123 where sname = wck;
        QRegExp get_ConAndMod("(set|SET)\\s+(.*)(where|WHERE)(.*);");
        if(get_ConAndMod.indexIn(sql)==-1){
            error_code = NO_SEMICOLON;
            std::cout<<"update没有分号"<<std::endl;
            return;
        }else{
            condition = get_ConAndMod.cap(4);//where条件
            modification = get_ConAndMod.cap(2);//被修改的部分
        }
    }
    std::cout<<tableName.toStdString()<<std::endl;
    std::cout<<condition.toStdString()<<std::endl;
    std::cout<<modification.toStdString()<<std::endl;
}

void Operation::handle_create(){
    QRegExp check_table("(create|CREATE)\\s+(table|TABLE|database|DATABASE)");
    bool isTable;
    int attributesnum;
    QString name;//表名
    QString attributes;

    //判断是table还是database
    if(check_table.indexIn(sql)==-1){
        std::cout<<"create 后面没有 table或者database"<<std::endl;
        error_code = CREATE_ERROR;
        return;
    }else{
        if(check_table.cap(2).toLower()=="table"){
            isTable = true;
        }else{
            isTable = false;
        }
    }

    //如果是创建一个table
//    CREATE TABLE table_name (
//        column1 data_type,
//        column2 data_type,
//        ...
//    );

    if(isTable){
        QRegExp get_Name("(table|TABLE)\\s+(\\S*)\\s*\\(");

        if(get_Name.indexIn(sql)==-1){
            std::cout<<"table name not found"<<std::endl;
            error_code = CREATE_ERROR;
            return;
        }

        name = get_Name.cap(2);//取出表名

        //下面取出各种属性，column1 data_type,column2 data_type, unique（column1，column2）
        QRegExp get_Attributes(name+"\\s*\\((.*)\\);");
        if(get_Attributes.indexIn(sql)==-1){
            error_code = NO_SEMICOLON;
            std::cout<<"semicolon not found"<<std::endl;
            return;
        }

        attributes = get_Attributes.cap(1);
        std::cout<<attributes.toStdString()<<std::endl;

        QStringList parameterList = attributes.split(",", QString::SkipEmptyParts);  // 拆分为逗号分隔的参数列表
            for (QString parameter : parameterList) {
                parameter = parameter.trimmed();  // 去掉空格

                //可以在这先取出前六个字符，判断是不是check（表一级的）
                if(parameter.left(5).toLower()=="check"){
                    QRegExp get_checkcontent("CHECK\\s*\\((.*)\\)");
                    if(get_checkcontent.indexIn(parameter)==-1){
                        error_code = CREATE_ERROR;
                       std::cout<<"check content cannot be null"<<std::endl;
                        return;
                    }

                    //取出check左右两边的值以及他的符号
                    QRegExp get_checkcontent2("CHECK\\s*\\((\\w*)\\s*(>=|<|=|>|<=)\\s*(\\w*)\\)");
                    get_checkcontent2.indexIn(parameter);


                    QStringList capturedTexts = get_checkcontent2.capturedTexts();
                    QString check_content=get_checkcontent.cap(1);
                    //在这后面调用函数

                }else if(parameter.left(11).toLower()=="primary key"){
                    QRegExp get_primarykey("PRIMARY KEY\\s*\\((.*)\\);");

                    if(get_primarykey.indexIn(parameter)==-1){
                        error_code = CREATE_ERROR;
                        std::cout<<"primary key content cannot be null"<<std::endl;
                        return;
                    }

                    QStringList primaryList = get_primarykey.cap(1).split(",", QString::SkipEmptyParts);  // 拆分为逗号分隔的参数列表



                  //  QString primarykey_content=get_primarykey.cap(1);
                    //可在此调用函数

                }else if(parameter.left(6).toLower()=="unique"){
                    QRegExp get_unique("UNIQUE\\s*\\((.*)\\);");
                    if(get_unique.indexIn(parameter)==-1){
                        error_code = CREATE_ERROR;
                        std::cout<<"unique content cannot be null"<<std::endl;
                        return;
                    }

                    QStringList primaryList = get_unique.cap(1).split(",", QString::SkipEmptyParts);  // 拆分为逗号分隔的参数列表

                    //QString unique_content=get_unique.cap(1);
                }else
                {
                    add_modify_attribute(parameter,1);//1代表add

                }
       }

    }else{//如果创建的是数据库
        QRegExp get_Name("(database|DATABASE)\\s+(\\S*)\\s*;");
        if(get_Name.indexIn(sql)==-1){
            std::cout<<"database name not found or no semicolon"<<std::endl;
            error_code = CREATE_ERROR;
            return;
        }
        name = get_Name.cap(2);//取出数据库名

        //create_database(String databasesname);
    }
    std::cout<<name.toStdString()<<std::endl;
}

void Operation::handle_delete(){
    QRegExp check_from("\\s*(delete|DELETE)\\s+(\\w{4})\\s+");
    check_from.indexIn(sql);
    QString tableName;
    QString conditions;
    if(check_from.cap(2).toLower()!="from"){
        error_code = DELETE_ERROR;
        std::cout<<"from not found"<<std::endl;
        return;
    }
    QRegExp check_semicolon(";$");
    if(check_semicolon.indexIn(sql)==-1){
        error_code = NO_SEMICOLON;
        std::cout<<"semicolon not found"<<std::endl;
        return;
    }
    QRegExp get_table("(from|FROM)\\s+(\\S*)\\s+");
    if(get_table.indexIn(sql)==-1){
        error_code = DELETE_ERROR;
        std::cout<<"table name not found"<<std::endl;
        return;
    }else {
        tableName = get_table.cap(2);
    }
    QRegExp check_where("\\s+(where||WHERE)\\s+");
    if(check_where.indexIn(sql)==-1){
        conditions="";
    }else{
        QRegExp get_condition("(where|WHERE)\\s+(.*);");
        if(get_condition.indexIn(sql)==-1){
            std::cout<<"condition not found"<<std::endl;
            error_code = DELETE_ERROR;
            return;
        }else {
            conditions = get_condition.cap(2);
        }
    }
    std::cout<<conditions.toStdString()<<std::endl;
    std::cout<<tableName.toStdString()<<std::endl;

}

//这个函数用来获取select里要查询的属性名
void Operation::parse_column(QString columns){
    QRegExp check_comma(",\\s*,");
    if(check_comma.indexIn(columns)!=-1){
        error_code = COLUMN_ERROR;
        std::cout<<"wrong input column"<<std::endl;
        return;
    }
    QStringList list = columns.split(",");
    for(QString each:list){
        target_column->push_back(each);
        std::cout<<each.toStdString()<<std::endl;
    }
}


bool Operation:: add_modify_attribute(QString attributeString,int type){//type表示是add还是modify
    //QString parameter = "name VARCHAR NOT NULL UNIQUE DEFAULT 'anonymous'";
    //下面这个用来解析一个属性对应属性名，约束
    QString pattern = "\\b(\\w+)\\b\\s+(\\w+)(?:\\s+(?!NOT NULL|UNIQUE|PRIMARY KEY|CHECK|DEFAULT)(\\w+))?(?:\\s+(NOT NULL|UNIQUE|PRIMARY KEY))?"
                     "(?:\\s+(?!NOT NULL|UNIQUE|PRIMARY KEY|CHECK|DEFAULT)(\\w+))?(?:\\s+(NOT NULL|UNIQUE|PRIMARY KEY))?"
                      "(?:\\s+(?!NOT NULL|UNIQUE|PRIMARY KEY|CHECK|DEFAULT)(\\w+))?(?:\\s+(NOT NULL|UNIQUE|PRIMARY KEY))?"
                      "(?:\\s+(?!NOT NULL|UNIQUE|PRIMARY KEY|DEFAULT|CHECK)(\\w+))?(?:\\s+DEFAULT\\s+(\\S+))?(?:\\s+CHECK\\s*\\((.*)\\))?";
                //(?:\\s+CHECK\\s+\\((.*)\\))?为什么就不行？？？？？？？？？？？
                //   "(?:\\s+CHECK\\s*\\((\\S+)\\))?";
    QRegExp attributeregex(pattern);


    if (attributeregex.indexIn(attributeString) != -1) {
        QStringList capturedTexts = attributeregex.capturedTexts(); // 获取所有匹配结果

            QString name = capturedTexts[1]; // 属性名
            QString type = capturedTexts[2]; // 数据类型
            QString notconstraints = capturedTexts[3]+capturedTexts[5]+capturedTexts[7]+capturedTexts[9]; // 其他错误约束条件，若改string非空，说明有错误约束，则给出错误信息
            QString defaultValue = capturedTexts[10]; // 默认值
            QString check=capturedTexts[11];

            bool isNotNull = capturedTexts.contains("NOT NULL"); // 是否有 "NOT NULL" 约束
            bool isUnique = capturedTexts.contains("UNIQUE"); // 是否有 "UNIQUE" 约束
            bool isPrimaryKey = capturedTexts.contains("PRIMARY KEY"); // 是否为主键

            if(check!=NULL){

                //判断check是否是between
                QRegExp get_checkbetweencontent("CHECK\\s*\\((\\w*)\\s*(>=|<|=|>|<=)\\s*(\\w*)\\)");

                //取出check左右两边的值以及他的符号
                QRegExp get_checkcontent("CHECK\\s*\\((\\w*)\\s*(>=|<|=|>|<=)\\s*(\\w*)\\)");
                get_checkcontent.indexIn(attributeString);
                QStringList checkTexts = get_checkcontent.capturedTexts();
                QString check_content=get_checkcontent.cap(1);
                if(check[1]!=name){
                    std::cout<<"请检查check后的属性名是否正确！"<<endl;
                    return false;
                }
                //在这后面调用函数
            }

            //出现错误约束
            if(notconstraints!=NULL){
                std::cout<<"check your constraint for "<<name.toStdString()<<std::endl;
                error_code = CREATE_ERROR;
                 return false;
            }


            //判断类型有没有错
            if(type.toLower()!="int" && type.toLower()!="float" && type.toLower()!="varchar" && type.toLower()!="char")
            {
             std::cout<<"create error type!"<<std::endl;
             error_code = CREATE_ERROR;
              return false;
             }


            //判断主键和default值，若同时存在，给出错误信息
            if(isPrimaryKey&&defaultValue!=NULL){
                std::cout<<"Primary Key"<<name.toStdString()<<" cannot set default value!"<<std::endl;
                error_code = CREATE_ERROR;
                return false;
            }

            //下面可以调用函数
            return true;
    }
    return false;

}




void Operation::handle_alter(){
    QRegExp check_alterTable("\\s*(alter|ALTER)\\s+(table|TABLE)");
    QString alter_type;//这个用来记录到底是modify add 还是 delete

    if(check_alterTable.indexIn(sql)==-1){
        error_code=ALTER_ERROR;
        std::cout<<"missing word 'table'"<<std::endl;
        return;
    }
    QRegExp get_nameAndType("(table|TABLE)\\s+(\\S*)\\s+(modify|MODIFY|ADD|add|drop|DROP)");
    if(get_nameAndType.indexIn(sql)==-1){
        error_code = ALTER_ERROR;
        std::cout<<"table name not found or invalid alter operation"<<std::endl;
        return;
    }else{
        target_table = get_nameAndType.cap(2);
        alter_type = get_nameAndType.cap(3).toLower();
        std::cout<<target_table.toStdString()<<std::endl;
        std::cout<<alter_type.toStdString()<<std::endl;
    }



    //下面开始分类，具体是alter的哪一类
    if(alter_type=="modify"){//alter table student modify sname varchar(8) unique   Oracle支持没有column的语法，所以这里有无column都可被解析
                                      //ALTER TABLE table_name MODIFY COLUMN column_name data_type;

       // QRegExp get_modify_message(alter_type+"\\s*(column|COLUMN)?\\s+(\\w*)+\\s+(\\w*)\\s*(.*)\\s*;",Qt::CaseInsensitive);
        QRegExp get_modify_message(alter_type+"\\s*(column|COLUMN)?\\s+(.*)\\s*;",Qt::CaseInsensitive);
        if(get_modify_message.indexIn(sql)==-1){
            error_code=ALTER_ERROR;
            std::cout<<"check your "<<std::endl;
            return;
        }

         add_modify_attribute(get_modify_message.cap(2),2);


//        QString modifyColumnName= get_modify_message.cap(2);//modify列的名字
//        QString modifyColumnType= get_modify_message.cap(3);//modify列的类型
//        QString modifyColumnCondition= get_modify_message.cap(4);//modify列的完整性约束

//        std::cout<<"modify column name:"<<modifyColumnName.toStdString()<<std::endl;
//        std::cout<<"modify column type:"<<modifyColumnType.toStdString()<<std::endl;
//        std::cout<<"modify column condition:"<<modifyColumnCondition.toStdString()<<std::endl;

//        QString test="'a'";
//        QString result=is_int_float_varchar_char(test);

//        std::cout<<result.toStdString()<<std::endl;


    }else if(alter_type=="add"){//alter table student add register_date timestamp default now();
        //ALTER TABLE table_name ADD COLUMN column_name data_type;
       // QRegExp get_add_message(alter_type+"\\s*(column|COLUMN)?\\s+(\\w+)+\\s+(\\w*)+\\s+(.*)\\s*;", Qt::CaseInsensitive);
        QRegExp get_add_message(alter_type+"\\s*(column|COLUMN)?\\s+(.*)\\s*;", Qt::CaseInsensitive);

        if(get_add_message.indexIn(sql)==-1){
            error_code=ALTER_ERROR;
            std::cout<<"check your  "<<std::endl;
            return;
        }
         add_modify_attribute(get_add_message.cap(2),1);
//        QString addColumnName= get_add_message.cap(2);//增加列的名字
//        QString addColumnType= get_add_message.cap(3);//增加列的类型
//        QString addColumnCondition= get_add_message.cap(4);//增加列的完整性约束



//        std::cout<<"add column name:"<<addColumnName.toStdString()<<std::endl;
//        std::cout<<"add column type:"<<addColumnType.toStdString()<<std::endl;
//        std::cout<<"add column condition"<<addColumnCondition.toStdString()<<std::endl;



    }else {//alter table student drop register_date;
           //alter table student drop column register_date;
         QRegExp get_drop_message(alter_type+"\\s*(column|COLUMN)?\\s+(\\w+)\\s*;",Qt::CaseInsensitive);

         if(get_drop_message.indexIn(sql)==-1){
             error_code=ALTER_ERROR;
             std::cout<<"check your  "<<std::endl;
             return;
         }
      //  parse_column();
         QString dropColumnName= get_drop_message.cap(2);//drop列的名字
         std::cout<<"drop column name:"<<dropColumnName.toStdString()<<std::endl;

    }

}





void Operation::execute(){
    //在这里判断各种条件是否正确，表与列是否存在
    if(error_code!=0){
        std::cout<<"wrong input"<<std::endl;
        return;
    }
    if(operation_type=="create"){//TODO

    }
}


