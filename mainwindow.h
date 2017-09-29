#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gw2api/gw2api.h"
#include "gw2api/gw2item.h"
#include "gw2api/gw2player.h"
#include <QMainWindow>
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private slots:
    void on_authButton_clicked();
    void onUpdateLog();
    void updateTime();
    void onUpdateUI();

private:
    gw2api *api;
    QNetworkAccessManager *manager;
    QTimer *tmr;
};

#endif // MAINWINDOW_H
