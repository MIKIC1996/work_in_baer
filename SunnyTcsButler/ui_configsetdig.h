/********************************************************************************
** Form generated from reading UI file 'configsetdig.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGSETDIG_H
#define UI_CONFIGSETDIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
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

class Ui_ConfigSetDig
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QTreeWidget *treeWidget;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *item_Box;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *item_remark_edit;
    QLabel *label_5;
    QPlainTextEdit *item_explain;
    QLabel *label_2;
    QTableWidget *attribute_list;
    QLabel *label_4;
    QComboBox *data_type;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *item_ok_btn;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QLineEdit *file_remark_edit;
    QLabel *label_6;
    QPlainTextEdit *file_explain;
    QLabel *file_path_label;
    QHBoxLayout *horizontalLayout;
    QLabel *config_path_label;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *ok_btn;
    QPushButton *cancel_btn;

    void setupUi(QWidget *ConfigSetDig)
    {
        if (ConfigSetDig->objectName().isEmpty())
            ConfigSetDig->setObjectName(QStringLiteral("ConfigSetDig"));
        ConfigSetDig->resize(807, 776);
        verticalLayout_4 = new QVBoxLayout(ConfigSetDig);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        treeWidget = new QTreeWidget(ConfigSetDig);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        horizontalLayout_2->addWidget(treeWidget);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        item_Box = new QGroupBox(ConfigSetDig);
        item_Box->setObjectName(QStringLiteral("item_Box"));
        verticalLayout = new QVBoxLayout(item_Box);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(item_Box);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        item_remark_edit = new QLineEdit(item_Box);
        item_remark_edit->setObjectName(QStringLiteral("item_remark_edit"));

        verticalLayout->addWidget(item_remark_edit);

        label_5 = new QLabel(item_Box);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        item_explain = new QPlainTextEdit(item_Box);
        item_explain->setObjectName(QStringLiteral("item_explain"));

        verticalLayout->addWidget(item_explain);

        label_2 = new QLabel(item_Box);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        attribute_list = new QTableWidget(item_Box);
        if (attribute_list->columnCount() < 2)
            attribute_list->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        attribute_list->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        attribute_list->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        attribute_list->setObjectName(QStringLiteral("attribute_list"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(attribute_list->sizePolicy().hasHeightForWidth());
        attribute_list->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(attribute_list);

        label_4 = new QLabel(item_Box);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        data_type = new QComboBox(item_Box);
        data_type->setObjectName(QStringLiteral("data_type"));

        verticalLayout->addWidget(data_type);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        item_ok_btn = new QPushButton(item_Box);
        item_ok_btn->setObjectName(QStringLiteral("item_ok_btn"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(item_ok_btn->sizePolicy().hasHeightForWidth());
        item_ok_btn->setSizePolicy(sizePolicy1);
        item_ok_btn->setMinimumSize(QSize(0, 25));

        horizontalLayout_4->addWidget(item_ok_btn);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_3->addWidget(item_Box);

        groupBox = new QGroupBox(ConfigSetDig);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        file_remark_edit = new QLineEdit(groupBox);
        file_remark_edit->setObjectName(QStringLiteral("file_remark_edit"));

        verticalLayout_2->addWidget(file_remark_edit);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_2->addWidget(label_6);

        file_explain = new QPlainTextEdit(groupBox);
        file_explain->setObjectName(QStringLiteral("file_explain"));

        verticalLayout_2->addWidget(file_explain);

        file_path_label = new QLabel(groupBox);
        file_path_label->setObjectName(QStringLiteral("file_path_label"));

        verticalLayout_2->addWidget(file_path_label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        config_path_label = new QLabel(groupBox);
        config_path_label->setObjectName(QStringLiteral("config_path_label"));

        horizontalLayout->addWidget(config_path_label);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy2);
        pushButton->setMinimumSize(QSize(70, 0));

        horizontalLayout->addWidget(pushButton);

        horizontalLayout->setStretch(0, 10);
        horizontalLayout->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addWidget(groupBox);

        verticalLayout_3->setStretch(0, 4);
        verticalLayout_3->setStretch(1, 2);

        horizontalLayout_2->addLayout(verticalLayout_3);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);

        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        ok_btn = new QPushButton(ConfigSetDig);
        ok_btn->setObjectName(QStringLiteral("ok_btn"));

        horizontalLayout_3->addWidget(ok_btn);

        cancel_btn = new QPushButton(ConfigSetDig);
        cancel_btn->setObjectName(QStringLiteral("cancel_btn"));

        horizontalLayout_3->addWidget(cancel_btn);


        verticalLayout_4->addLayout(horizontalLayout_3);


        retranslateUi(ConfigSetDig);

        QMetaObject::connectSlotsByName(ConfigSetDig);
    } // setupUi

    void retranslateUi(QWidget *ConfigSetDig)
    {
        ConfigSetDig->setWindowTitle(QApplication::translate("ConfigSetDig", "Form", 0));
        item_Box->setTitle(QApplication::translate("ConfigSetDig", "\345\275\223\345\211\215\346\240\207\347\255\276", 0));
        label->setText(QApplication::translate("ConfigSetDig", "\346\240\207\347\255\276\345\220\215\357\274\232", 0));
        label_5->setText(QApplication::translate("ConfigSetDig", "\346\240\207\347\255\276\345\244\207\346\263\250:", 0));
        label_2->setText(QApplication::translate("ConfigSetDig", "\345\261\236\346\200\247\345\210\227\350\241\250\357\274\232", 0));
        QTableWidgetItem *___qtablewidgetitem = attribute_list->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ConfigSetDig", "\345\261\236\346\200\247", 0));
        QTableWidgetItem *___qtablewidgetitem1 = attribute_list->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ConfigSetDig", "\345\244\207\346\263\250\345\220\215", 0));
        label_4->setText(QApplication::translate("ConfigSetDig", "\346\240\207\347\255\276\346\225\260\346\215\256\347\261\273\345\236\213:", 0));
        data_type->clear();
        data_type->insertItems(0, QStringList()
         << QApplication::translate("ConfigSetDig", "\346\226\207\346\234\254", 0)
         << QApplication::translate("ConfigSetDig", "\346\225\260\345\255\227", 0)
         << QApplication::translate("ConfigSetDig", "\345\270\203\345\260\224", 0)
         << QApplication::translate("ConfigSetDig", "\346\227\240", 0)
        );
        item_ok_btn->setText(QApplication::translate("ConfigSetDig", "\344\277\256\346\224\271", 0));
        groupBox->setTitle(QApplication::translate("ConfigSetDig", "\346\226\207\344\273\266", 0));
        label_3->setText(QApplication::translate("ConfigSetDig", "\346\226\207\344\273\266\345\220\215:", 0));
        label_6->setText(QApplication::translate("ConfigSetDig", "\346\226\207\344\273\266\345\244\207\346\263\250:", 0));
        file_path_label->setText(QApplication::translate("ConfigSetDig", "\346\226\207\344\273\266\350\267\257\345\276\204:", 0));
        config_path_label->setText(QApplication::translate("ConfigSetDig", "\351\205\215\347\275\256\346\226\207\344\273\266\350\267\257\345\276\204:", 0));
        pushButton->setText(QApplication::translate("ConfigSetDig", "\346\233\264\346\224\271", 0));
        ok_btn->setText(QApplication::translate("ConfigSetDig", "\347\241\256\345\256\232", 0));
        cancel_btn->setText(QApplication::translate("ConfigSetDig", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class ConfigSetDig: public Ui_ConfigSetDig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGSETDIG_H
