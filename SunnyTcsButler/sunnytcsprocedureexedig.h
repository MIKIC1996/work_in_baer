#ifndef SUNNYTCSPROCEDUREEXEDIG_H
#define SUNNYTCSPROCEDUREEXEDIG_H

#include <QWidget>
#include "sunnytcsprocedureaction.h"
#include "sunnytcsconfig.h"

namespace Ui {
class SunnyTcsProcedureExeDig;
}

class SunnyTcsProcedureExeDig : public QWidget
{
    Q_OBJECT

public:
    explicit SunnyTcsProcedureExeDig(QWidget *parent = 0);
    ~SunnyTcsProcedureExeDig();

    inline SunnyTcsProcedure* getProcedure(){return _procedure;}
    inline void setProcedure(SunnyTcsProcedure* pro){_procedure=pro;}

    qint8 setProcedureFile(SunnyTcsProcedure* pro);
    void openAllNeedFile();

    qint8 exeAction(qint8 type);

private slots:
    void on_Btn_next_clicked();//
    void on_Btn_save_clicked();
private:


    Ui::SunnyTcsProcedureExeDig *ui;

    SunnyTcsProcedure* _procedure=nullptr;


    QMap<QString,SunnyTcsConfig*> _fileMap;//所有的文件
    QMap<SunnyTcsProcedureAction*,QList<QString>> _actionFileMap;//动作与其文件的关联map
//    QList<SunnyTcsProcedureAction*> _actionOrder;//动作的执行顺序<1,type>

    qint32 _currentIndex=0;//当前在第几步了


};

#endif // SUNNYTCSPROCEDUREEXEDIG_H
