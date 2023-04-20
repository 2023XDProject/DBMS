#include "loginui.h"
#include "ui_loginui.h"

loginUI::loginUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginUI)
{
    ui->setupUi(this);
}

loginUI::~loginUI()
{
    delete ui;
}
