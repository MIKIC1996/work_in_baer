/********************************************************************************
** Form generated from reading UI file 'sunnytcsprocedurechilddig.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUNNYTCSPROCEDURECHILDDIG_H
#define UI_SUNNYTCSPROCEDURECHILDDIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SunnyTcsProcedureChildDig
{
public:
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QPushButton *okBtn;

    void setupUi(QWidget *SunnyTcsProcedureChildDig)
    {
        if (SunnyTcsProcedureChildDig->objectName().isEmpty())
            SunnyTcsProcedureChildDig->setObjectName(QStringLiteral("SunnyTcsProcedureChildDig"));
        SunnyTcsProcedureChildDig->resize(516, 443);
        verticalLayout = new QVBoxLayout(SunnyTcsProcedureChildDig);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        treeWidget = new QTreeWidget(SunnyTcsProcedureChildDig);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout->addWidget(treeWidget);

        okBtn = new QPushButton(SunnyTcsProcedureChildDig);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        verticalLayout->addWidget(okBtn);


        retranslateUi(SunnyTcsProcedureChildDig);

        QMetaObject::connectSlotsByName(SunnyTcsProcedureChildDig);
    } // setupUi

    void retranslateUi(QWidget *SunnyTcsProcedureChildDig)
    {
        SunnyTcsProcedureChildDig->setWindowTitle(QApplication::translate("SunnyTcsProcedureChildDig", "Form", 0));
        okBtn->setText(QApplication::translate("SunnyTcsProcedureChildDig", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class SunnyTcsProcedureChildDig: public Ui_SunnyTcsProcedureChildDig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUNNYTCSPROCEDURECHILDDIG_H
