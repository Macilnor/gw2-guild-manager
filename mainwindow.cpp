#include "mainwindow.h"
#include <QRegExp>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    manager = new QNetworkAccessManager;
    api = new gw2api(manager);
    tmr = new QTimer();
    tmr->start(5000);
    connect(authLineEdit, SIGNAL(returnPressed()), this, SLOT(on_authButton_clicked()));
    connect(api, SIGNAL(updatedLog()), this, SLOT(onUpdateLog()));
    connect(api, SIGNAL(updatedUi()), this, SLOT(onUpdateUI()));
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    if(api->getAPIKey().isEmpty())
    {
        stackedWidget->setCurrentWidget(authPage);
    }
    else
    {
        stackedWidget->setCurrentWidget(mainPage);
        api->requestGuildID();
    }
}

void MainWindow::on_authButton_clicked()
{
    QRegExp apikeyReg("([A-Z,0-9]{8})+[-]+([A-Z,0-9]{4})+[-]+([A-Z,0-9]{4})+[-]+([A-Z,0-9]{4})+[-]+([A-Z,0-9]{20})+[-]+([A-Z,0-9]{4})+[-]+([A-Z,0-9]{4})+[-]+([A-Z,0-9]{4})+[-]+([A-Z,0-9]{12})");
    QString api_key = authLineEdit->text().trimmed();

    if(!api_key.isEmpty())
    {
        if(apikeyReg.indexIn(api_key)!= -1)
        {
            api_key = apikeyReg.cap(0);
            QFile settings("settings.json");
            if (!settings.open(QIODevice::WriteOnly))
            {
                qDebug() << "Couldn't open or create file.";
                return;
            }
            QJsonObject jsonKey;
            jsonKey.insert("api_key", api_key);
            QJsonDocument settingsJSON(jsonKey);
            settings.write(settingsJSON.toJson());
            settings.close();
            api->setAPIKey(api_key);
            api->requestGuildID();
            stackedWidget->setCurrentWidget(mainPage);
        }
        else authMessage->setText("Wrong API Key!");
    }
}

void MainWindow::updateTime()
{
    tmr->setInterval(60000);
    api->requestGuildName();
    api->requestGuildLog();
}

void MainWindow::onUpdateUI()
{
    keyLabel->setText(api->getGuildName());
}

void MainWindow::onUpdateLog()
{
    QList<gw2Player> players;
    QJsonArray log = api->getGuildLog();

    qDebug() << log.count();

    for (int i = 0; i<log.count(); i++)
    {
        int count;
        QJsonObject obj = log[i].toObject();
        if(obj["type"].toString() == "treasury")
        {

            bool found = false;

            count++;
            for (int j = 0; j<players.count(); j++)
            {
                if (players[j].getName()==obj["user"].toString())
                {
                    found = true;
                    gw2Item it(obj["item_id"].toInt(),"",obj["count"].toInt(),0);
                    players[j].addItem(it);
                }
            }
            if (!found)
            {
                gw2Player user(obj["user"].toString());
                players.append(user);
                gw2Item it(obj["item_id"].toInt(),"",obj["count"].toInt(),0);
                players.last().addItem(it);
            }
            qDebug() << count;
        }
    }


    foreach (gw2Player p, players)
    {
       qDebug() << p.getName();
       for (int i = 0; i<p.countItems(); i++)
       {
           qDebug() << p.getItem(i)->getId() << p.getItem(i)->getName() << p.getItem(i)->getCount() << p.getItem(i)->getPrice();
           qDebug() << "___________________";
       }
       qDebug() << "___________________";
    }

}
