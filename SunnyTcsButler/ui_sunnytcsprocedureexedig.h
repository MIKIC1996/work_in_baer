/********************************************************************************
** Form generated from reading UI file 'sunnytcsprocedureexedig.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUNNYTCSPROCEDUREEXEDIG_H
#define UI_SUNNYTCSPROCEDUREEXEDIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SunnyTcsProcedureExeDig
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *actionBox;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QPlainTextEdit *actionTEdit;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *exeBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_9;
    QLineEdit *A0_valueEdit;
    QWidget *page_2;
    QLabel *label_2;
    QTableWidget *tableWidget;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_4;
    QWidget *page_3;
    QLabel *label_3;
    QTreeWidget *treeWidget;
    QTableView *tableView;
    QPushButton *pushButton_3;
    QWidget *page_4;
    QLabel *label_4;
    QTableWidget *tableWidget_2;
    QWidget *page_5;
    QLabel *label_5;
    QTableWidget *tableWidget_3;
    QPushButton *pushButton_6;
    QLabel *label_13;
    QWidget *page_6;
    QLabel *label_6;
    QTreeWidget *treeWidget_2;
    QPushButton *pushButton_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *lastBtn;
    QPushButton *nextBtn;
    QPushButton *saveBtn;

    void setupUi(QWidget *SunnyTcsProcedureExeDig)
    {
        if (SunnyTcsProcedureExeDig->objectName().isEmpty())
            SunnyTcsProcedureExeDig->setObjectName(QStringLiteral("SunnyTcsProcedureExeDig"));
        SunnyTcsProcedureExeDig->resize(682, 463);
        verticalLayout = new QVBoxLayout(SunnyTcsProcedureExeDig);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        actionBox = new QGroupBox(SunnyTcsProcedureExeDig);
        actionBox->setObjectName(QStringLiteral("actionBox"));
        verticalLayout_3 = new QVBoxLayout(actionBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer);

        actionTEdit = new QPlainTextEdit(actionBox);
        actionTEdit->setObjectName(QStringLiteral("actionTEdit"));
        actionTEdit->setReadOnly(true);

        verticalLayout_3->addWidget(actionTEdit);


        verticalLayout->addWidget(actionBox);

        stackedWidget = new QStackedWidget(SunnyTcsProcedureExeDig);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        verticalLayout_2 = new QVBoxLayout(page);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        exeBox = new QGroupBox(page);
        exeBox->setObjectName(QStringLiteral("exeBox"));
        horizontalLayout_3 = new QHBoxLayout(exeBox);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_9 = new QLabel(exeBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_3->addWidget(label_9);

        A0_valueEdit = new QLineEdit(exeBox);
        A0_valueEdit->setObjectName(QStringLiteral("A0_valueEdit"));

        horizontalLayout_3->addWidget(A0_valueEdit);


        verticalLayout_2->addWidget(exeBox);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        label_2 = new QLabel(page_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(250, 10, 161, 31));
        tableWidget = new QTableWidget(page_2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(70, 140, 581, 121));
        label_10 = new QLabel(page_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 110, 91, 16));
        label_11 = new QLabel(page_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 50, 91, 16));
        label_12 = new QLabel(page_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(80, 80, 72, 15));
        lineEdit_2 = new QLineEdit(page_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(140, 80, 511, 21));
        pushButton_4 = new QPushButton(page_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(560, 270, 93, 28));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        label_3 = new QLabel(page_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 20, 111, 41));
        treeWidget = new QTreeWidget(page_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(40, 70, 161, 231));
        tableView = new QTableView(page_3);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(210, 70, 231, 231));
        pushButton_3 = new QPushButton(page_3);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(500, 90, 93, 28));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        label_4 = new QLabel(page_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(60, 20, 121, 31));
        tableWidget_2 = new QTableWidget(page_4);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(60, 60, 541, 231));
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        label_5 = new QLabel(page_5);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(290, 20, 72, 16));
        tableWidget_3 = new QTableWidget(page_5);
        tableWidget_3->setObjectName(QStringLiteral("tableWidget_3"));
        tableWidget_3->setGeometry(QRect(20, 90, 461, 201));
        pushButton_6 = new QPushButton(page_5);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(510, 90, 93, 28));
        label_13 = new QLabel(page_5);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(20, 50, 161, 31));
        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QStringLiteral("page_6"));
        label_6 = new QLabel(page_6);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(260, 20, 72, 15));
        treeWidget_2 = new QTreeWidget(page_6);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        treeWidget_2->setHeaderItem(__qtreewidgetitem1);
        treeWidget_2->setObjectName(QStringLiteral("treeWidget_2"));
        treeWidget_2->setGeometry(QRect(40, 50, 181, 241));
        pushButton_5 = new QPushButton(page_6);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(490, 70, 93, 28));
        stackedWidget->addWidget(page_6);

        verticalLayout->addWidget(stackedWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lastBtn = new QPushButton(SunnyTcsProcedureExeDig);
        lastBtn->setObjectName(QStringLiteral("lastBtn"));

        horizontalLayout->addWidget(lastBtn);

        nextBtn = new QPushButton(SunnyTcsProcedureExeDig);
        nextBtn->setObjectName(QStringLiteral("nextBtn"));

        horizontalLayout->addWidget(nextBtn);

        saveBtn = new QPushButton(SunnyTcsProcedureExeDig);
        saveBtn->setObjectName(QStringLiteral("saveBtn"));

        horizontalLayout->addWidget(saveBtn);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 3);
        verticalLayout->setStretch(2, 1);

        retranslateUi(SunnyTcsProcedureExeDig);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SunnyTcsProcedureExeDig);
    } // setupUi

    void retranslateUi(QWidget *SunnyTcsProcedureExeDig)
    {
        SunnyTcsProcedureExeDig->setWindowTitle(QApplication::translate("SunnyTcsProcedureExeDig", "Form", 0));
        actionBox->setTitle(QApplication::translate("SunnyTcsProcedureExeDig", "GroupBox", 0));
        exeBox->setTitle(QApplication::translate("SunnyTcsProcedureExeDig", "\344\277\256\346\224\271\345\200\274", 0));
        label_9->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\350\276\223\345\205\245\345\200\274\357\274\232", 0));
        label_2->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\346\267\273\345\212\240xml\346\240\207\347\255\276", 0));
        label_10->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\346\267\273\345\212\240\345\261\236\346\200\247\345\200\274", 0));
        label_11->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\350\256\276\347\275\256\346\240\207\347\255\276\345\200\274", 0));
        label_12->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\346\240\207\347\255\276\345\220\215", 0));
        pushButton_4->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\346\267\273\345\212\240", 0));
        label_3->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\345\210\240\351\231\244xml\346\240\207\347\255\276", 0));
        pushButton_3->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\345\210\240\351\231\244", 0));
        label_4->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\344\277\256\346\224\271xml\345\261\236\346\200\247", 0));
        label_5->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\346\267\273\345\212\240json", 0));
        pushButton_6->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\346\267\273\345\212\240", 0));
        label_13->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\345\275\223\345\211\215\346\267\273\345\212\240\347\261\273\345\236\213\357\274\232", 0));
        label_6->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\345\210\240\351\231\244json", 0));
        pushButton_5->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\345\210\240\351\231\244", 0));
        lastBtn->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\344\270\212\344\270\200\346\255\245", 0));
        nextBtn->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\344\270\213\344\270\200\346\255\245", 0));
        saveBtn->setText(QApplication::translate("SunnyTcsProcedureExeDig", "\344\277\235\345\255\230", 0));
    } // retranslateUi

};

namespace Ui {
    class SunnyTcsProcedureExeDig: public Ui_SunnyTcsProcedureExeDig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUNNYTCSPROCEDUREEXEDIG_H
