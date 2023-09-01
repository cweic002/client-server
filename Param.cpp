#include "Param.h"

float8::operator float() const {
    return (static_cast<double>((numb+1)*10))/100;
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
