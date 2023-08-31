#ifndef PAGESETTINGS_H
#define PAGESETTINGS_H
#include "State.h"
#include <QDialog>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include "QNetworkInterface"
#include "QRegularExpression"

class DialogSettingsNetwork : public QDialog
{
    Q_OBJECT
public slots:
    void accept() override;
public:
    void closeEvent(QCloseEvent *) override;
    explicit DialogSettingsNetwork(QWidget *parent = nullptr);
    ~DialogSettingsNetwork();
    quint16 port();
    QHostAddress hostAddress();
private:
    void initState();
    QSpinBox * spinBoxPort;
    //client
    #ifdef CLIENT
        QLineEdit * lineEditIp;
    #endif
    //server
    #ifdef SERVER
        QComboBox * comboBoxIp;
    #endif
    QPushButton * pushButtonAccepted;
    State state;
};

#endif // PAGESETTINGS_H
