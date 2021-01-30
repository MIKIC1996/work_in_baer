#ifndef SUNNYTCSFILESETDIG_H
#define SUNNYTCSFILESETDIG_H
#include "sunnytcsconfig.h"
#include "sunytcstreeitem.h"

#include <QWidget>

namespace Ui {
class SunnyTcsFileSetDig;
}

class SunnyTcsFileSetDig : public QWidget
{
    Q_OBJECT

public:
    explicit SunnyTcsFileSetDig(SunnyTcsConfig* config=nullptr,QWidget *parent = 0);
    ~SunnyTcsFileSetDig();

    qint8 loadFileUi();
    inline bool isSetFile(){return _file!=nullptr;}
    void setFile(SunnyTcsConfig* file);

protected:
    void loadTree(SunnyTcsConfigItem *item,SunyTcsTreeItem* treeItem);

signals:
    void file_setOk();
    void file_setCancel();
private slots:
    void on_currentNode_changed(QTreeWidgetItem* current,QTreeWidgetItem* previous);
    void on_okBtn_clicked();
    void on_cancelbtn_clicked();
    void on_Btn_save_clicked();
private:
    Ui::SunnyTcsFileSetDig *ui;

    SunnyTcsConfig* _file;
};

#endif // SUNNYTCSFILESETDIG_H
