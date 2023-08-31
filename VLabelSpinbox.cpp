#include "VLabelSpinbox.h"

VLabelSpinBox::VLabelSpinBox(const QString & name):label(new QLabel(name)),
    spinBox(new QSpinBox()),hBoxLayout(new QHBoxLayout()){
    spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spinBox->setSizePolicy(QSizePolicy::Policy::Minimum,QSizePolicy::Policy::Minimum);
    label->setSizePolicy(QSizePolicy::Policy::Minimum,QSizePolicy::Policy::Minimum);
    hBoxLayout->addWidget(label);
    hBoxLayout->addWidget(spinBox);
    hBoxLayout->setMargin(1);
}

VLabelSpinBox::~VLabelSpinBox(){

}
