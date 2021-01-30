#include "sunytcstreeitem.h"


SunyTcsTreeItem::SunyTcsTreeItem(SunnyTcsConfigItem *item, const QStringList list):QTreeWidgetItem(list)
{
    _item=item;
}
