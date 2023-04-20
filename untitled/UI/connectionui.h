#ifndef CONNECTIONUI_H
#define CONNECTIONUI_H

#include <QWidget>
#include <QString>

namespace Ui {
class connectionUI;
}

class connectionUI : public QWidget
{
    Q_OBJECT

public:
    explicit connectionUI(QWidget *parent = nullptr);
    ~connectionUI();
    void getNewDBName();//获取新数据库名称

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void setDBName(QString );

private:
    Ui::connectionUI *ui;
    QString DBName="";
};

#endif // CONNECTIONUI_H
