#ifndef SUNNYTCSPROCEDURECHILDDIG_H
#define SUNNYTCSPROCEDURECHILDDIG_H

#include <QWidget>
#include "sunnytcsconfig.h"
#include "sunnytcsconfigitem.h"
#include <sunytcstreeitem.h>

namespace Ui {
class SunnyTcsProcedureChildDig;
}


//内置显示文件结构的小窗口
class SunnyTcsProcedureChildDig : public QWidget
{
    Q_OBJECT

public:
    explicit SunnyTcsProcedureChildDig(QString path,QWidget *parent = 0);
    ~SunnyTcsProcedureChildDig();

    void loadFileUi();
    void loadTree(SunnyTcsConfigItem *item,SunyTcsTreeItem* treeItem);
    void setFile(SunnyTcsConfig* file);

signals:
    void childDigOk(QString path,QString index);
    void childClose(QString path);

private slots:
    void on_Btn_ok_clicked();
    void on_currentAction_changed(int action);


private:
    Ui::SunnyTcsProcedureChildDig *ui;
    SunnyTcsConfig* _file=nullptr;
    qint8 _currentAction=0x00;


    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // SUNNYTCSPROCEDURECHILDDIG_H
