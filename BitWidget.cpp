#include "BitWidget.h"
#include <QDebug>

BitWidget::BitWidget(size_t size,const QString & name,QWidget * parent):_label(new QLabel(name)),_size(size){
    _labelBit.resize(size);
    _spinBoxBit.resize(size);
    gridLayout = new QGridLayout();
    gridLayout->addWidget(_label,0,0,1,1);
    void (QSpinBox::*spinBox_offset_func)(int) = &QSpinBox::valueChanged;
    for(size_t i = 0;i<size;++i){
        _labelBit[i] = new QLabel(QString::number(i),parent);
        _labelBit[i]->setSizePolicy(QSizePolicy::Policy::Minimum,QSizePolicy::Policy::Minimum);
        _spinBoxBit[i] = new QSpinBox(parent);
        _spinBoxBit[i]->setMinimum(0);
        _spinBoxBit[i]->setMaximum(1);
        _spinBoxBit[i]->setButtonSymbols(QAbstractSpinBox::NoButtons);
        _spinBoxBit[i]->setSizePolicy(QSizePolicy::Policy::Minimum,QSizePolicy::Policy::Minimum);
        gridLayout->addWidget(_spinBoxBit[i],0,1+i);
        gridLayout->addWidget(_labelBit[i],1,1+i);
        connect(_spinBoxBit[i],spinBox_offset_func,[this,i](int value){
            emit this->changeBit(i,value);
        });
    };
    gridLayout->setMargin(1);
}
