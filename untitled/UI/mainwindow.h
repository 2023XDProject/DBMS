#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "connectionui.h"
#include "../Logic/CRKDBMSDoc.h"
#include "qobjectdefs.h"

#include <QMainWindow>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QDebug>
#include <QDockWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTextEdit>
#include <QWidgetAction>
#include <QPushButton>
#include <QToolButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateTableInfo();
    void updateItemInfo();
    void updateToolBar();

signals:
    //void clicked(bool);

private slots:
    bool createDB();//新建数据库
    bool createEnquiry();//新建查询
    bool createUser();//新建用户
    bool login();//登录
    bool run();//运行查询
private:
    Ui::MainWindow *ui;
    //菜单栏组件
    QMenuBar *bar;
    QMenu * fileMenu,* helpMenu;
    //中心编辑区域组件
    QTextEdit * text;
    //状态栏组件
    QStatusBar * stBar;
    QLabel * label1,* label2;
    //工具栏组件
    QToolBar * toolbar;
    QToolButton * btn1,* btn2,* btn3,* btn4,* btn5;
    CRKDBMSDoc *CRKDBMSD_;
};
#endif // MAINWINDOW_H
