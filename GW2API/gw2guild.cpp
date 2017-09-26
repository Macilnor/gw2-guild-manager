#include "gw2guild.h"

gw2Guild::gw2Guild() : gw2api()
{
requestAPI("https://api.guildwars2.com/v2/account?access_token="+api_key);
}

QString gw2Guild::getGuildID()
{
    return guildID;
}

QString gw2Guild::getGuildName()
{
    return guildName;
}

QJsonObject gw2Guild::getGuildLog()
{
    return guildLog;
}
