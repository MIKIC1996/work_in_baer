#ifndef SUNNYTCSPROCEDURECONFIGDIG_H
#define SUNNYTCSPROCEDURECONFIGDIG_H

#include <QWidget>
#include "sunnytcsconfig.h"
#include <QMap>
#include "sunnytcsprocedureaction.h"
#include "sunnytcsprocedurechilddig.h"
#include <QMultiMap>

namespace Ui {
class SunnyTcsProcedureConfigDig;
}

class SunnyTcsProcedureConfigDig : public QWidget
{
    Q_OBJECT

public:
    explicit SunnyTcsProcedureConfigDig(QWidget *parent = 0);
    ~SunnyTcsProcedureConfigDig();
    void setProcedureFile(SunnyTcsProcedure *pro);


signals:
    void procedureSave();
    void procedureClose();

private slots:
    void on_fileOpenBtn_clicked();

    void on_childOk(QString path,QString index);
    void on_childClose(QString path);

    void on_Btn_addAction_clicked();

    void on_Btn_createAction_clicked();
    void on_Btn_deleteAction_clicked();
    void on_currentTab_changed(int index);
    void on_Btn_saveProcedure_clicked();
    void on_actionBox_changed(int index);
    void on_addJsonCBox_changed(int index);
    void on_Btn_attsAdd_clicked();
    void on_Btn_jsonValue_clicked();

    void on_Btn_deleteSelected_clicked();

private:
    void openFile(QString file);


    Ui::SunnyTcsProcedureConfigDig *ui;
    SunnyTcsProcedure* _procedure;
    QMap<QString,SunnyTcsProcedureChildDig*> _childDigs;//<path,SunnyTcsProcedureChildDig> 子窗口集
    QMap<QString,QList<QString>> _indexMap;//已选的标签集 <QString path，qList<QString> index>



    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // SUNNYTCSPROCEDURECONFIGDIG_H
