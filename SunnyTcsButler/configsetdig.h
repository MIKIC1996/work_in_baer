#ifndef CONFIGSETDIG_H
#define CONFIGSETDIG_H

#include <QWidget>
#include <sunnytcsconfig.h>
#include <QTreeWidget>
#include <sunytcstreeitem.h>

namespace Ui {
class ConfigSetDig;
}

class ConfigSetDig : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigSetDig(SunnyTcsConfig* con=nullptr,QWidget *parent = 0);
    ~ConfigSetDig();


    inline bool isSetFile(){return _file!=nullptr;}
    void setFile(SunnyTcsConfig* file);
    void loadFileUI();

signals:
    void setCancel();
    void setOk(SunnyTcsConfig* file);//设置完成
private slots:
    void on_clear_configDig(){_file=nullptr;}
    void on_currentNode_changed(QTreeWidgetItem* current,QTreeWidgetItem* previous);
    void on_okBtn_clicked();
    void on_item_okBtn_clicked();
    void on_cancelBtn_clicked();


protected:
    void closeEvent(QCloseEvent *event);
    void loadTree(SunnyTcsConfigItem *item,SunyTcsTreeItem* treeItem);

private:
    Ui::ConfigSetDig *ui;
    SunnyTcsConfig* _file=nullptr;
};

#endif // CONFIGSETDIG_H
