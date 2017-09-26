#include "gw2api.h"
#include <QDebug>

gw2api::gw2api()
{
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

QJsonObject gw2api::requestAPI(QString request)
{
    QJsonObject object;
    networkManager = new QNetworkAccessManager();
    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(request)));
    qDebug() << reply->url();
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    object = document.object();
    qDebug() << reply->errorString();
    reply->deleteLater();
    return object;
}

