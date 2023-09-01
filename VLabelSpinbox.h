#ifndef VLABELSPINBOX_H
#define VLABELSPINBOX_H

#include "QLabel"
#include "QSpinBox"
#include "QDoubleSpinBox"
#include "QHBoxLayout"

struct VLabelSpinBox
{
    QLabel * label;
    QSpinBox * spinBox;
    QHBoxLayout * hBoxLayout;
    VLabelSpinBox(const QString & name);
};

#endif // LABELSPINBOX_H
