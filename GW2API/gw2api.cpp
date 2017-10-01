#include "gw2api.h"
#include <QDebug>

gw2api::gw2api(QNetworkAccessManager *networkManager)
{
    this->networkManager = networkManager;

    QFile settings("settings.json");
    if (!settings.open(QIODevice::ReadWrite))
    {
        qWarning ("Couldn't open or create file.");
        this->api_key = "";
        return;
    }
    QByteArray setarray = settings.readAll();
    QJsonDocument settingsJSON(QJsonDocument::fromJson(setarray));
    QJsonObject jsonKey = settingsJSON.object();
    api_key = jsonKey["api_key"].toString();
    settings.close();
}

void gw2api::setAPIKey(QString api_key)
{
    this->api_key = api_key;
}

QString gw2api::getAPIKey()
{
    return api_key;
}

//void gw2api::requestAPI(QString requestURL)
//{
//    QNetworkRequest* request = new QNetworkRequest;
//    request->setUrl(QUrl(requestURL));
//    //qDebug() << request.url();

//    QNetworkReply *reply = networkManager->get(*request);

//    connect(reply, SIGNAL(finished()), this, SLOT(slotReadyRead()));
//    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
//            this, SLOT(slotError(QNetworkReply::NetworkError)));
//    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
//            this, SLOT(slotSslErrors(QList<QSslError>)));
//}

//void gw2api::slotReadyRead()
//{
//    QNetworkReply* reply = qobject_cast<QNetworkReply*> (QObject::sender());
//    if (reply->error() != QNetworkReply::NoError)
//    {
//        qDebug() << "Error. " << reply->errorString();
//        return;
//    }
//    QByteArray rearray = reply->readAll();
//    QJsonDocument replyJSON(QJsonDocument::fromJson(rearray));
//    QJsonObject* replyObject = new QJsonObject;
//    *replyObject = replyJSON.object();
//    //qDebug() << *replyObject;
//    reply->close();
//    reply->deleteLater();
//    emit requestDone(replyObject);

//}

void gw2api::slotError(QNetworkReply::NetworkError error)
{
    qDebug() << "Error. " << error;
}

void gw2api::slotSslErrors(QList<QSslError> sslErrors)
{
    qDebug() << "SSLError."<< sslErrors;
}

QString gw2api::getGuildID()
{
    if (guildName.isEmpty())
    {
        requestGuildID();
    }
    return guildID;
}

QString gw2api::getGuildName()
{
    if (guildName.isEmpty())
    {
        requestGuildName();
    }
    return guildName;
}

QJsonArray gw2api::getGuildLog()
{
    if (guildLog.isEmpty())
    {
        requestGuildLog();
    }
    return guildLog;
}

void gw2api::requestGuildID()
{
    //requestAPI("https://api.guildwars2.com/v2/account?access_token="+api_key);
    //connect(this, &gw2api::requestDone, this, &gw2api::setGuildID);

    QUrl requestURL("https://api.guildwars2.com/v2/account?access_token="+api_key);

    QNetworkRequest* request = new QNetworkRequest;
    request->setUrl(requestURL);
//    qDebug() << request->url();

    QNetworkReply *reply = networkManager->get(*request);

    connect(reply, SIGNAL(finished()), this, SLOT(setGuildID()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(slotSslErrors(QList<QSslError>)));
}

void gw2api::requestGuildName()
{
    if(!guildID.isEmpty())
    {
        //requestAPI("https://api.guildwars2.com/v2/guild/"+guildID+"?access_token="+api_key);
        //connect(this, &gw2api::requestDone, this, &gw2api::setGuildName);

        QUrl requestURL("https://api.guildwars2.com/v2/guild/"+guildID+"?access_token="+api_key);

        QNetworkRequest* request = new QNetworkRequest;
        request->setUrl(requestURL);
//        qDebug() << request->url();

        QNetworkReply *reply = networkManager->get(*request);

        connect(reply, SIGNAL(finished()), this, SLOT(setGuildName()));
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
                this, SLOT(slotError(QNetworkReply::NetworkError)));
        connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
                this, SLOT(slotSslErrors(QList<QSslError>)));
    }
}

void gw2api::requestGuildLog()
{
    if(!guildID.isEmpty())
    {
        //requestAPI("https://api.guildwars2.com/v2/guild/"+guildID+"/log?access_token="+api_key);
        //connect(this, &gw2api::requestDone, this, &gw2api::setGuildLog);
        QUrl requestURL("https://api.guildwars2.com/v2/guild/"+guildID+"/log?access_token="+api_key);

        QNetworkRequest* request = new QNetworkRequest;
        request->setUrl(requestURL);
<<<<<<< HEAD
        qDebug() << request->url();
=======
        //qDebug() << request->url();
>>>>>>> 63edb5c03f96451cf0bd3e62ca3bab4fec46d1d4

        QNetworkReply *reply = networkManager->get(*request);

        connect(reply, SIGNAL(finished()), this, SLOT(setGuildLog()));
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
                this, SLOT(slotError(QNetworkReply::NetworkError)));
        connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
                this, SLOT(slotSslErrors(QList<QSslError>)));
    }
}

void gw2api::setGuildID()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*> (QObject::sender());
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Error. " << reply->errorString();
        return;
    }
    QByteArray rearray = reply->readAll();
    QJsonDocument replyJSON(QJsonDocument::fromJson(rearray));
    QJsonObject replyObject = replyJSON.object();
//    qDebug() << replyObject;
    reply->close();
    reply->deleteLater();

    QJsonValue guild = replyObject.value("guild_leader");
    if(guild.isArray())
    {
        QJsonArray ja = guild.toArray();
        guildID = ja.at(0).toString();
    }
    qDebug() << guildID;

}

void gw2api::setGuildName()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*> (QObject::sender());
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Error. " << reply->errorString();
        return;
    }
    QByteArray rearray = reply->readAll();
    QJsonDocument replyJSON(QJsonDocument::fromJson(rearray));
    QJsonObject replyObject = replyJSON.object();
//    qDebug() << replyObject;
    reply->close();
    reply->deleteLater();

    QJsonValue guild = replyObject.value("name");
    guildName = guild.toString();
    qDebug() << guildName;
    emit updatedUi();
}

void gw2api::setGuildLog()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*> (QObject::sender());
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Error. " << reply->errorString();
        return;
    }
    QByteArray rearray = reply->readAll();
    QJsonDocument replyJSON(QJsonDocument::fromJson(rearray));
    QJsonArray replyArr = replyJSON.array();
    reply->close();
    reply->deleteLater();

    guildLog = replyArr;

    //qDebug() << guildLog[0];

    emit updatedLog();
}

void gw2api::setItemName()
{

}

void gw2api::setItemPrice()
{

}
