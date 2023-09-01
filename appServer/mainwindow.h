#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QUdpSocket>
#include <cstring>
#include <QMenu>
#include <QMenuBar>
#include <QDialog>
#include <QTextBrowser>
#include "DialogSettingNetwork.h"
#include "VLabelSpinbox.h"
#include "Param.h"
#include <set>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void readingData();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    std::set<std::pair<QString,quint16>> listIp;
    QUdpSocket * socket;
    quint16 port;
    QHostAddress hostAddress;
    QTextBrowser * textBrowser;
    DialogSettingsNetwork * dialogSettingsNetwork;
};
#endif // MAINWINDOW_H
