#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateTableInfo();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTableInfo(){
    //添加菜单栏
    QMenuBar *bar = menuBar();
    this->setMenuBar(bar);

    QMenu * fileMenu = bar->addMenu("文件");
    QMenu * helpMenu = bar->addMenu("帮助");

    //工具栏（只可上方停靠，不可移动）
    QToolBar * toolbar = new QToolBar(this);
    toolbar->setIconSize(QSize(100,100));
    toolbar->setAllowedAreas(Qt::TopToolBarArea);
    toolbar->setFixedHeight(50);
    toolbar->setMovable(false);

    //新建连接
    QIcon connectIcon=QIcon("./Icon/connect_icon.jpg");
    QAction *Action1 = fileMenu ->addAction("新建连接");
    Action1->setIcon(connectIcon);
    toolbar->addAction(Action1);
    toolbar->addSeparator();

    //新建查询
    QIcon enquiryIcon=QIcon("./Icon/enquiry_icon.jpg");
    QAction *Action2 = fileMenu ->addAction("新建查询");
    Action2->setIcon(enquiryIcon);
    toolbar->addAction(Action2);
    toolbar->addSeparator();

    this->addToolBar(toolbar);

    QTextEdit * text = new QTextEdit(this);
    //text->setStyleSheet();样式表，先摆了
    setCentralWidget(text);
    //更新左侧连接信息
    updateItemInfo();

    //状态栏（最下方），不一定用得上
        QStatusBar * stBar = statusBar();
        setStatusBar(stBar);
        QLabel * label1 = new QLabel("提示信息",this);
        stBar->addWidget(label1);
        QLabel * label2 = new QLabel("右侧提示信息",this);
        stBar->addPermanentWidget(label2);
}

void MainWindow::updateItemInfo(){
    QDockWidget* Dock1 = new QDockWidget(this);

    Dock1->setAllowedAreas(Qt::LeftDockWidgetArea);

    QTreeWidget *tree=new QTreeWidget(Dock1);
    tree->setHeaderLabel("test");
    tree->setIndentation(10);

    Dock1->setWidget(tree);
    addDockWidget(Qt::LeftDockWidgetArea,Dock1);

    //要从文件中读取该用户有多少表和查询。。。先摆了！

}

