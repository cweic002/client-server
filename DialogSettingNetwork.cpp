#include "DialogSettingNetwork.h"

DialogSettingsNetwork::DialogSettingsNetwork(QWidget *parent):
    QDialog(parent),spinBoxPort(new QSpinBox()),
    #ifdef CLIENT
        lineEditIp(new QLineEdit()),
    #endif
    #ifdef SERVER
        comboBoxIp(new QComboBox()),
    #endif
    pushButtonAccepted(new QPushButton("Ok"))
{
    //create QDialog ,lineEditIp,spinBoxPort,comboBoxIp,pushButtonAccepted

    //create labelIp
    auto labelIp = new QLabel("ip:");

    //create labelPort
    auto labelPort = new QLabel("port:");

    //create gridLayout
    auto gridLayout = new QGridLayout();

    //create hBoxLayoutPort
    auto hBoxLayoutPort = new QHBoxLayout();

    //create hBoxLayoutIp
    auto hBoxLayoutIp = new QHBoxLayout();

    //init hBoxLayoutPort
    hBoxLayoutPort->setContentsMargins(5,0,5,0);
    hBoxLayoutPort->addWidget(labelPort);
    hBoxLayoutPort->addWidget(spinBoxPort,1,Qt::AlignmentFlag::AlignLeft);

    //init hBoxLayoutIp
    hBoxLayoutIp->setContentsMargins(5,0,5,0);
    hBoxLayoutIp->addWidget(labelIp);
    #ifdef CLIENT
        hBoxLayoutIp->addWidget(lineEditIp,Qt::AlignmentFlag::AlignLeft);
    #endif
    #ifdef SERVER
        hBoxLayoutIp->addWidget(comboBoxIp,Qt::AlignmentFlag::AlignLeft);
    #endif

    //init vBoxLayout
    gridLayout->setContentsMargins(5,5,5,5);
    gridLayout->addLayout(hBoxLayoutIp,0,0);
    gridLayout->addLayout(hBoxLayoutPort,0,1);
    gridLayout->addWidget(pushButtonAccepted,1,1);

    #ifdef CLIENT
    //init lineEditIp
    QRegularExpression reg("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
    QValidator * validator = new QRegularExpressionValidator(reg, this);
    lineEditIp->setValidator(validator);
    connect(lineEditIp,&QLineEdit::textChanged,[reg,this](const QString & value){
        QRegularExpressionMatch match = reg.match(value);
        pushButtonAccepted->setEnabled(match.hasMatch());
    });
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()){
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost){
            lineEditIp->setText(address.toString());
            break;
        }
    }
    #endif

    #ifdef SERVER
        //init comboBoxIp
        const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
        for (const QHostAddress &address: QNetworkInterface::allAddresses()){
            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
                 comboBoxIp->addItem(address.toString());
        }
    #endif

    //init spinBoxPort
    spinBoxPort->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spinBoxPort->setMinimumSize(40,20);
    spinBoxPort->setMinimum(0);
    spinBoxPort->setMaximum(65535);
    spinBoxPort->setValue(1111);

    //create pushButtonAccepted
    connect(pushButtonAccepted,&QPushButton::pressed,this,&DialogSettingsNetwork::accept);

    //init State
    this->initState();

    //init DialogSettingsNetwork
    this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint |
                   Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowTitle("Настройки соеденения");
    this->setLayout(gridLayout);
}

quint16 DialogSettingsNetwork::port(){
    return static_cast<quint16>(spinBoxPort->value());
}

QHostAddress DialogSettingsNetwork::hostAddress(){
    #ifdef CLIENT
        return QHostAddress(lineEditIp->text());
    #endif
    #ifdef SERVER
        return QHostAddress(comboBoxIp->currentText());
    #endif
}

void DialogSettingsNetwork::accept(){
    state.saveState();
    DialogSettingsNetwork::QDialog::accept();
}

void DialogSettingsNetwork::closeEvent(QCloseEvent *){
    state.restoreState();
    DialogSettingsNetwork::QDialog::reject();
}

void DialogSettingsNetwork::initState(){

    //FSaveSpinBoxPort
    auto FSaveSpinBoxPort =[](QSpinBox * self){
        return self->value();
    };
    //FSavePushButtonAccepted
    auto FSavePushButtonAccepted =[](QPushButton * self){
        return self->isEnabled();
    };
    #ifdef CLIENT
        //lineEditIp
        auto FSaveLineEditIp =[](QLineEdit * self){
            return self->text();
        };
    #endif
    #ifdef SERVER
        //FSaveComboBoxIp
        auto FSaveComboBoxIp =[](QComboBox * self){
            return self->currentText();
        };
    #endif

    //FRestoreSpinBoxPort
    auto FRestoreSpinBoxPort =[](QSpinBox * self,int save){
        self->setValue(save);
    };
    //FRestorePushButtonAccepted
    auto FRestorePushButtonAccepted =[](QPushButton * self,bool save){
        self->setEnabled(save);
    };

    #ifdef CLIENT
        //lineEditIp
        auto FRestoreLineEditIp =[](QLineEdit * self,QString & save){
            return self->setText(save);
        };
    #endif
    #ifdef SERVER
        //FRestoreComboBoxIp
        auto FRestoreComboBoxIp =[](QComboBox * self,QString save){
            self->setCurrentText(save);
        };
    #endif


    //state.addState(lineEditIp,FSaveLineEditIp,FRestoreLineEditIp);
    state.addState(spinBoxPort,FSaveSpinBoxPort,FRestoreSpinBoxPort);
    state.addState(pushButtonAccepted,FSavePushButtonAccepted,FRestorePushButtonAccepted);

    #ifdef CLIENT
        state.addState(lineEditIp,FSaveLineEditIp,FRestoreLineEditIp);
    #endif
    #ifdef SERVER
        state.addState(comboBoxIp,FSaveComboBoxIp,FRestoreComboBoxIp);
    #endif
}

DialogSettingsNetwork::~DialogSettingsNetwork(){}



