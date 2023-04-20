/********************************************************************************
** Form generated from reading UI file 'loginui.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINUI_H
#define UI_LOGINUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginUI
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *loginUI)
    {
        if (loginUI->objectName().isEmpty())
            loginUI->setObjectName(QString::fromUtf8("loginUI"));
        loginUI->resize(700, 900);
        pushButton = new QPushButton(loginUI);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(70, 800, 121, 51));
        QFont font;
        font.setPointSize(16);
        pushButton->setFont(font);
        pushButton_2 = new QPushButton(loginUI);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(510, 800, 121, 51));

        retranslateUi(loginUI);

        QMetaObject::connectSlotsByName(loginUI);
    } // setupUi

    void retranslateUi(QWidget *loginUI)
    {
        loginUI->setWindowTitle(QCoreApplication::translate("loginUI", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("loginUI", "\347\241\256\345\256\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("loginUI", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginUI: public Ui_loginUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINUI_H
