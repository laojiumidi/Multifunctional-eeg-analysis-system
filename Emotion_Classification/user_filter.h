#ifndef USER_FILTER_H
#define USER_FILTER_H

#include <QVector>

#include "iir_ii.h"

class User_Filter
{
public:
    User_Filter();

    void Filter_IIR(const QVector<double> &input_vec, QVector<double> &out_vec);
};

#endif // USER_FILTER_H
