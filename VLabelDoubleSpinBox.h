#ifndef VLABELDOUBLESPINBOX_H
#define VLABELDOUBLESPINBOX_H

#include "QLabel"
#include "QDoubleSpinBox"
#include "QDoubleSpinBox"
#include "QHBoxLayout"

struct VLabelDoubleSpinBox
{
    QLabel * label;
    QDoubleSpinBox * doubleSpinBox;
    QHBoxLayout * hBoxLayout;
    VLabelDoubleSpinBox(const QString & name);
};

#endif // VLABELDOUBLESPINBOX_H
