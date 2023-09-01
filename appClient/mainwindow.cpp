#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),socket(new QUdpSocket(this)),param(),
      textBrowser(new QTextBrowser(this)),dialogSettingsNetwork(new DialogSettingsNetwork(this))
{
    //create QMainWindow, socket , param, textBrowser, dialogSettingsNetwork;

    //create widget
    auto widget = new QWidget(this);

    //create  gridLayout
    auto gridLayout = new QGridLayout();

    //create vLabelSpinBox_.
    VLabelSpinBox vLabelSpinBox_X("X");
    VLabelSpinBox vLabelSpinBox_Y("Y");
    VLabelSpinBox vLabelSpinBox_V("V");
    VLabelSpinBox vLabelSpinBox_M("M");
    VLabelSpinBox vLabelSpinBox_S("S");
    VLabelSpinBox vLabelSpinBox_P("P");

    //create vLabelDoubleSpinBox_A
    VLabelDoubleSpinBox vLabelDoubleSpinBox_A("A");

    //create bitWidgetR
    auto bitWidgetR= new BitWidget(16,"R",widget);

    //create menu
    auto menu = new QMenu(this);

    //create actionSettingNetwork
    auto actionSettingNetwork = new QAction(this);

    //create menuBar
    auto menuBar = new QMenuBar(this);

    //create pushButtonSend
    auto pushButtonSend = new QPushButton("Отправить");

    //init widget
    widget->setLayout(gridLayout);

    //init gridLayout
    gridLayout->addWidget(textBrowser,0,0,8,1);
    gridLayout->addLayout(vLabelSpinBox_X.hBoxLayout,0,1,1,1);
    gridLayout->addLayout(vLabelSpinBox_Y.hBoxLayout,1,1,1,1);
    gridLayout->addLayout(vLabelSpinBox_V.hBoxLayout,2,1,1,1);
    gridLayout->addLayout(vLabelSpinBox_M.hBoxLayout,3,1,1,1);
    gridLayout->addLayout(vLabelSpinBox_S.hBoxLayout,4,1,1,1);
    gridLayout->addLayout(vLabelDoubleSpinBox_A.hBoxLayout,5,1,1,1);
    gridLayout->addLayout(vLabelSpinBox_P.hBoxLayout,6,1,1,1);
    gridLayout->addLayout(bitWidgetR->gridLayout,7,1,1,1);
    gridLayout->addWidget(pushButtonSend,8,1,1,1);

    //init textBrowser
    textBrowser->setStyleSheet("QTextBrowser{"
                               "padding:8px;"
                               "border-radius: 30px;"
                               "border: 2px solid #bababa;"
                               "}");

    //init vLabelSpinBox_.
    void (QSpinBox::*func)(int) = &QSpinBox::valueChanged;

    vLabelSpinBox_X.spinBox->setMaximum(63);
    connect(vLabelSpinBox_X.spinBox,func,[this](int value){
        param.X=static_cast<unsigned char>(value);
    });

    vLabelSpinBox_Y.spinBox->setMinimum(-32);
    vLabelSpinBox_Y.spinBox->setMaximum(31);
    connect(vLabelSpinBox_Y.spinBox,func,[this](int value){
        param.Y=static_cast<signed char>(value);
    });

    vLabelSpinBox_V.spinBox->setMaximum(255);
    connect(vLabelSpinBox_V.spinBox,func,[this](int value){
        param.V=static_cast<unsigned char>(value);
    });

    vLabelSpinBox_M.spinBox->setMaximum(3);
    connect(vLabelSpinBox_M.spinBox,func,[this](int value){
        param.M=static_cast<unsigned char>(value);
    });

    vLabelSpinBox_S.spinBox->setMaximum(3);
    connect(vLabelSpinBox_S.spinBox,func,[this](int value){
        param.S=static_cast<unsigned char>(value);
    });
    vLabelSpinBox_P.spinBox->setMaximum(130);
    connect(vLabelSpinBox_P.spinBox,func,[this](int value){
        param.P=static_cast<unsigned char>(value);
    });

    //init vLabelDoubleSpinBox_A
    void (QDoubleSpinBox::*funcD)(double) = &QDoubleSpinBox::valueChanged;
    vLabelDoubleSpinBox_A.doubleSpinBox->setMinimum(-12.7);
    vLabelDoubleSpinBox_A.doubleSpinBox->setMaximum(12.8);
    connect(vLabelDoubleSpinBox_A.doubleSpinBox,funcD,[this](double value){
        param.A = static_cast<float>(value);
    });

    //init bitWidgetR
    connect(bitWidgetR,&BitWidget::changeBit,[this](size_t bit,bool val){
        if(val){
            this->param.R |= 1 << bit;
        }else{
            this->param.R &= ~(1 << bit);
        }
    });

    //init menu
    menu->setTitle("Меню");
    menu->addAction(actionSettingNetwork);

    //init actionSettingNetwork
    actionSettingNetwork->setText("Настройки соеденения");
    connect(actionSettingNetwork,&QAction::triggered,[this](){
        dialogSettingsNetwork->exec();
        port = dialogSettingsNetwork->port();
        hostAddress = dialogSettingsNetwork->hostAddress();
    });

    //init port
    port=dialogSettingsNetwork->port();

    //init hostAddress
    hostAddress = dialogSettingsNetwork->hostAddress();

    //init menuBar
    menuBar->addAction(menu->menuAction());

    //init pushButtonSend
    connect(pushButtonSend,&QPushButton::pressed,[this](){
        QByteArray datagrama;
        datagrama.resize(sizeof(Param));
        std::memcpy(datagrama.data(),&param,datagrama.size());
        socket->writeDatagram(datagrama,dialogSettingsNetwork->hostAddress(),dialogSettingsNetwork->port());
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
            qDebug()<<"Size:"<<size<<" ip:"<<senderAddress<<" Port:"<<senderPort<<endl;
        }else{
            socket->readDatagram(datagrama.data(),datagrama.size(),&senderAddress,&senderPort);
        }
    }
}


MainWindow::~MainWindow()
{
}

