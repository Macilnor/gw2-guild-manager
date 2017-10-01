#include "gw2player.h"

gw2Player::gw2Player(QString name)
{
    setName(name);
}

void gw2Player::setName(QString name)
{
    this->name = name;
}
void gw2Player::addItem(gw2Item item)
{

    int id = item.getId();
    bool found;
    for (int i = 0; i<countItems(); i++)
    {
        if (items_donated[i].getId()==id)
        {
            items_donated[i].addCount(item.getCount());
            found = true;
        }
    }
    if (!found)
        items_donated.append(item);
}

QString gw2Player::getName()
{
    return name;
}


gw2Item* gw2Player::getItem(int i)
{
    return &items_donated[i];
}
int gw2Player::countItems()
{
    int i = items_donated.count();
    return i;
}

void gw2Player::updateItems()
{

}
