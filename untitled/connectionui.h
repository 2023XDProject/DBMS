#ifndef CONNECTIONUI_H
#define CONNECTIONUI_H

#include <QWidget>

namespace Ui {
class connectionUI;
}

class connectionUI : public QWidget
{
    Q_OBJECT

public:
    explicit connectionUI(QWidget *parent = nullptr);
    ~connectionUI();

private:
    Ui::connectionUI *ui;
};

#endif // CONNECTIONUI_H
