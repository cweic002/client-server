#ifndef PARAM_H
#define PARAM_H
#include <QTextStream>

struct float8{
    float8():numb(0){}
    float8(double a):numb(static_cast<unsigned char>(a*10-1)){}
    signed char numb;
    operator float() const;
};

struct Param
{
    unsigned short R;
    unsigned char X: 6;
    unsigned char M: 2;
    unsigned char V: 8;
    unsigned char P : 8;
    float8 A;
    union{
        struct{
            signed char Y: 6;
        };
        struct{
            unsigned char : 6;
            unsigned char S: 2;
        };
    };
    Param();
    operator QString() const;
};

#endif // PARAM_H
