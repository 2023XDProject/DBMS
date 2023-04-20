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
