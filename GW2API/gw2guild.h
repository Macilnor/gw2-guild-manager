#ifndef GW2GUILD_H
#define GW2GUILD_H

#include <QApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include "gw2api.h"

class gw2Guild : public gw2api
{
private:
    QString guildID;
    QString guildName;
    QJsonObject guildLog;
public:
    gw2Guild(QNetworkAccessManager* manager);
    QString getGuildID();
    QString getGuildName();
    QJsonObject getGuildLog();
};

#endif // GW2GUILD_H
