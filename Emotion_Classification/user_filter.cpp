#include "user_filter.h"

double b[9] = {
    0.0008330715682766,                 0,-0.003332286273107,                 0,
      0.00499842940966,                 0,-0.003332286273107,                 0,
    0.0008330715682766

  };
double a[9] = {
    1,   -6.933990773964,    21.13075870675,   -36.97896787671,
40.65862348731,   -28.76703949977,    12.79166611949,   -3.268478730737,
0.3674286925029
    };

User_Filter::User_Filter()
{

}

void User_Filter::Filter_IIR(const QVector<double> &input_vec, QVector<double> &out_vec)
{
    double *x;
    double *y;
    int length_xy = input_vec.size();
    x = (double *)malloc(sizeof(double)*length_xy);
    y = (double *)malloc(sizeof(double)*length_xy);
    for(int i=0;i<length_xy;i++)
    {
        x[i] = input_vec[i];
    }
    IIR_II filter;
    filter.setPara(b, 8, a, 8);
    filter.resp(x, length_xy, y, length_xy);
    for(int i= 0; i< length_xy; i++)
    {
        out_vec.append(y[i]);
    }
}

