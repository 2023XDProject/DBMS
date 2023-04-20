/********************************************************************************
** Form generated from reading UI file 'connectionui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTIONUI_H
#define UI_CONNECTIONUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_connectionUI
{
public:

    void setupUi(QWidget *connectionUI)
    {
        if (connectionUI->objectName().isEmpty())
            connectionUI->setObjectName(QString::fromUtf8("connectionUI"));
        connectionUI->resize(700, 900);

        retranslateUi(connectionUI);

        QMetaObject::connectSlotsByName(connectionUI);
    } // setupUi

    void retranslateUi(QWidget *connectionUI)
    {
        connectionUI->setWindowTitle(QCoreApplication::translate("connectionUI", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class connectionUI: public Ui_connectionUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTIONUI_H
