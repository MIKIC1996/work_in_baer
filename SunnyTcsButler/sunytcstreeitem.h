#ifndef SUNYTCSTREEITEM_H
#define SUNYTCSTREEITEM_H

#include <QObject>
#include <QTreeWidget>
#include <sunnytcsconfigitem.h>

class SunyTcsTreeItem :public QTreeWidgetItem
{
public:
    SunyTcsTreeItem(SunnyTcsConfigItem* item,const QStringList list);
    ~SunyTcsTreeItem(){_item=nullptr;}
    inline SunnyTcsConfigItem* getItem(){return _item;}
    inline void setItem(SunnyTcsConfigItem* item){_item=item;}
    inline void setItemNull(){_item=nullptr;}

signals:


private:
    SunnyTcsConfigItem* _item;
};

#endif // SUNYTCSTREEITEM_H
