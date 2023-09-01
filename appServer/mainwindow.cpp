#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),socket(new QUdpSocket(this)),
      textBrowser(new QTextBrowser(this)),dialogSettingsNetwork(new DialogSettingsNetwork(this))
{
    //create QMainWindow, socket , param, dialogSettingsNetwork;

    //create widget
    auto widget = new QWidget(this);

    //create  gridLayout
    auto gridLayout = new QGridLayout();

    //create setting
    auto menu = new QMenu(this);

    //create setting
    auto settingNetwork = new QAction(this);

    //create menuBar
    auto menuBar = new QMenuBar(this);

    //create pushButtonConnect
    auto pushButtonConnect = new QPushButton("Открыть соеденение",this);

    //create pushButtonDisconnect
    auto pushButtonDisconnect = new QPushButton("закрыть соеденение",this);

    //init widget
    widget->setLayout(gridLayout);

    //init gridLayout
    gridLayout->addWidget(textBrowser,0,0,8,1);
    gridLayout->addWidget(pushButtonConnect,8,0,1,1);
    gridLayout->addWidget(pushButtonDisconnect,8,0,1,1);

    //init textBrowser
    textBrowser->setStyleSheet("QTextBrowser{"
                               "padding:8px;"
                               "border-radius: 30px;"
                               "border: 2px solid #bababa;"
                               "}");

    //init menu
    menu->setTitle("Меню");
    menu->addAction(settingNetwork);

    //init setting
    settingNetwork->setText("Настройки соеденения");
    connect(settingNetwork,&QAction::triggered,[this](){
        dialogSettingsNetwork->exec();
        port=dialogSettingsNetwork->port();
        hostAddress = dialogSettingsNetwork->hostAddress();
    });

    //init port
    port=dialogSettingsNetwork->port();

    //init hostAddress
    hostAddress = dialogSettingsNetwork->hostAddress();

    //init menuBar
    menuBar->addAction(menu->menuAction());

    //init pushButtonConnect
    connect(pushButtonConnect,&QPushButton::pressed,[this,pushButtonConnect,pushButtonDisconnect](){
        auto status = this->socket->bind(hostAddress,port);
        if(status){
            pushButtonConnect->hide();
            pushButtonDisconnect->show();
        }
    });

    //init pushButtonDisconnect
    pushButtonDisconnect->hide();
    connect(pushButtonDisconnect,&QPushButton::pressed,[this,pushButtonConnect,pushButtonDisconnect](){
        this->socket->close();
        pushButtonConnect->show();
        pushButtonDisconnect->hide();
    });

    //init socket
    connect(socket,&QUdpSocket::readyRead,this,&MainWindow::readingData);

    //init MainWindow
    this->setCentralWidget(widget);
    this->setMenuBar(menuBar);
    this->setStyleSheet("MainWindow{background:white;}");

}

void MainWindow::readingData(){
    while (socket->hasPendingDatagrams()) {
        auto size=socket->pendingDatagramSize();
        QByteArray datagrama;
        datagrama.resize(size);
        QHostAddress senderAddress;
        quint16 senderPort;
        if(size==sizeof(Param)){
            Param param;
            socket->readDatagram(datagrama.data(),datagrama.size(),&senderAddress,&senderPort);
            std::memcpy(&param,datagrama.data(),datagrama.size());
            textBrowser->append(param);
            listIp.emplace(senderAddress.toString(),senderPort);
            for(auto iter:listIp){
                socket->writeDatagram(datagrama.data(),datagrama.size(),QHostAddress(iter.first),iter.second);
            }
        }else{
            socket->readDatagram(datagrama.data(),datagrama.size(),&senderAddress,&senderPort);
        }
    }
}

MainWindow::~MainWindow()
{
}

