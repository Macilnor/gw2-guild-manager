#ifndef GW2API_H
#define GW2API_H

#include <QObject>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

class gw2api : public QObject
{
    Q_OBJECT
private:
    QString api_key;
    QNetworkAccessManager *networkManager;
//guild
    QString guildID;
    QString guildName;
    QJsonArray guildLog;

public:
    gw2api(QNetworkAccessManager*);//конструктор
    void setAPIKey(QString);
    QString getAPIKey();
    //void requestAPI(QString);
//guild
    QString getGuildID();
    QString getGuildName();
    QJsonArray getGuildLog();
    void requestGuildID();
    void requestGuildName();
    void requestGuildLog();
//items
    void requestItemName(int id);
    void requestItemPrice(int id);
signals:
    //void requestDone(QJsonObject *replyObj);
    void updatedLog();
    void updatedUi();
public slots:
    //void slotReadyRead();
    void slotError(QNetworkReply::NetworkError);
    void slotSslErrors(QList<QSslError>);
//guild
    void setGuildID();
    void setGuildName();
    void setGuildLog();
//items
    void setItemName();
    void setItemPrice();
};

#endif // GW2API_H
