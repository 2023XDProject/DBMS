#ifndef LOGINUI_H
#define LOGINUI_H

#include <QWidget>

namespace Ui {
class loginUI;
}

class loginUI : public QWidget
{
    Q_OBJECT

public:
    explicit loginUI(QWidget *parent = nullptr);
    ~loginUI();

private:
    Ui::loginUI *ui;
};

#endif // LOGINUI_H
