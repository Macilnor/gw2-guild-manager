#include "mainwindow.h"
#include "gw2api/gw2api.h"
#include "gw2api/gw2guild.h"
#include <QRegExp>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

QNetworkAccessManager* manager = new QNetworkAccessManager;
gw2Guild* guild = new gw2Guild(manager);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    gw2api api(manager);
    setupUi(this);
    connect(authLineEdit, SIGNAL(returnPressed()), this, SLOT(on_authButton_clicked()));
    if(api.getAPIKey().isEmpty())
    {
        stackedWidget->setCurrentWidget(authPage);
    }
    else
    {
        stackedWidget->setCurrentWidget(mainPage);
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
                qWarning ("Couldn't open or create file.");
                return;
            }
            QJsonObject jsonKey;
            jsonKey.insert("api_key", api_key);
            QJsonDocument settingsJSON(jsonKey);
            settings.write(settingsJSON.toJson());
            settings.close();
            stackedWidget->setCurrentWidget(mainPage);
            keyLabel->setText(guild->getGuildID());
        }
        else authMessage->setText("Wrong API Key!");
    }
}
