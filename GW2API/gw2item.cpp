#include "gw2item.h"

gw2Item::gw2Item(int id, QString name, int count, double price)
{
    setId(id);
    setCount(count);
    setName(name);
    setPrice(price);
}

void gw2Item::setId(int id)
{
    item_id = id;
}

void gw2Item::setCount(int c)
{
    count = c;
}

int gw2Item::getId()
{
    return item_id;
}

QString gw2Item::getName()
{
    return item_name;
}

int gw2Item::getCount()
{
    return count;
}

double gw2Item::getPrice()
{
    return price;
}

void gw2Item::addCount(int c)
{
    count += c;
}

void gw2Item::setName(QString name)
{
    item_name = name;
}

void gw2Item::setPrice(double pr)
{
    price = pr;
}
