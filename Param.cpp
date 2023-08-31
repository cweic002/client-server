#include "Param.h"

float32::operator float8() const{
    float8 temp;
    temp.M = M_4;
    temp.P = P_1;
    temp.P_S = P_S;
    temp.S = S;
    return temp;
}

float32::operator float() const {
    union {
        float32 f32;
        float f;
    };
    f32=*this;
    return f;
}

float8::operator float() const {
    float32 temp;
    temp.M_19 = 0;
    temp.M_4 = M;
    temp.P_1 = P;
    temp.P_2 = 0;
    temp.P_S = P_S;
    temp.S = S;
    return temp;
}

QTextStream &operator<<(QTextStream & stream,const float8 & right){
    stream << (float)right;
    return stream;
}

Param::operator QString() const{
    QString s;
    QTextStream out(&s);
    out<< "X:"<<X<< " ;Y:"<<Y;
    out<< " ;V:"<<V<< " ;M:"<<M;
    out<< " ;S:"<<S<< " ;A:"<<A;
    out<< " ;P:"<<P<< " ;R:"<<bin<<R;
    return s;
}

Param::Param():R(0),X(0),M(0),V(0),P(0),A(0),Y(0){
    S=0;
}
