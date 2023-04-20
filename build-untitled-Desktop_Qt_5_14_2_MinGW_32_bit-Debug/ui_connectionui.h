/********************************************************************************
** Form generated from reading UI file 'connectionui.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTIONUI_H
#define UI_CONNECTIONUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_connectionUI
{
public:
    QLabel *label;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *connectionUI)
    {
        if (connectionUI->objectName().isEmpty())
            connectionUI->setObjectName(QString::fromUtf8("connectionUI"));
        connectionUI->resize(600, 400);
        label = new QLabel(connectionUI);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 50, 291, 91));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        textEdit = new QTextEdit(connectionUI);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(90, 140, 391, 64));
        pushButton = new QPushButton(connectionUI);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(80, 310, 101, 41));
        QFont font1;
        font1.setPointSize(11);
        pushButton->setFont(font1);
        pushButton_2 = new QPushButton(connectionUI);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(390, 310, 101, 41));
        pushButton_2->setFont(font1);

        retranslateUi(connectionUI);

        QMetaObject::connectSlotsByName(connectionUI);
    } // setupUi

    void retranslateUi(QWidget *connectionUI)
    {
        connectionUI->setWindowTitle(QCoreApplication::translate("connectionUI", "Form", nullptr));
        label->setText(QCoreApplication::translate("connectionUI", "\346\226\260\345\273\272\346\225\260\346\215\256\345\272\223\345\220\215\347\247\260\357\274\232", nullptr));
        pushButton->setText(QCoreApplication::translate("connectionUI", "\345\210\233\345\273\272", nullptr));
        pushButton_2->setText(QCoreApplication::translate("connectionUI", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class connectionUI: public Ui_connectionUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTIONUI_H
