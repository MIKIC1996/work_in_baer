/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *close_action;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_14;
    QTabWidget *main_tabwidget;
    QWidget *home_tab;
    QHBoxLayout *horizontalLayout_14;
    QToolButton *start_all;
    QToolButton *close_all;
    QToolButton *toolButton_2;
    QWidget *config_tab;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *load_btn;
    QToolButton *delelte_btn;
    QPushButton *modify_btn;
    QToolButton *file_modify_btn;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_15;
    QToolButton *createProBtn;
    QToolButton *modifyProBtn;
    QToolButton *deleteProBtn;
    QToolButton *exeProBtn;
    QWidget *tab;
    QPushButton *flush_cycle;
    QStackedWidget *main_widget;
    QWidget *open_page;
    QVBoxLayout *verticalLayout_13;
    QGroupBox *kernel_box;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_7;
    QLabel *kernel_img;
    QVBoxLayout *verticalLayout_7;
    QLabel *label;
    QLabel *kernel_state;
    QVBoxLayout *verticalLayout;
    QPushButton *kernel_start;
    QPushButton *kernel_close;
    QSpacerItem *horizontalSpacer;
    QGroupBox *broker_box;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_8;
    QLabel *broker_img;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_2;
    QLabel *broker_state;
    QVBoxLayout *verticalLayout_2;
    QPushButton *broker_start;
    QPushButton *broker_close;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *data_box;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_9;
    QLabel *data_img;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_3;
    QLabel *data_state;
    QVBoxLayout *verticalLayout_3;
    QPushButton *data_start;
    QPushButton *data_close;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *log_box;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_10;
    QLabel *log_img;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_4;
    QLabel *log_state;
    QVBoxLayout *verticalLayout_4;
    QPushButton *log_start;
    QPushButton *log_close;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *inter_box;
    QHBoxLayout *horizontalLayout_13;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_12;
    QLabel *inter_img;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_6;
    QLabel *connector_state;
    QVBoxLayout *verticalLayout_6;
    QPushButton *inter_start;
    QPushButton *inter_close;
    QSpacerItem *horizontalSpacer_6;
    QGroupBox *super_box;
    QHBoxLayout *horizontalLayout_12;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_11;
    QLabel *super_img;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_5;
    QLabel *super_state;
    QVBoxLayout *verticalLayout_5;
    QPushButton *super_start;
    QPushButton *super_close;
    QSpacerItem *horizontalSpacer_5;
    QWidget *config_page;
    QVBoxLayout *verticalLayout_15;
    QTableWidget *config_table;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_16;
    QListWidget *procedureList;
    QWidget *page;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(417, 749);
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/image/9.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        close_action = new QAction(MainWindow);
        close_action->setObjectName(QStringLiteral("close_action"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix1/res/img/139.png"), QSize(), QIcon::Normal, QIcon::Off);
        close_action->setIcon(icon1);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_14 = new QVBoxLayout(centralWidget);
        verticalLayout_14->setSpacing(1);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(3, -1, 3, 0);
        main_tabwidget = new QTabWidget(centralWidget);
        main_tabwidget->setObjectName(QStringLiteral("main_tabwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(main_tabwidget->sizePolicy().hasHeightForWidth());
        main_tabwidget->setSizePolicy(sizePolicy);
        main_tabwidget->setMinimumSize(QSize(0, 100));
        home_tab = new QWidget();
        home_tab->setObjectName(QStringLiteral("home_tab"));
        horizontalLayout_14 = new QHBoxLayout(home_tab);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        start_all = new QToolButton(home_tab);
        start_all->setObjectName(QStringLiteral("start_all"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(start_all->sizePolicy().hasHeightForWidth());
        start_all->setSizePolicy(sizePolicy1);

        horizontalLayout_14->addWidget(start_all);

        close_all = new QToolButton(home_tab);
        close_all->setObjectName(QStringLiteral("close_all"));
        sizePolicy1.setHeightForWidth(close_all->sizePolicy().hasHeightForWidth());
        close_all->setSizePolicy(sizePolicy1);

        horizontalLayout_14->addWidget(close_all);

        toolButton_2 = new QToolButton(home_tab);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        sizePolicy1.setHeightForWidth(toolButton_2->sizePolicy().hasHeightForWidth());
        toolButton_2->setSizePolicy(sizePolicy1);

        horizontalLayout_14->addWidget(toolButton_2);

        main_tabwidget->addTab(home_tab, QString());
        config_tab = new QWidget();
        config_tab->setObjectName(QStringLiteral("config_tab"));
        horizontalLayout_5 = new QHBoxLayout(config_tab);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        load_btn = new QToolButton(config_tab);
        load_btn->setObjectName(QStringLiteral("load_btn"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(load_btn->sizePolicy().hasHeightForWidth());
        load_btn->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(load_btn);

        delelte_btn = new QToolButton(config_tab);
        delelte_btn->setObjectName(QStringLiteral("delelte_btn"));
        sizePolicy2.setHeightForWidth(delelte_btn->sizePolicy().hasHeightForWidth());
        delelte_btn->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(delelte_btn);

        modify_btn = new QPushButton(config_tab);
        modify_btn->setObjectName(QStringLiteral("modify_btn"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(modify_btn->sizePolicy().hasHeightForWidth());
        modify_btn->setSizePolicy(sizePolicy3);

        horizontalLayout_5->addWidget(modify_btn);

        file_modify_btn = new QToolButton(config_tab);
        file_modify_btn->setObjectName(QStringLiteral("file_modify_btn"));
        sizePolicy2.setHeightForWidth(file_modify_btn->sizePolicy().hasHeightForWidth());
        file_modify_btn->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(file_modify_btn);

        main_tabwidget->addTab(config_tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalLayout_15 = new QHBoxLayout(tab_2);
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        createProBtn = new QToolButton(tab_2);
        createProBtn->setObjectName(QStringLiteral("createProBtn"));
        sizePolicy1.setHeightForWidth(createProBtn->sizePolicy().hasHeightForWidth());
        createProBtn->setSizePolicy(sizePolicy1);

        horizontalLayout_15->addWidget(createProBtn);

        modifyProBtn = new QToolButton(tab_2);
        modifyProBtn->setObjectName(QStringLiteral("modifyProBtn"));
        sizePolicy1.setHeightForWidth(modifyProBtn->sizePolicy().hasHeightForWidth());
        modifyProBtn->setSizePolicy(sizePolicy1);

        horizontalLayout_15->addWidget(modifyProBtn);

        deleteProBtn = new QToolButton(tab_2);
        deleteProBtn->setObjectName(QStringLiteral("deleteProBtn"));
        sizePolicy1.setHeightForWidth(deleteProBtn->sizePolicy().hasHeightForWidth());
        deleteProBtn->setSizePolicy(sizePolicy1);

        horizontalLayout_15->addWidget(deleteProBtn);

        exeProBtn = new QToolButton(tab_2);
        exeProBtn->setObjectName(QStringLiteral("exeProBtn"));
        sizePolicy1.setHeightForWidth(exeProBtn->sizePolicy().hasHeightForWidth());
        exeProBtn->setSizePolicy(sizePolicy1);

        horizontalLayout_15->addWidget(exeProBtn);

        main_tabwidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        flush_cycle = new QPushButton(tab);
        flush_cycle->setObjectName(QStringLiteral("flush_cycle"));
        flush_cycle->setGeometry(QRect(20, 10, 91, 51));
        main_tabwidget->addTab(tab, QString());

        verticalLayout_14->addWidget(main_tabwidget);

        main_widget = new QStackedWidget(centralWidget);
        main_widget->setObjectName(QStringLiteral("main_widget"));
        main_widget->setLineWidth(0);
        open_page = new QWidget();
        open_page->setObjectName(QStringLiteral("open_page"));
        verticalLayout_13 = new QVBoxLayout(open_page);
        verticalLayout_13->setSpacing(3);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        kernel_box = new QGroupBox(open_page);
        kernel_box->setObjectName(QStringLiteral("kernel_box"));
        horizontalLayout_8 = new QHBoxLayout(kernel_box);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        kernel_img = new QLabel(kernel_box);
        kernel_img->setObjectName(QStringLiteral("kernel_img"));

        horizontalLayout->addWidget(kernel_img);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        label = new QLabel(kernel_box);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font.setPointSize(10);
        label->setFont(font);

        verticalLayout_7->addWidget(label);

        kernel_state = new QLabel(kernel_box);
        kernel_state->setObjectName(QStringLiteral("kernel_state"));
        QFont font1;
        font1.setFamily(QStringLiteral("Microsoft YaHei UI"));
        kernel_state->setFont(font1);

        verticalLayout_7->addWidget(kernel_state);


        horizontalLayout->addLayout(verticalLayout_7);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        kernel_start = new QPushButton(kernel_box);
        kernel_start->setObjectName(QStringLiteral("kernel_start"));
        kernel_start->setStyleSheet(QStringLiteral(""));
        kernel_start->setFlat(false);

        verticalLayout->addWidget(kernel_start);

        kernel_close = new QPushButton(kernel_box);
        kernel_close->setObjectName(QStringLiteral("kernel_close"));
        kernel_close->setFlat(false);

        verticalLayout->addWidget(kernel_close);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalLayout->setStretch(1, 2);
        horizontalLayout->setStretch(2, 6);
        horizontalLayout->setStretch(3, 1);

        horizontalLayout_8->addLayout(horizontalLayout);


        verticalLayout_13->addWidget(kernel_box);

        broker_box = new QGroupBox(open_page);
        broker_box->setObjectName(QStringLiteral("broker_box"));
        horizontalLayout_9 = new QHBoxLayout(broker_box);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_8 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);

        broker_img = new QLabel(broker_box);
        broker_img->setObjectName(QStringLiteral("broker_img"));

        horizontalLayout_2->addWidget(broker_img);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_2 = new QLabel(broker_box);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        verticalLayout_8->addWidget(label_2);

        broker_state = new QLabel(broker_box);
        broker_state->setObjectName(QStringLiteral("broker_state"));
        broker_state->setFont(font1);

        verticalLayout_8->addWidget(broker_state);


        horizontalLayout_2->addLayout(verticalLayout_8);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        broker_start = new QPushButton(broker_box);
        broker_start->setObjectName(QStringLiteral("broker_start"));
        broker_start->setFlat(false);

        verticalLayout_2->addWidget(broker_start);

        broker_close = new QPushButton(broker_box);
        broker_close->setObjectName(QStringLiteral("broker_close"));
        broker_close->setFlat(false);

        verticalLayout_2->addWidget(broker_close);


        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(2, 6);
        horizontalLayout_2->setStretch(3, 1);

        horizontalLayout_9->addLayout(horizontalLayout_2);


        verticalLayout_13->addWidget(broker_box);

        data_box = new QGroupBox(open_page);
        data_box->setObjectName(QStringLiteral("data_box"));
        horizontalLayout_10 = new QHBoxLayout(data_box);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_9 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        data_img = new QLabel(data_box);
        data_img->setObjectName(QStringLiteral("data_img"));

        horizontalLayout_3->addWidget(data_img);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        label_3 = new QLabel(data_box);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        verticalLayout_9->addWidget(label_3);

        data_state = new QLabel(data_box);
        data_state->setObjectName(QStringLiteral("data_state"));
        data_state->setFont(font1);

        verticalLayout_9->addWidget(data_state);


        horizontalLayout_3->addLayout(verticalLayout_9);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        data_start = new QPushButton(data_box);
        data_start->setObjectName(QStringLiteral("data_start"));
        data_start->setFlat(false);

        verticalLayout_3->addWidget(data_start);

        data_close = new QPushButton(data_box);
        data_close->setObjectName(QStringLiteral("data_close"));
        data_close->setFlat(false);

        verticalLayout_3->addWidget(data_close);


        horizontalLayout_3->addLayout(verticalLayout_3);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        horizontalLayout_3->setStretch(1, 2);
        horizontalLayout_3->setStretch(2, 6);
        horizontalLayout_3->setStretch(3, 1);

        horizontalLayout_10->addLayout(horizontalLayout_3);


        verticalLayout_13->addWidget(data_box);

        log_box = new QGroupBox(open_page);
        log_box->setObjectName(QStringLiteral("log_box"));
        horizontalLayout_11 = new QHBoxLayout(log_box);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_10 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);

        log_img = new QLabel(log_box);
        log_img->setObjectName(QStringLiteral("log_img"));

        horizontalLayout_4->addWidget(log_img);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        label_4 = new QLabel(log_box);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        verticalLayout_10->addWidget(label_4);

        log_state = new QLabel(log_box);
        log_state->setObjectName(QStringLiteral("log_state"));
        log_state->setFont(font1);

        verticalLayout_10->addWidget(log_state);


        horizontalLayout_4->addLayout(verticalLayout_10);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        log_start = new QPushButton(log_box);
        log_start->setObjectName(QStringLiteral("log_start"));
        log_start->setFlat(false);

        verticalLayout_4->addWidget(log_start);

        log_close = new QPushButton(log_box);
        log_close->setObjectName(QStringLiteral("log_close"));
        log_close->setFlat(false);

        verticalLayout_4->addWidget(log_close);


        horizontalLayout_4->addLayout(verticalLayout_4);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        horizontalLayout_4->setStretch(1, 2);
        horizontalLayout_4->setStretch(2, 6);
        horizontalLayout_4->setStretch(3, 1);

        horizontalLayout_11->addLayout(horizontalLayout_4);


        verticalLayout_13->addWidget(log_box);

        inter_box = new QGroupBox(open_page);
        inter_box->setObjectName(QStringLiteral("inter_box"));
        horizontalLayout_13 = new QHBoxLayout(inter_box);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_12 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_12);

        inter_img = new QLabel(inter_box);
        inter_img->setObjectName(QStringLiteral("inter_img"));

        horizontalLayout_7->addWidget(inter_img);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        label_6 = new QLabel(inter_box);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);

        verticalLayout_12->addWidget(label_6);

        connector_state = new QLabel(inter_box);
        connector_state->setObjectName(QStringLiteral("connector_state"));
        connector_state->setFont(font1);

        verticalLayout_12->addWidget(connector_state);


        horizontalLayout_7->addLayout(verticalLayout_12);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        inter_start = new QPushButton(inter_box);
        inter_start->setObjectName(QStringLiteral("inter_start"));
        inter_start->setFlat(false);

        verticalLayout_6->addWidget(inter_start);

        inter_close = new QPushButton(inter_box);
        inter_close->setObjectName(QStringLiteral("inter_close"));
        inter_close->setFlat(false);

        verticalLayout_6->addWidget(inter_close);


        horizontalLayout_7->addLayout(verticalLayout_6);

        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);

        horizontalLayout_7->setStretch(1, 2);
        horizontalLayout_7->setStretch(2, 6);
        horizontalLayout_7->setStretch(3, 1);

        horizontalLayout_13->addLayout(horizontalLayout_7);


        verticalLayout_13->addWidget(inter_box);

        super_box = new QGroupBox(open_page);
        super_box->setObjectName(QStringLiteral("super_box"));
        horizontalLayout_12 = new QHBoxLayout(super_box);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_11 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_11);

        super_img = new QLabel(super_box);
        super_img->setObjectName(QStringLiteral("super_img"));

        horizontalLayout_6->addWidget(super_img);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        label_5 = new QLabel(super_box);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_11->addWidget(label_5);

        super_state = new QLabel(super_box);
        super_state->setObjectName(QStringLiteral("super_state"));

        verticalLayout_11->addWidget(super_state);


        horizontalLayout_6->addLayout(verticalLayout_11);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        super_start = new QPushButton(super_box);
        super_start->setObjectName(QStringLiteral("super_start"));
        super_start->setFlat(false);

        verticalLayout_5->addWidget(super_start);

        super_close = new QPushButton(super_box);
        super_close->setObjectName(QStringLiteral("super_close"));
        super_close->setFlat(false);

        verticalLayout_5->addWidget(super_close);


        horizontalLayout_6->addLayout(verticalLayout_5);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        horizontalLayout_6->setStretch(1, 2);
        horizontalLayout_6->setStretch(2, 6);
        horizontalLayout_6->setStretch(3, 1);

        horizontalLayout_12->addLayout(horizontalLayout_6);


        verticalLayout_13->addWidget(super_box);

        main_widget->addWidget(open_page);
        config_page = new QWidget();
        config_page->setObjectName(QStringLiteral("config_page"));
        verticalLayout_15 = new QVBoxLayout(config_page);
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        config_table = new QTableWidget(config_page);
        if (config_table->columnCount() < 2)
            config_table->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        config_table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        config_table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        config_table->setObjectName(QStringLiteral("config_table"));

        verticalLayout_15->addWidget(config_table);

        main_widget->addWidget(config_page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        verticalLayout_16 = new QVBoxLayout(page_2);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        procedureList = new QListWidget(page_2);
        procedureList->setObjectName(QStringLiteral("procedureList"));

        verticalLayout_16->addWidget(procedureList);

        main_widget->addWidget(page_2);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        main_widget->addWidget(page);

        verticalLayout_14->addWidget(main_widget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        main_tabwidget->setCurrentIndex(0);
        main_widget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        close_action->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0));
        start_all->setText(QApplication::translate("MainWindow", "\344\270\200\351\224\256\345\220\257\345\212\250", 0));
        close_all->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271\346\234\215\345\212\241\351\205\215\347\275\256", 0));
        toolButton_2->setText(QApplication::translate("MainWindow", "\346\227\245\345\277\227", 0));
        main_tabwidget->setTabText(main_tabwidget->indexOf(home_tab), QApplication::translate("MainWindow", "\351\246\226\351\241\265", 0));
        load_btn->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245\345\271\266\351\205\215\347\275\256", 0));
        delelte_btn->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\351\205\215\347\275\256", 0));
        modify_btn->setText(QApplication::translate("MainWindow", "\351\205\215\347\275\256\344\277\256\346\224\271", 0));
        file_modify_btn->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\344\277\256\346\224\271", 0));
        main_tabwidget->setTabText(main_tabwidget->indexOf(config_tab), QApplication::translate("MainWindow", "\351\205\215\347\275\256\346\226\207\344\273\266\344\277\256\346\224\271", 0));
        createProBtn->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\346\265\201\347\250\213", 0));
        modifyProBtn->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271\346\265\201\347\250\213", 0));
        deleteProBtn->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\346\265\201\347\250\213", 0));
        exeProBtn->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214\346\265\201\347\250\213", 0));
        main_tabwidget->setTabText(main_tabwidget->indexOf(tab_2), QApplication::translate("MainWindow", "\346\265\201\347\250\213", 0));
        flush_cycle->setText(QApplication::translate("MainWindow", "\345\210\267\346\226\260\345\221\250\346\234\237", 0));
        main_tabwidget->setTabText(main_tabwidget->indexOf(tab), QApplication::translate("MainWindow", "\350\256\276\347\275\256", 0));
        kernel_box->setTitle(QString());
        kernel_img->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Kernel", 0));
        kernel_state->setText(QApplication::translate("MainWindow", "\347\212\266\346\200\201\357\274\232", 0));
        kernel_start->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250", 0));
        kernel_close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0));
        broker_box->setTitle(QString());
        broker_img->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Broker", 0));
        broker_state->setText(QApplication::translate("MainWindow", "\347\212\266\346\200\201\357\274\232", 0));
        broker_start->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250", 0));
        broker_close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0));
        data_box->setTitle(QString());
        data_img->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "DataCenter", 0));
        data_state->setText(QApplication::translate("MainWindow", "\347\212\266\346\200\201\357\274\232", 0));
        data_start->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250", 0));
        data_close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0));
        log_box->setTitle(QString());
        log_img->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "LogCenter", 0));
        log_state->setText(QApplication::translate("MainWindow", "\347\212\266\346\200\201\357\274\232", 0));
        log_start->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250", 0));
        log_close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0));
        inter_box->setTitle(QString());
        inter_img->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "Connector", 0));
        connector_state->setText(QApplication::translate("MainWindow", "\347\212\266\346\200\201\357\274\232", 0));
        inter_start->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250", 0));
        inter_close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0));
        super_box->setTitle(QString());
        super_img->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "Supervisory", 0));
        super_state->setText(QApplication::translate("MainWindow", "\347\212\266\346\200\201\357\274\232", 0));
        super_start->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250", 0));
        super_close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0));
        QTableWidgetItem *___qtablewidgetitem = config_table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\351\205\215\347\275\256\345\220\215", 0));
        QTableWidgetItem *___qtablewidgetitem1 = config_table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\350\267\257\345\276\204", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
