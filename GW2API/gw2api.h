#ifndef GW2API_H
#define GW2API_H

#include <QObject>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

class gw2api:public QObject
{
    Q_OBJECT
protected:
    QString api_key;
    QNetworkAccessManager *networkManager;
public:
    gw2api(QNetworkAccessManager *manager);//конструктор
    void setAPIKey(QString);
    QString getAPIKey();
    QJsonObject requestAPI(QString request);
signals:
public slots:
};

#endif // GW2API_H
