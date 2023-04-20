#include "./UI/mainwindow.h"
#include <qtextcodec.h>
#include <QApplication>
#include "./UI/loginui.h"
int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);
    MainWindow w;
    connectionUI comnectionUI;
    loginUI lui;
    //lui.show();
    w.show();
    //comnectionUI.show();


    return a.exec();
}
