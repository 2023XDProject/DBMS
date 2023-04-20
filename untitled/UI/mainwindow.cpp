#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),CRKDBMSD_(new CRKDBMSDoc())
    , ui(new Ui::MainWindow),cUI_(new connectionUI())
{
    ui->setupUi(this);
    updateTableInfo();
    CRKDBMSD_->OnNewDocument();
    //绑定接受新数据库名称界面和此界面
    connect(cUI_, SIGNAL(setDBName(QString )), this, SLOT(receiveDBName(QString )),Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete CRKDBMSD_;
    delete bar;
    delete fileMenu,helpMenu;
    delete text;
    delete stBar;
    delete label1,label2;
    delete toolbar;
    delete btn1,btn2,btn3,btn4,btn5;
}

void MainWindow::updateTableInfo(){
    //添加菜单栏
    bar = menuBar();
    this->setMenuBar(bar);

    fileMenu = bar->addMenu("文件");
    helpMenu = bar->addMenu("帮助");

    //更新工具栏
    updateToolBar();

    //添加中心编辑区域
    text = new QTextEdit(this);
    //text->setStyleSheet();样式表，先摆了
    setCentralWidget(text);
    //更新左侧连接信息
    updateItemInfo();

    //状态栏（最下方），不一定用得上
        stBar = statusBar();
        setStatusBar(stBar);
        label1 = new QLabel("提示信息",this);
        stBar->addWidget(label1);
        label2 = new QLabel("右侧提示信息",this);
        stBar->addPermanentWidget(label2);
}

//更新工具栏
void MainWindow::updateToolBar(){
    //工具栏（只可上方停靠，不可移动）
    toolbar = new QToolBar(this);
    toolbar->setIconSize(QSize(100,100));
    toolbar->setAllowedAreas(Qt::TopToolBarArea);
    toolbar->setFixedHeight(80);
    toolbar->setMovable(false);

    //新建数据库
    QIcon CreateDBIcon=QIcon("./Icon/createDB_icon.jpg");
    btn1= new QToolButton(toolbar);
    btn1->setIconSize(QSize(20,20));//为什么没用呢
    btn1->setIcon(CreateDBIcon);
    btn1->setFixedSize(70,70);
    btn1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn1->setText(QString::fromLocal8Bit("新建数据库" ));
    toolbar->addWidget(btn1);
    toolbar->addSeparator();
    connect(btn1, SIGNAL(clicked(bool)), this, SLOT(createDB()));

    //新建查询
    QIcon enquiryIcon=QIcon("./Icon/enquiry_icon.jpg");
    btn2= new QToolButton(toolbar);
    btn2->setIconSize(QSize(20,20));
    btn2->setIcon(enquiryIcon);
    btn2->setFixedSize(70,70);
    btn2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn2->setText(QString::fromLocal8Bit("新建查询" ));
    toolbar->addWidget(btn2);
    toolbar->addSeparator();
    connect(btn2, SIGNAL(clicked(bool)), this, SLOT(createEnquiry()));

    //新建用户
    QIcon createUserIcon=QIcon("./Icon/createUser_icon.jpg");
    btn3= new QToolButton(toolbar);
    btn3->setIconSize(QSize(20,20));
    btn3->setIcon(createUserIcon);
    btn3->setFixedSize(70,70);
    btn3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn3->setText(QString::fromLocal8Bit("新建用户" ));
    toolbar->addWidget(btn3);
    toolbar->addSeparator();
    connect(btn3, SIGNAL(clicked(bool)), this, SLOT(createUser()));

    //登录
    QIcon loginIcon=QIcon("./Icon/login_icon.jpg");
    btn4= new QToolButton(toolbar);
    btn4->setIconSize(QSize(20,20));
    btn4->setIcon(loginIcon);
    btn4->setFixedSize(70,70);
    btn4->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn4->setText(QString::fromLocal8Bit("登录" ));
    toolbar->addWidget(btn4);
    toolbar->addSeparator();
    connect(btn4, SIGNAL(clicked(bool)), this, SLOT(login()));

    //运行
    QIcon runIcon=QIcon("./Icon/run_icon.jpg");
    btn5= new QToolButton(toolbar);
    btn5->setIconSize(QSize(20,20));
    btn5->setIcon(runIcon);
    btn5->setFixedSize(70,70);
    btn5->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn5->setText(QString::fromLocal8Bit("运行" ));
    toolbar->addWidget(btn5);
    toolbar->addSeparator();
    connect(btn5, SIGNAL(clicked(bool)), this, SLOT(run()));

    this->addToolBar(toolbar);
}

//更新左侧连接信息(未完成)
void MainWindow::updateItemInfo(){
    QDockWidget* Dock1 = new QDockWidget(this);

    Dock1->setAllowedAreas(Qt::LeftDockWidgetArea);

    QTreeWidget *tree=new QTreeWidget(Dock1);
    tree->setHeaderLabel("test");
    tree->setIndentation(10);

    Dock1->setWidget(tree);
    addDockWidget(Qt::LeftDockWidgetArea,Dock1);

    //TODO:要从文件中读取该用户有多少表和查询。。。先摆了！

}

//新建数据库
bool MainWindow::createDB(){
    cUI_->show();
}

//接受新建数据库
void MainWindow::receiveDBName(QString Name){
    DBName_=Name;
    qDebug()<<DBName_;
    //bool temp=CRKDBMSD_->newDocument(DBName_.toStdString());
}

//新建查询
bool MainWindow::createEnquiry(){

}

//新建用户
bool MainWindow::createUser(){
     //弹出新建用户UI
}

//登录
bool MainWindow::login(){
     //弹出登录UI
}

//运行查询
bool MainWindow::run(){
    bool temp=false;
    QString tempText=text->toPlainText();
    //qDebug()<<temp;
    if(tempText.isNull()){
        return false;
    }else{
        temp=CRKDBMSD_->matchQSLType(tempText);
        return temp;
    }

    //if()
}

