/********************************************************************************
** Form generated from reading UI file 'sunnytcsprocedureconfigdig.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUNNYTCSPROCEDURECONFIGDIG_H
#define UI_SUNNYTCSPROCEDURECONFIGDIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SunnyTcsProcedureConfigDig
{
public:
    QVBoxLayout *verticalLayout_6;
    QLabel *proName;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLineEdit *ProcedureNameEdit;
    QSpacerItem *horizontalSpacer_2;
    QPlainTextEdit *proExplain;
    QGridLayout *gridLayout;
    QPushButton *pushButton_2;
    QPushButton *saveProcedureBtn;
    QPushButton *createActionBtn;
    QPushButton *deleteActionBtn;
    QTabWidget *tabWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QLabel *label;
    QTableWidget *tableWidget;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_2;
    QSpinBox *exeCountSBox;
    QComboBox *Action_CBox;
    QLineEdit *ActionNameEdit;
    QPlainTextEdit *ActionExplainPlainEdit;
    QPushButton *deleteSelectedItemBtn;
    QLabel *label_12;
    QComboBox *A0_valueTypeCBox;
    QStackedWidget *extraPageSWidget;
    QWidget *page;
    QLabel *label_7;
    QLineEdit *xmlAttEdit;
    QPushButton *attAddBtn;
    QLineEdit *xmlNameEdit;
    QListWidget *xmlattsList;
    QLabel *label_8;
    QLabel *label_9;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_10;
    QComboBox *addJsonCBox;
    QStackedWidget *addJsonSWidget;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *jsonValueEdit;
    QComboBox *jsonValueCBox;
    QPushButton *jsonValueBtn;
    QTableWidget *addJsonTable;
    QWidget *page_4;
    QWidget *page_5;
    QPushButton *addActionBtn;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *openFileBtn;
    QMdiArea *mdiArea;

    void setupUi(QWidget *SunnyTcsProcedureConfigDig)
    {
        if (SunnyTcsProcedureConfigDig->objectName().isEmpty())
            SunnyTcsProcedureConfigDig->setObjectName(QStringLiteral("SunnyTcsProcedureConfigDig"));
        SunnyTcsProcedureConfigDig->resize(1119, 843);
        verticalLayout_6 = new QVBoxLayout(SunnyTcsProcedureConfigDig);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        proName = new QLabel(SunnyTcsProcedureConfigDig);
        proName->setObjectName(QStringLiteral("proName"));

        verticalLayout_6->addWidget(proName);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_6 = new QLabel(SunnyTcsProcedureConfigDig);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_4->addWidget(label_6);

        ProcedureNameEdit = new QLineEdit(SunnyTcsProcedureConfigDig);
        ProcedureNameEdit->setObjectName(QStringLiteral("ProcedureNameEdit"));

        horizontalLayout_4->addWidget(ProcedureNameEdit);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_4);

        proExplain = new QPlainTextEdit(SunnyTcsProcedureConfigDig);
        proExplain->setObjectName(QStringLiteral("proExplain"));

        verticalLayout_3->addWidget(proExplain);


        horizontalLayout->addLayout(verticalLayout_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_2 = new QPushButton(SunnyTcsProcedureConfigDig);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        saveProcedureBtn = new QPushButton(SunnyTcsProcedureConfigDig);
        saveProcedureBtn->setObjectName(QStringLiteral("saveProcedureBtn"));

        gridLayout->addWidget(saveProcedureBtn, 0, 0, 1, 1);

        createActionBtn = new QPushButton(SunnyTcsProcedureConfigDig);
        createActionBtn->setObjectName(QStringLiteral("createActionBtn"));

        gridLayout->addWidget(createActionBtn, 2, 0, 1, 1);

        deleteActionBtn = new QPushButton(SunnyTcsProcedureConfigDig);
        deleteActionBtn->setObjectName(QStringLiteral("deleteActionBtn"));

        gridLayout->addWidget(deleteActionBtn, 2, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        verticalLayout_6->addLayout(horizontalLayout);

        tabWidget = new QTabWidget(SunnyTcsProcedureConfigDig);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));

        verticalLayout_6->addWidget(tabWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_5 = new QLabel(SunnyTcsProcedureConfigDig);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 5, 0, 1, 1);

        label = new QLabel(SunnyTcsProcedureConfigDig);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        tableWidget = new QTableWidget(SunnyTcsProcedureConfigDig);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout_2->addWidget(tableWidget, 5, 2, 1, 1);

        label_3 = new QLabel(SunnyTcsProcedureConfigDig);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        label_4 = new QLabel(SunnyTcsProcedureConfigDig);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 4, 0, 1, 1);

        label_2 = new QLabel(SunnyTcsProcedureConfigDig);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 3, 0, 1, 1);

        exeCountSBox = new QSpinBox(SunnyTcsProcedureConfigDig);
        exeCountSBox->setObjectName(QStringLiteral("exeCountSBox"));

        gridLayout_2->addWidget(exeCountSBox, 1, 2, 1, 1);

        Action_CBox = new QComboBox(SunnyTcsProcedureConfigDig);
        Action_CBox->setObjectName(QStringLiteral("Action_CBox"));

        gridLayout_2->addWidget(Action_CBox, 0, 2, 1, 1);

        ActionNameEdit = new QLineEdit(SunnyTcsProcedureConfigDig);
        ActionNameEdit->setObjectName(QStringLiteral("ActionNameEdit"));

        gridLayout_2->addWidget(ActionNameEdit, 3, 2, 1, 1);

        ActionExplainPlainEdit = new QPlainTextEdit(SunnyTcsProcedureConfigDig);
        ActionExplainPlainEdit->setObjectName(QStringLiteral("ActionExplainPlainEdit"));

        gridLayout_2->addWidget(ActionExplainPlainEdit, 4, 2, 1, 1);

        deleteSelectedItemBtn = new QPushButton(SunnyTcsProcedureConfigDig);
        deleteSelectedItemBtn->setObjectName(QStringLiteral("deleteSelectedItemBtn"));

        gridLayout_2->addWidget(deleteSelectedItemBtn, 6, 2, 1, 1);

        label_12 = new QLabel(SunnyTcsProcedureConfigDig);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_2->addWidget(label_12, 2, 0, 1, 1);

        A0_valueTypeCBox = new QComboBox(SunnyTcsProcedureConfigDig);
        A0_valueTypeCBox->setObjectName(QStringLiteral("A0_valueTypeCBox"));

        gridLayout_2->addWidget(A0_valueTypeCBox, 2, 2, 1, 1);


        verticalLayout_5->addLayout(gridLayout_2);

        extraPageSWidget = new QStackedWidget(SunnyTcsProcedureConfigDig);
        extraPageSWidget->setObjectName(QStringLiteral("extraPageSWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        label_7 = new QLabel(page);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 20, 161, 21));
        xmlAttEdit = new QLineEdit(page);
        xmlAttEdit->setObjectName(QStringLiteral("xmlAttEdit"));
        xmlAttEdit->setGeometry(QRect(90, 100, 121, 21));
        attAddBtn = new QPushButton(page);
        attAddBtn->setObjectName(QStringLiteral("attAddBtn"));
        attAddBtn->setGeometry(QRect(150, 130, 61, 28));
        xmlNameEdit = new QLineEdit(page);
        xmlNameEdit->setObjectName(QStringLiteral("xmlNameEdit"));
        xmlNameEdit->setGeometry(QRect(90, 70, 121, 21));
        xmlattsList = new QListWidget(page);
        xmlattsList->setObjectName(QStringLiteral("xmlattsList"));
        xmlattsList->setGeometry(QRect(10, 170, 201, 211));
        label_8 = new QLabel(page);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 70, 72, 15));
        label_9 = new QLabel(page);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 100, 72, 15));
        extraPageSWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        verticalLayout_2 = new QVBoxLayout(page_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_10 = new QLabel(page_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_2->addWidget(label_10);

        addJsonCBox = new QComboBox(page_2);
        addJsonCBox->setObjectName(QStringLiteral("addJsonCBox"));

        verticalLayout_2->addWidget(addJsonCBox);

        addJsonSWidget = new QStackedWidget(page_2);
        addJsonSWidget->setObjectName(QStringLiteral("addJsonSWidget"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        verticalLayout_7 = new QVBoxLayout(page_3);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        label_11 = new QLabel(page_3);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout_7->addWidget(label_11);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        jsonValueEdit = new QLineEdit(page_3);
        jsonValueEdit->setObjectName(QStringLiteral("jsonValueEdit"));

        verticalLayout_4->addWidget(jsonValueEdit);

        jsonValueCBox = new QComboBox(page_3);
        jsonValueCBox->setObjectName(QStringLiteral("jsonValueCBox"));

        verticalLayout_4->addWidget(jsonValueCBox);


        horizontalLayout_5->addLayout(verticalLayout_4);

        jsonValueBtn = new QPushButton(page_3);
        jsonValueBtn->setObjectName(QStringLiteral("jsonValueBtn"));

        horizontalLayout_5->addWidget(jsonValueBtn);


        verticalLayout_7->addLayout(horizontalLayout_5);

        addJsonTable = new QTableWidget(page_3);
        if (addJsonTable->columnCount() < 2)
            addJsonTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        addJsonTable->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        addJsonTable->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        addJsonTable->setObjectName(QStringLiteral("addJsonTable"));

        verticalLayout_7->addWidget(addJsonTable);

        addJsonSWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        addJsonSWidget->addWidget(page_4);

        verticalLayout_2->addWidget(addJsonSWidget);

        extraPageSWidget->addWidget(page_2);
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        extraPageSWidget->addWidget(page_5);

        verticalLayout_5->addWidget(extraPageSWidget);

        addActionBtn = new QPushButton(SunnyTcsProcedureConfigDig);
        addActionBtn->setObjectName(QStringLiteral("addActionBtn"));

        verticalLayout_5->addWidget(addActionBtn);

        verticalLayout_5->setStretch(0, 1);
        verticalLayout_5->setStretch(1, 2);

        horizontalLayout_3->addLayout(verticalLayout_5);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        openFileBtn = new QPushButton(SunnyTcsProcedureConfigDig);
        openFileBtn->setObjectName(QStringLiteral("openFileBtn"));

        horizontalLayout_2->addWidget(openFileBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        mdiArea = new QMdiArea(SunnyTcsProcedureConfigDig);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));

        verticalLayout->addWidget(mdiArea);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalLayout_3->setStretch(0, 2);
        horizontalLayout_3->setStretch(1, 7);

        verticalLayout_6->addLayout(horizontalLayout_3);


        retranslateUi(SunnyTcsProcedureConfigDig);

        tabWidget->setCurrentIndex(-1);
        extraPageSWidget->setCurrentIndex(2);
        addJsonSWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SunnyTcsProcedureConfigDig);
    } // setupUi

    void retranslateUi(QWidget *SunnyTcsProcedureConfigDig)
    {
        SunnyTcsProcedureConfigDig->setWindowTitle(QApplication::translate("SunnyTcsProcedureConfigDig", "Form", 0));
        proName->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\346\265\201\347\250\213\345\220\215", 0));
        label_6->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\346\265\201\347\250\213\345\220\215", 0));
        pushButton_2->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\345\217\226\346\266\210", 0));
        saveProcedureBtn->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\344\277\235\345\255\230\346\265\201\347\250\213", 0));
        createActionBtn->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\346\267\273\345\212\240\345\212\250\344\275\234", 0));
        deleteActionBtn->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\345\210\240\351\231\244\345\212\250\344\275\234", 0));
        label_5->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\347\233\256\346\240\207\346\240\207\347\255\276", 0));
        label->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\345\212\250\344\275\234\347\261\273\345\236\213", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\347\233\256\346\240\207\346\240\207\347\255\276", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\346\226\207\344\273\266\350\267\257\345\276\204", 0));
        label_3->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\346\211\247\350\241\214\346\254\241\346\225\260", 0));
        label_4->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\345\212\250\344\275\234\350\257\264\346\230\216", 0));
        label_2->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\345\212\250\344\275\234\345\220\215", 0));
        Action_CBox->clear();
        Action_CBox->insertItems(0, QStringList()
         << QApplication::translate("SunnyTcsProcedureConfigDig", "\344\277\256\346\224\271\345\200\274", 0)
         << QApplication::translate("SunnyTcsProcedureConfigDig", "\346\267\273\345\212\240xml\346\240\207\347\255\276", 0)
         << QApplication::translate("SunnyTcsProcedureConfigDig", "\345\210\240\351\231\244xml\346\240\207\347\255\276", 0)
         << QApplication::translate("SunnyTcsProcedureConfigDig", "\345\261\236\346\200\247\344\277\256\346\224\271", 0)
         << QApplication::translate("SunnyTcsProcedureConfigDig", "\346\267\273\345\212\240json\345\257\271\350\261\241/\345\200\274", 0)
         << QApplication::translate("SunnyTcsProcedureConfigDig", "\345\210\240\351\231\244json\345\257\271\350\261\241/\345\200\274", 0)
        );
        deleteSelectedItemBtn->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\345\210\240\351\231\244\351\200\211\344\270\255\346\240\207\347\255\276", 0));
        label_12->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\346\225\260\346\215\256\347\261\273\345\236\213", 0));
        A0_valueTypeCBox->clear();
        A0_valueTypeCBox->insertItems(0, QStringList()
         << QApplication::translate("SunnyTcsProcedureConfigDig", "\346\226\207\346\234\254", 0)
         << QApplication::translate("SunnyTcsProcedureConfigDig", "\346\225\264\345\236\213\346\225\260", 0)
        );
        label_7->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\346\267\273\345\212\240xml\351\231\204\351\241\265", 0));
        attAddBtn->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\346\267\273\345\212\240", 0));
        label_8->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\346\240\207\347\255\276\345\220\215", 0));
        label_9->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\346\240\207\347\255\276\345\261\236\346\200\247", 0));
        label_10->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\346\267\273\345\212\240Json\351\231\204\351\241\265", 0));
        addJsonCBox->clear();
        addJsonCBox->insertItems(0, QStringList()
         << QApplication::translate("SunnyTcsProcedureConfigDig", "\345\257\271\350\261\241", 0)
         << QApplication::translate("SunnyTcsProcedureConfigDig", "\345\200\274", 0)
        );
        label_11->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\345\200\274\345\210\227\350\241\250", 0));
        jsonValueCBox->clear();
        jsonValueCBox->insertItems(0, QStringList()
         << QApplication::translate("SunnyTcsProcedureConfigDig", "\346\226\207\346\234\254", 0)
         << QApplication::translate("SunnyTcsProcedureConfigDig", "\346\225\260\345\200\274", 0)
        );
        jsonValueBtn->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\346\267\273\345\212\240", 0));
        QTableWidgetItem *___qtablewidgetitem2 = addJsonTable->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\345\200\274\345\220\215", 0));
        QTableWidgetItem *___qtablewidgetitem3 = addJsonTable->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\347\261\273\345\236\213", 0));
        addActionBtn->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\344\277\235\345\255\230\345\212\250\344\275\234", 0));
        openFileBtn->setText(QApplication::translate("SunnyTcsProcedureConfigDig", "\346\211\223\345\274\200\346\226\207\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class SunnyTcsProcedureConfigDig: public Ui_SunnyTcsProcedureConfigDig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUNNYTCSPROCEDURECONFIGDIG_H
