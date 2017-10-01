#ifndef GW2PLAYER_H
#define GW2PLAYER_H

#include <QObject>
#include "gw2item.h"

class gw2Player
{
private:
    QString name;
    QList<gw2Item> items_donated;
public:
    gw2Player(QString);

    void setName(QString);
    void addItem(gw2Item);

    QString getName();
    gw2Item* getItem(int i);
    int countItems();

    void updateItems();
};

#endif // GW2PLAYER_H
