#include "connectionui.h"
#include "ui_connectionui.h"

connectionUI::connectionUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::connectionUI)
{
    ui->setupUi(this);
}

connectionUI::~connectionUI()
{
    delete ui;
}

void connectionUI::on_pushButton_clicked()
{
    DBName=this->ui->textEdit->toPlainText();
    emit setDBName(DBName);
    this->close();
}

//获取新数据库名称
void connectionUI::getNewDBName(){
     this->show();
}

void connectionUI::on_pushButton_2_clicked()
{
    this->close();
}

