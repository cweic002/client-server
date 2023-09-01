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
#include "VLabelDoubleSpinbox.h"
#include "BitWidget.h"
#include "Param.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void readingData();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QUdpSocket * socket;
    Param param;
    quint16 port;
    QTextBrowser * textBrowser;
    QHostAddress hostAddress;
    DialogSettingsNetwork * dialogSettingsNetwork;
};
#endif // MAINWINDOW_H
