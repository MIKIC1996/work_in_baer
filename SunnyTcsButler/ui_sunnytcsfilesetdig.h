/********************************************************************************
** Form generated from reading UI file 'sunnytcsfilesetdig.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUNNYTCSFILESETDIG_H
#define UI_SUNNYTCSFILESETDIG_H

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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SunnyTcsFileSetDig
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *file_box;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPlainTextEdit *file_explain;
    QHBoxLayout *horizontalLayout_4;
    QTreeWidget *treeWidget;
    QGroupBox *item_box;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_2;
    QPlainTextEdit *item_explain;
    QLabel *label_3;
    QTableWidget *attributes_list;
    QLabel *label;
    QLineEdit *value_edit;
    QLabel *type_label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *save_btn;
    QPushButton *ok_Btn;
    QPushButton *cancel_Btn;

    void setupUi(QWidget *SunnyTcsFileSetDig)
    {
        if (SunnyTcsFileSetDig->objectName().isEmpty())
            SunnyTcsFileSetDig->setObjectName(QStringLiteral("SunnyTcsFileSetDig"));
        SunnyTcsFileSetDig->resize(811, 582);
        verticalLayout_3 = new QVBoxLayout(SunnyTcsFileSetDig);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        file_box = new QGroupBox(SunnyTcsFileSetDig);
        file_box->setObjectName(QStringLiteral("file_box"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(11);
        font.setBold(false);
        font.setWeight(50);
        file_box->setFont(font);
        horizontalLayout_5 = new QHBoxLayout(file_box);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(4, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        file_explain = new QPlainTextEdit(file_box);
        file_explain->setObjectName(QStringLiteral("file_explain"));
        QFont font1;
        font1.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setWeight(50);
        file_explain->setFont(font1);
        file_explain->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout->addWidget(file_explain);


        horizontalLayout_5->addLayout(verticalLayout);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 100);

        verticalLayout_2->addWidget(file_box);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        treeWidget = new QTreeWidget(SunnyTcsFileSetDig);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        horizontalLayout_4->addWidget(treeWidget);

        item_box = new QGroupBox(SunnyTcsFileSetDig);
        item_box->setObjectName(QStringLiteral("item_box"));
        QFont font2;
        font2.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font2.setBold(false);
        font2.setWeight(50);
        item_box->setFont(font2);
        verticalLayout_5 = new QVBoxLayout(item_box);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalSpacer_2 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_2);

        item_explain = new QPlainTextEdit(item_box);
        item_explain->setObjectName(QStringLiteral("item_explain"));
        QFont font3;
        font3.setBold(false);
        font3.setWeight(50);
        item_explain->setFont(font3);
        item_explain->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout_5->addWidget(item_explain);

        label_3 = new QLabel(item_box);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font3);

        verticalLayout_5->addWidget(label_3);

        attributes_list = new QTableWidget(item_box);
        if (attributes_list->columnCount() < 2)
            attributes_list->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        attributes_list->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        attributes_list->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        attributes_list->setObjectName(QStringLiteral("attributes_list"));
        attributes_list->setFont(font3);

        verticalLayout_5->addWidget(attributes_list);

        label = new QLabel(item_box);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font3);

        verticalLayout_5->addWidget(label);

        value_edit = new QLineEdit(item_box);
        value_edit->setObjectName(QStringLiteral("value_edit"));
        value_edit->setFont(font3);

        verticalLayout_5->addWidget(value_edit);

        type_label = new QLabel(item_box);
        type_label->setObjectName(QStringLiteral("type_label"));
        type_label->setFont(font2);

        verticalLayout_5->addWidget(type_label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton = new QPushButton(item_box);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout_5->addLayout(horizontalLayout);


        horizontalLayout_4->addWidget(item_box);

        horizontalLayout_4->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        save_btn = new QPushButton(SunnyTcsFileSetDig);
        save_btn->setObjectName(QStringLiteral("save_btn"));

        horizontalLayout_3->addWidget(save_btn);

        ok_Btn = new QPushButton(SunnyTcsFileSetDig);
        ok_Btn->setObjectName(QStringLiteral("ok_Btn"));

        horizontalLayout_3->addWidget(ok_Btn);

        cancel_Btn = new QPushButton(SunnyTcsFileSetDig);
        cancel_Btn->setObjectName(QStringLiteral("cancel_Btn"));

        horizontalLayout_3->addWidget(cancel_Btn);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalLayout_2->setStretch(0, 4);
        verticalLayout_2->setStretch(1, 10);
        verticalLayout_2->setStretch(2, 1);

        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(SunnyTcsFileSetDig);

        QMetaObject::connectSlotsByName(SunnyTcsFileSetDig);
    } // setupUi

    void retranslateUi(QWidget *SunnyTcsFileSetDig)
    {
        SunnyTcsFileSetDig->setWindowTitle(QApplication::translate("SunnyTcsFileSetDig", "Form", 0));
        file_box->setTitle(QApplication::translate("SunnyTcsFileSetDig", "\346\226\207\344\273\266\345\244\207\346\263\250\345\220\215\342\200\224\342\200\224\346\226\207\344\273\266\345\220\215", 0));
        file_explain->setPlainText(QString());
        item_box->setTitle(QApplication::translate("SunnyTcsFileSetDig", "\345\275\223\345\211\215\346\240\207\347\255\276", 0));
        item_explain->setPlainText(QString());
        label_3->setText(QApplication::translate("SunnyTcsFileSetDig", "\345\261\236\346\200\247\345\210\227\350\241\250", 0));
        QTableWidgetItem *___qtablewidgetitem = attributes_list->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SunnyTcsFileSetDig", "\345\261\236\346\200\247\345\220\215", 0));
        QTableWidgetItem *___qtablewidgetitem1 = attributes_list->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SunnyTcsFileSetDig", "\345\200\274", 0));
        label->setText(QApplication::translate("SunnyTcsFileSetDig", "\350\256\276\347\275\256\345\200\274:", 0));
        type_label->setText(QApplication::translate("SunnyTcsFileSetDig", "\345\200\274\347\261\273\345\236\213\357\274\232\346\226\207\346\234\254", 0));
        pushButton->setText(QApplication::translate("SunnyTcsFileSetDig", "\344\277\256\346\224\271\346\240\207\347\255\276", 0));
        save_btn->setText(QApplication::translate("SunnyTcsFileSetDig", "\344\277\235\345\255\230\345\210\260\346\226\207\344\273\266", 0));
        ok_Btn->setText(QApplication::translate("SunnyTcsFileSetDig", "\344\270\264\346\227\266\344\277\235\345\255\230", 0));
        cancel_Btn->setText(QApplication::translate("SunnyTcsFileSetDig", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class SunnyTcsFileSetDig: public Ui_SunnyTcsFileSetDig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUNNYTCSFILESETDIG_H
