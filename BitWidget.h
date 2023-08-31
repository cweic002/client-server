#ifndef BITWIDGET_H
#define BITWIDGET_H

#include "QLabel"
#include "QSpinBox"
#include "QDoubleSpinBox"
#include "QGridLayout"

class BitWidget :public QObject
{
    Q_OBJECT
    QLabel * _label;
    std::vector<QLabel*> _labelBit;
    std::vector<QSpinBox*> _spinBoxBit;
    size_t _size;
public:
    QGridLayout * gridLayout;
    BitWidget(size_t size,const QString & name,QWidget *parent=nullptr);
Q_SIGNALS:
    void changeBit(size_t bit,bool value);
};

#endif // BITWIDGET_H
