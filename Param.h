#ifndef PARAM_H
#define PARAM_H

#include <QTextStream>

struct float8;

struct float32{
    float32() = default;
    unsigned int M_19 : 19;
    unsigned int M_4 : 4;
    unsigned int P_1 : 2;
    unsigned int P_2 : 5;
    unsigned int P_S : 1;
    unsigned int S : 1;
    operator float() const;
    operator float8() const;
};

struct float8{
    float8():M(0),P(0),P_S(0),S(0){}
    float8(float a){
        union {
            float f;
            float32 f32;
        };
        f = a;
        *this = f32;
    }
    char M:4;
    char P:2;
    char P_S:1;
    char S:1;
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
