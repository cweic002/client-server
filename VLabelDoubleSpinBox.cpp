#include "VLabelDoubleSpinBox.h"

VLabelDoubleSpinBox::VLabelDoubleSpinBox(const QString & name):label(new QLabel(name)),
    doubleSpinBox(new QDoubleSpinBox()),hBoxLayout(new QHBoxLayout()){
    doubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    doubleSpinBox->setSizePolicy(QSizePolicy::Policy::Minimum,QSizePolicy::Policy::Minimum);
    label->setSizePolicy(QSizePolicy::Policy::Minimum,QSizePolicy::Policy::Minimum);
    hBoxLayout->addWidget(label);
    hBoxLayout->addWidget(doubleSpinBox);
    hBoxLayout->setMargin(1);
}
