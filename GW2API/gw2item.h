#ifndef GW2ITEM_H
#define GW2ITEM_H

#include <QObject>

class gw2Item
{
private:
    int item_id;
    QString item_name;
    int count;
    double price;
public:
    gw2Item(int i, QString n, int c, double p);

    void setId(int);
    void setCount(int);
    void setName(QString);
    void setPrice(double);

    int getId();
    QString getName();
    int getCount();
    double getPrice();

    void addCount(int);

};

#endif // GW2ITEM_H
